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
    std::vector<std::function<void()>> getTests() override
    {
        return {
            [this]() { this->test_deposit(); },
            [this]() { this->test_withdraw(); }};
    }

    void test_deposit()
    {
        Bank *bank = new Bank();
        bank->deposit(50, 3);
        this->assertIntegerEquals(3, bank->getCoinQuantity(50));
    }

    void test_withdraw()
    {
        Bank *bank = new Bank();
        bank->deposit(50, 3);
        bank->withdraw(50, 2);
        this->assertIntegerEquals(1, bank->getCoinQuantity(50));
    }
};