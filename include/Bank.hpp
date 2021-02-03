#pragma once

#include <map>
#include <array>
#include "Stop.hpp"

class Bank
{
protected:
    std::map<unsigned int, unsigned int> wallet;

public:
    static const unsigned int COIN_100 = 100;
    static const unsigned int COIN_50 = 50;
    static const unsigned int COIN_20 = 20;
    static const unsigned int COIN_10 = 10;
    static const unsigned int COIN_5 = 5;
    static const unsigned int COIN_2 = 2;
    static const unsigned int COIN_1 = 1;

    /**
     * Add the number of specified coins to the wallet.
     * 
     * @param coin The coin type to be added.
     * @param quantity The number of coins to be added.
     */
    void deposit(const unsigned int &coin, const unsigned int &quantity = 1);

    /**
     * Withdraw the number of given coins to the wallet.
     * 
     * @param coin The coin type to be withdrawn.
     * @param quantity The quantity of coins to be withdrawn.
     * 
     * @throws std::invalid_argument Thrown when the coins to be withdrawn are 
     *      not in the bank.
     */
    void withdraw(const unsigned int &coin, const unsigned int &quantity = 1);

    /**
     * Get the number of coins of the specified type in the wallet.
     * 
     * @param coin The coin type whose number is to be returned
     * @return unsigned int Number of coins in wallet
     */
    unsigned int getCoinQuantity(const unsigned int &coin);

    /**
     * Get the existing coin types in descending order.
     * 
     * @return std::array<unsigned int, 7> The array containing the existing 
     *      coin types.
     */
    std::array<unsigned int, 7> getDescendingCoinTypes();
};
