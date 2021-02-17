#pragma once

#include <exception>
#include <stdexcept>
#include <iostream>
#include <functional>

#include "TestCase.hpp"
#include "Bank.cpp"

class BankTest : public TestCase
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

    void test_withdraw()
    {
        Bank *bank = new Bank();
        bank->deposit(Bank::COIN_50, 3);
        bank->withdraw(Bank::COIN_50, 2);
        this->assertIntegerEquals(1, bank->getCoinQuantity(Bank::COIN_50));
    }

    void test_withdraw_fails_when_coins_are_not_available()
    {
        Bank *bank = new Bank();
        this->expectException();
        bank->deposit(Bank::COIN_50, 3);
        bank->withdraw(Bank::COIN_50, 4);
    }

    void test_getCoinQuantity_when_no_coins_where_deposited()
    {
        Bank *bank = new Bank();
        this->assertIntegerEquals(0, bank->getCoinQuantity(Bank::COIN_50));
    }

    void test_getDescendingCoinTypes()
    {
        Bank *bank = new Bank();

        std::array<Bank::Coin, 7> expectedCoinTypes = {Bank::COIN_100, Bank::COIN_50, Bank::COIN_20, Bank::COIN_10, Bank::COIN_5, Bank::COIN_2, Bank::COIN_1};

        this->makeAssertion((expectedCoinTypes == bank->getDescendingCoinTypes()));
    }
};