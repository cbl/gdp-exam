#ifndef BANK_H_INCLUDED
#define BANK_H_INCLUDED

#include <iostream>
#include <map>
#include <array>
#include <map>

/**
 * Responsible for managing coins.
 * 
 */
class Bank
{
public:
    enum Coin
    {
        COIN_100,
        COIN_50,
        COIN_20,
        COIN_10,
        COIN_5,
        COIN_2,
        COIN_1,
    };

    /**
     * Returns the value of the given coin.
     * 
     * @param coin The coin whose value is requested.
     * @return unsigned int The value of the coin.
     */
    static unsigned int getCoinValue(const Coin &coin)
    {
        std::map<Coin, unsigned int> values = {
            {Bank::COIN_100, 100},
            {Bank::COIN_50, 50},
            {Bank::COIN_20, 20},
            {Bank::COIN_10, 10},
            {Bank::COIN_5, 5},
            {Bank::COIN_2, 2},
            {Bank::COIN_1, 1},
        };

        return values[coin];
    }

    /**
     * Add the number of specified coins to the wallet.
     * 
     * @param coin The coin type to be added.
     * @param quantity The number of coins to be added.
     */
    void deposit(const Coin &coin, const unsigned int &quantity = 1);

    /**
     * Withdraw the number of given coins to the wallet.
     * 
     * @param coin The coin type to be withdrawn.
     * @param quantity The quantity of coins to be withdrawn.
     * 
     * @throws std::invalid_argument Thrown when the coins to be withdrawn are 
     *      not in the bank.
     */
    void withdraw(const Coin &coin, const unsigned int &quantity = 1);

    /**
     * Get the number of coins of the specified type in the wallet.
     * 
     * @param coin The coin type whose number is to be returned
     * @return unsigned int Number of coins in wallet
     */
    unsigned int getCoinQuantity(const Coin &coin);

    /**
     * Get the existing coin types in descending order.
     * 
     * @return std::array<unsigned int, 7> The array containing the existing 
     *      coin types.
     */
    std::array<Coin, 7> getDescendingCoinTypes();

protected:
    std::map<Coin, unsigned int> wallet;
};

#endif // #ifndef BANK_H_INCLUDED