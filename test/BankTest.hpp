#pragma once

#include <exception>
#include <stdexcept>
#include <iostream>
#include <functional>

#include "TestCase.hpp"
#include "src/Bank.cpp"

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
        bank->deposit(50, 3);
        bank->deposit(100, 2);
        this->assertIntegerEquals(4, bank->getCoinQuantity(50));
        this->assertIntegerEquals(2, bank->getCoinQuantity(100));
    }

    void test_withdraw()
    {
        Bank *bank = new Bank();
        bank->deposit(50, 3);
        bank->withdraw(50, 2);
        this->assertIntegerEquals(1, bank->getCoinQuantity(50));
    }

    void test_withdraw_fails_when_coins_are_not_available()
    {
        Bank *bank = new Bank();
        this->expectException();
        bank->deposit(50, 3);
        bank->withdraw(50, 4);
    }

    void test_getCoinQuantity_when_no_coins_where_deposited()
    {
        Bank *bank = new Bank();
        this->assertIntegerEquals(0, bank->getCoinQuantity(50));
    }

    void test_getDescendingCoinTypes()
    {
        Bank *bank = new Bank();

        std::array<unsigned int, 7> expectedCoinTypes = {100, 50, 20, 10, 5, 2, 1};

        this->makeAssertion((expectedCoinTypes == bank->getDescendingCoinTypes()));
    }
};