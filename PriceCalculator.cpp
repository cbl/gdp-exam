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
std::map<Bank::Coin, unsigned int> PriceCalculator::getChange(unsigned int changeAmount)
{
    const std::array<Bank::Coin, 7> &coinTypes = this->bank->getDescendingCoinTypes();
    std::map<Bank::Coin, unsigned int> change;

    for (int i = 0; i < 7; i++)
    {
        Bank::Coin coin = coinTypes.at(i);
        unsigned int value = Bank::getCoinValue(coin);
        unsigned int quantity = this->bank->getCoinQuantity(coin);

        while (value <= changeAmount)
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
            changeAmount -= value;
        }
    }

    if (changeAmount > 0)
    {
        throw std::invalid_argument("Not enough change.");
    }

    return change;
};
