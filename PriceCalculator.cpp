#include "Stop.hpp"
#include "PriceCalculator.hpp"

/*! @copydoc PriceCalculator::PriceCalculator()
 *
 */
PriceCalculator::PriceCalculator(Bank *bank, const unsigned int &pricePerDistance)
{
    this->bank = bank;
    this->pricePerDistance = pricePerDistance;
};

/*! @copydoc PriceCalculator::getPriceFor()
 *
 */
unsigned int PriceCalculator::getPriceFor(Stop *stop)
{
    return this->pricePerDistance * stop->getDistance();
};

/**! @copydoc PriceCalculator::getChange()
 * 
 * The change is calculated as the smallest possible number of coins based on 
 * the number of coins in the bank.
 */
std::map<unsigned int, unsigned int> PriceCalculator::getChange(unsigned int changeAmount)
{
    const std::array<unsigned int, 7> &coinTypes = this->bank->getDescendingCoinTypes();
    std::map<unsigned int, unsigned int> change;

    for (int i = 0; i < 7; i++)
    {
        unsigned int coin = coinTypes.at(i);
        unsigned int quantity = this->bank->getCoinQuantity(coin);

        while (coin <= changeAmount)
        {
            if (change[coin] >= quantity)
            {
                break;
            }

            if (change.find(coin) == change.end())
            {
                change[coin] = 0;
            }

            change[coin]++;
            changeAmount -= coin;
        }
    }

    if (changeAmount > 0)
    {
        throw std::invalid_argument("Not enough change.");
    }

    return change;
};
