#include "Bank.hpp"
#include "Stop.hpp"
#include "Filesystem.hpp"

/*! @copydoc Bank::deposit()
 *
 */
void Bank::deposit(const unsigned int &coin, const unsigned int &quantity)
{
    if (this->wallet.find(coin) == this->wallet.end())
    {
        this->wallet[coin] = 0;
    }

    this->wallet[coin] += quantity;
};

/*! @copydoc Bank::withdraw()
 *
 */
void Bank::withdraw(const unsigned int &coin, const unsigned int &quantity)
{
    if (this->wallet.find(coin) == this->wallet.end())
    {
        this->wallet[coin] = 0;
    }

    int newQuantity = this->wallet[coin] - quantity;

    if (newQuantity < 0)
    {
        throw std::invalid_argument("Not enough credit.");
    }

    this->wallet[coin] = newQuantity;
};

/*! @copydoc Bank::getCoinQuantity()
 *
 */
unsigned int Bank::getCoinQuantity(const unsigned int &coin)
{
    if (this->wallet.find(coin) == this->wallet.end())
    {
        return 0;
    }

    return this->wallet[coin];
};

/*! @copydoc Bank::getDescendingCoinTypes()
 *
 */
std::array<unsigned int, 7> Bank::getDescendingCoinTypes()
{
    return {
        Bank::COIN_100,
        Bank::COIN_50,
        Bank::COIN_20,
        Bank::COIN_10,
        Bank::COIN_5,
        Bank::COIN_2,
        Bank::COIN_1,
    };
};