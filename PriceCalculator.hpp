#ifndef PRICE_CALCULATOR_H_INCLUDED
#define PRICE_CALCULATOR_H_INCLUDED

#include <string>

#include "Bank.hpp"
#include "Stop.hpp"

/**
 * Responsible for the calculation with monetary amounts.
 * 
 */
class PriceCalculator
{
protected:
    Bank *bank;
    unsigned int pricePerDistance;

public:
    /**
     * Construct a new Price Calculator object.
     * 
     * @param bank 
     * @param pricePerDistance The cost per distance that is used to calucalate 
     *      the ticket price to a stop.
     */
    PriceCalculator(Bank *bank, const unsigned int &pricePerDistance);

    /**
     * Calculate the ticket price for the given stop.
     * 
     * The ticket price is the product of the distance of the stop and the price 
     * per distance.
     * 
     * @param stop The stop whose price is to be calculated.
     * @return unsigned int Ticket price for the give stop.
     */
    unsigned int getPriceFor(Stop *stop);

    /**
     * Gets change for the given stop and the paid amount.
     * 
     * The coin types and number of the associated coin types are returned.
     * 
     * @param changeAmount The total change amount.
     * @return std::map<Bank::Coin, unsigned int> map of coin types and the 
     *      number of the associated coin types.
     */
    std::map<Bank::Coin, unsigned int> getChange(unsigned int changeAmount);
};

#endif // #ifndef PRICE_CALCULATOR_H_INCLUDED