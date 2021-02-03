#pragma once

#include <string>
#include <map>
#include "Stop.hpp"
#include "StopCollection.hpp"

class UserInterface
{
public:
    /**
     * Get a string from user input.
     * 
     * @return std::string The user input value.
     */
    std::string getStringInput();

    /**
     * Get a char from user input.
     * 
     * @return char The user input value.
     */
    char getCharInput();

    /**
     * Get an integer from user input.
     * 
     * @return int The user input value.
     */
    int getIntegerInput();

    /**
     * Display the booking start.
     * 
     */
    void showAllStops(StopCollection *stops);

    /**
     * Display the booking start.
     * 
     */
    void showBookingStart();

    /**
     * Display that the booking was canceled.
     * 
     */
    void showBookingCanceled();

    /**
     * Show the destination that was selected.
     * 
     * @param destination The selcted destination.
     */
    void showDestinationSelected(Stop *destination);

    /**
     * Show that the destination was not found and ask the user to retry.
     * 
     * @param name The name that was searched for.
     */
    void showDestinationNotFoundAndRetry(std::string name);

    /**
     * Display the price of a given destination.
     * 
     * @param price The price to be displayed.
     */
    void showDestinationPrice(const unsigned int &price);

    /**
     * Show the price to be paid and the amount that was paid.
     * 
     * @param price The ticket price.
     * @param paid The price that was paid.
     */
    void showPayment(const unsigned int &price, const unsigned int &paid);

    /**
     * Display the ticket to the destination.
     * 
     * The ticket contains the destination name and the ticket price.
     * 
     * @param destination The destination stop object.
     * @param price The ticket price.
     */
    void showTicket(Stop *destination, const unsigned int &price);

    /**
     * Display the change that the user gets back.
     * 
     * @param change A map contaning all coin types and the number of the 
     *      associated coin types that the user gets back.
     */
    void showChange(const std::map<unsigned int, unsigned int> change);

    /**
     * Ask the user to enter the desired destination.
     * 
     */
    void askForDestination();

    /**
     * Ask the user to pay.
     * 
     * @param price The ticket price that is to be paid.
     */
    void askForPayment(const unsigned int &price);

    /**
     * Ask wether the user wants to cancel or continue.
     * 
     */
    void askForCancel();

    /**
     * Display that an invalid amount was paid and ask the user wether he wants 
     * to cancel or retry payment.
     * 
     */
    void showInvalidAmounPaidAndAskForRetry();

    /**
     * Display that giving change for the paid amount is not possible and aks 
     * wheter the user wants to cancel or retry.
     * 
     */
    void showGiveChangeNotPossibleAndAskForRetry();
};
