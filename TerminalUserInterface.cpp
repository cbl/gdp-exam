#include <map>
#include <iostream>

#include "Stop.hpp"
#include "UserInterface.hpp"

/**
 * Clear's cin error state on failure.
 * 
 * @return void
 */
void clearInputOnFailure()
{
    if (!std::cin.fail())
    {
        return;
    }

    // clear error state
    std::cin.clear();
    // discard 'bad' character(s)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string UserInterface::getStringInput()
{
    std::string input;
    std::cout << "> ";
    std::cin >> input;

    clearInputOnFailure();

    return input;
}

char UserInterface::getCharInput()
{
    char input;
    std::cout << "> ";
    std::cin >> input;

    clearInputOnFailure();

    return input;
}

int UserInterface::getIntegerInput()
{
    int input;
    std::cout << "> ";
    std::cin >> input;

    clearInputOnFailure();

    return input;
}

void UserInterface::showAllStops(StopCollection *stops)
{
    std::cout << "Mögliche Zielhaltestellen:" << std::endl;

    stops->forEach([](Stop *stop) {
        std::cout << "- " << stop->getName() << std::endl;
    });
}

void UserInterface::showBookingStart()
{
    std::cout << "======= Ticket Buchung =======" << std::endl;
}

void UserInterface::showBookingCanceled()
{
    std::cout << "Buchungsvorgang abgebrochen." << std::endl;
}

void UserInterface::showDestinationSelected(Stop *destination)
{
    std::cout << "Ihre gewünschte Zielhaltestelle ist " << destination->getName() << "." << std::endl;
}

void UserInterface::showDestinationNotFoundAndRetry(std::string name)
{
    std::cout << "Keine Haltestelle mit dem namen '" << name << "' vorhanden, versuchen Sie es erneut:" << std::endl;
}

void UserInterface::showDestinationPrice(const unsigned int &price)
{
    std::cout << "der Preis dafür beträgt " << price << " Geld." << std::endl;
}

void UserInterface::showPayment(const unsigned int &price, const unsigned int &paid)
{
    std::cout << "Sie bezahlen " << paid << " Geld." << std::endl;
    std::cout << "Sie bekommen " << paid - price << " Geld zurück." << std::endl;
}

void UserInterface::showChange(const std::map<Bank::Coin, unsigned int> change)
{
    if (change.empty())
    {
        return;
    }

    std::cout
        << "Rückgeld: " << std::endl;

    for (auto const &[coin, quantity] : change)
    {
        std::cout << "- " << quantity << "x " << Bank::getCoinValue(coin) << std::endl;
    }
}

void UserInterface::showTicket(Stop *destination, const unsigned int &price)
{
    std::cout << std::endl
              << "------------------" << std::endl;
    std::cout << "----- Ticket -----" << std::endl;
    std::cout << "-" << std::endl;
    std::cout << "- Nach:  " << destination->getName() << std::endl;
    std::cout << "- Preis: " << price << std::endl;
    std::cout << "-" << std::endl;
    std::cout << "------------------" << std::endl
              << std::endl;
}

void UserInterface::askForDestination()
{
    std::cout << "Bitte geben Sie den Namen der Zielhaltestelle ein:" << std::endl;
}

void UserInterface::askForPayment(const unsigned int &price)
{
    std::cout << "Bezahlen Sie " << price << " oder mehr:" << std::endl;
}

void UserInterface::showInvalidAmounPaidAndAskForRetry()
{
    std::cout << "Sie haben einen ungültigen Betrag eingebeben." << std::endl;
    std::cout << "Möchten Sie den Vorgang abbrechen oder erneut einen Betrag eingeben?" << std::endl;
}

void UserInterface::showGiveChangeNotPossibleAndAskForRetry()
{
    std::cout << "Rückgeldausgabe nicht möglich, möchten Sie es mit einem anderen Betrag versuchen?" << std::endl;
}

void UserInterface::askForCancel()
{
    std::cout << "Vorgang abbrechen: j: Ja, n: Nein" << std::endl;
}