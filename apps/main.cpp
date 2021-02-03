
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include "include/Stop.hpp"
#include "include/StopCollection.hpp"
#include "include/Database.hpp"
#include "include/Filesystem.hpp"
#include "include/PriceCalculator.hpp"
#include "include/UserInterface.hpp"

struct CanceledException : public std::exception
{
    const char *what() const throw()
    {
        return "Process canceled.";
    }
};

class App
{
protected:
    Filesystem *files;
    Database *db;
    Bank *bank;
    PriceCalculator *priceCalculator;
    StopCollection *stops;
    UserInterface *ui;

    bool isValidPaymentInput(const unsigned int &price, const int &amount)
    {
        int diff = amount - price;
        unsigned int max = -1;

        return diff > 0 && amount < max;
    }

public:
    App()
    {
        const std::string dbPath = "db.txt";

        this->files = new Filesystem();
        this->db = new Database(files, dbPath);
        this->bank = new Bank();
        this->priceCalculator = new PriceCalculator(bank, db->getPricePerDistance());
        this->stops = db->getStops();
    }

    Bank *getBank()
    {
        return this->bank;
    }

    Stop *askForDestination()
    {
        Stop *destination;
        std::string searchTerm;

        this->ui->askForDestination();

        while (true)
        {
            searchTerm = this->ui->getStringInput();

            try
            {
                destination = this->stops->findFirst([searchTerm](Stop *stop) -> bool {
                    return stop->getName() == searchTerm;
                });
            }
            catch (const std::invalid_argument *e)
            {
                this->ui->showDestinationNotFoundAndRetry(searchTerm);
                continue;
            }

            return destination;
        }
    }

    unsigned int askForPayment(const unsigned int &price)
    {
        int paid;

        while (true)
        {
            this->ui->askForPayment(price);
            paid = this->ui->getIntegerInput();

            if (this->isValidPaymentInput(price, paid))
            {
                return paid;
            }

            if (std::cin.fail())
            {
                // clear error state
                std::cin.clear();
                // discard 'bad' character(s)
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            this->ui->showInvalidAmounPaidAndAskForRetry();

            this->askForCancel();
        }
    }

    std::map<unsigned int, unsigned int> payment(Stop *destination, const unsigned int &price)
    {
        std::map<unsigned int, unsigned int> change;
        unsigned int paid;

        while (true)
        {
            paid = this->askForPayment(price);

            if (paid == price)
            {
                break;
            }

            try
            {
                change = this->priceCalculator->getChange(paid - price);
            }
            catch (std::invalid_argument &e)
            {
                this->ui->showGiveChangeNotPossibleAndAskForRetry();

                this->askForCancel();

                continue;
            }

            break;
        }

        this->ui->showPayment(price, paid);

        return change;
    }

    void cancel()
    {
        throw CanceledException();
    }

    void askForCancel()
    {
        char cancel;

        this->ui->askForCancel();
        cancel = this->ui->getCharInput();

        if (cancel == 'j')
        {
            this->cancel();
        }
    }

    void giveChange(const std::map<unsigned int, unsigned int> &change)
    {
        for (auto const &[coin, quantity] : change)
        {
            bank->withdraw(coin, quantity);
        }

        this->ui->showChange(change);
    }

    void printTicket(Stop *destination, const unsigned int &price)
    {
        this->ui->showTicket(destination, price);
    }

    void booking()
    {
        Stop *destination;
        unsigned int price;
        std::map<unsigned int, unsigned int> change;

        this->ui->showBookingStart();
        this->ui->showAllStops(this->stops);

        // Get destination.
        destination = this->askForDestination();
        this->ui->showDestinationSelected(destination);

        // Get destination price.
        price = this->priceCalculator->getPriceFor(destination);
        this->ui->showDestinationPrice(price);

        // Payment.
        change = this->payment(destination, price);

        this->printTicket(destination, price);
        this->giveChange(change);
    }

    void run()
    {
        while (true)
        {
            try
            {
                this->booking();
            }
            catch (const CanceledException &e)
            {
                this->ui->showBookingCanceled();
            }
        }
    }

    void handleException(const std::exception &e)
    {
        std::cout << "[Error]: \"" << e.what() << "\"\n";
    }
};

int main()
{
    App *app = new App();

    Bank *bank = app->getBank();

    bank->deposit(100, 2);
    bank->deposit(50, 2);
    bank->deposit(20, 2);
    bank->deposit(10, 2);
    bank->deposit(5, 2);
    bank->deposit(2, 2);
    bank->deposit(1, 2);

    try
    {
        app->run();
    }
    catch (const std::exception &e)
    {
        app->handleException(e);
    }
}