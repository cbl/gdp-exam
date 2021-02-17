#pragma once

#include <exception>
#include <stdexcept>
#include <iostream>
#include <functional>

#include "TestCase.hpp"
#include "Bank.cpp"

class AppIntegrationTest : public TestCase
{
public:
    std::vector<std::function<void()> > getTests() override
    {
        return {
            [this]() { this->test_deposit(); },
            [this]() { this->test_withdraw(); },
            [this]() { this->test_withdraw_fails_when_coins_are_not_available(); },
            [this]() { this->test_getCoinQuantity_when_no_coins_where_deposited(); },
            [this]() { this->test_getDescendingCoinTypes(); },
        };
    }

    void test_deposit()
    {
        Bank *bank = new Bank();
        bank->deposit(Bank::COIN_50, 3);
        bank->deposit(Bank::COIN_100, 2);
        this->assertIntegerEquals(3, bank->getCoinQuantity(Bank::COIN_50));
        this->assertIntegerEquals(2, bank->getCoinQuantity(Bank::COIN_100));
    }
};