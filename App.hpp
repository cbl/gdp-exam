#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include "Stop.hpp"
#include "StopCollection.hpp"
#include "Database.hpp"
#include "Filesystem.hpp"
#include "PriceCalculator.hpp"
#include "UserInterface.hpp"

struct CanceledException : public std::exception
{
    const char *what() const throw()
    {
        return "Process canceled.";
    }
};

/**
 * Defines the business logic of ticket booking.
 * 
 */
class App final
{
protected:
    Filesystem *files;
    Database *db;
    Bank *bank;
    PriceCalculator *priceCalculator;
    StopCollection *stops;
    UserInterface *ui;

public:
    /**
     * Construct a new App object.
     * 
     */
    App()
    {
        const std::string dbPath = "db.txt";

        this->files = new Filesystem();
        this->db = new Database(files, dbPath);
        this->bank = new Bank();
        this->priceCalculator = new PriceCalculator(bank, db->getPricePerDistance());
        this->stops = db->getStops();

        this->fillBankWithMoney();
    }

    /**
     * Handle ticket booking.
     * 
     * Handling ticket booking includes:
     * - All available stops are displayed.
     * - The user is asked to enter a destination.
     * - The selected destination is displayed.
     * - The price for the destination is calculated.
     * - The calculated ticket price is displayed.
     * - The user is asked to pay.
     * - The ticket is printed.
     * - The calculated change is given to the user.
     */
    void booking()
    {
        Stop *destination;
        unsigned int price;
        std::map<Bank::Coin, unsigned int> change;

        this->ui->showBookingStart();
        this->ui->showAllStops(this->stops);

        // Get destination.
        destination = this->askForDestination();
        this->ui->showDestinationSelected(destination);

        // Get destination price.
        price = this->priceCalculator->getPriceFor(destination);
        this->ui->showDestinationPrice(price);

        // Payment.
        change = this->payment(price);

        this->printTicket(destination, price);
        this->giveChange(change);
    }

    /**
     * Run the 
     * 
     */
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

    /**
     * Handle the given exception.
     * 
     * Logs the exception message to the console.
     * 
     * @param e The exception that is to be handled.
     */
    void handleException(const std::exception &e)
    {
        std::cout << "[Error]: \"" << e.what() << "\"\n";
    }

private:
    /**
     * Print the ticket to the given destination and the price.
     * 
     * The ticket contains the destination name and the price.
     * 
     * @param destination The ticket's destination.
     * @param price The ticket price.
     */
    void printTicket(Stop *destination, const unsigned int &price)
    {
        this->ui->showTicket(destination, price);
    }

    /**
     * Ask the user to pay the given price.
     * 
     * The returned price is validated.
     * 
     * @param price The price that is to be payed.
     * @return unsigned int The price payed by the user.
     */
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

            this->ui->showInvalidAmounPaidAndAskForRetry();

            this->askForCancel();
        }
    }

    /**
     * Handle payment for the given price.
     * 
     * Handling payment includes:
     * - Asking the user to pay the price.
     * - Calculating the change when the payed amount is greater than the price.
     * - Give the user the option to cancel or retry payment when there's not 
     *   enough change.
     * 
     * @param price The price that is to be payed.
     * @return std::map<Bank::Coin, unsigned int> The calculated change for to 
     *      repay the excess amount of money.
     */
    std::map<Bank::Coin, unsigned int> payment(const unsigned int &price)
    {
        std::map<Bank::Coin, unsigned int> change;
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

    /**
     * Cancel the booking process.
     * 
     * @throws CanceledException
     */
    void cancel()
    {
        throw CanceledException();
    }

    /**
     * Ask the user whether he wants to cancel the booking process.
     * 
     * @throws CanceledException
     */
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

    /**
     * Give the given change to the user.
     * 
     * First the changen will be withdrawn from the bank, then it will be shown 
     * on the user interface.
     * 
     * @param change The change the is to be given.
     */
    void giveChange(const std::map<Bank::Coin, unsigned int> &change)
    {
        for (auto const &[coin, quantity] : change)
        {
            bank->withdraw(coin, quantity);
        }

        this->ui->showChange(change);
    }

    /**
     * Ask the user to enter a destination name.
     * 
     * @return Stop* 
     */
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

    /**
     * Determines whether the payment input value is valid.
     * 
     * A payment input is valid when:
     * - it is greater than the price that is to be payed
     * - it is in the range of unsigned integers
     * 
     * @param price The price input that is to be payed.
     * @param amount The payment input amount that was payed.
     * @return bool
     */
    bool isValidPaymentInput(const unsigned int &price, const int &amount)
    {
        unsigned int max = -1;

        return price <= amount && amount < max;
    }

    /**
     * Fills bank with 2x of each available coin.
     * 
     * @return void
     */
    void fillBankWithMoney()
    {
        this->bank->deposit(Bank::COIN_100, 2);
        this->bank->deposit(Bank::COIN_50, 2);
        this->bank->deposit(Bank::COIN_20, 2);
        this->bank->deposit(Bank::COIN_10, 2);
        this->bank->deposit(Bank::COIN_5, 2);
        this->bank->deposit(Bank::COIN_2, 2);
        this->bank->deposit(Bank::COIN_1, 2);
    }
};

#endif // #ifndef APP_H_INCLUDED