#pragma once

#include <exception>
#include <stdexcept>
#include <iostream>
#include <functional>

#include "TestCase.hpp"
#include "PriceCalculator.cpp"
#include "Bank.hpp"
#include "Stop.hpp"

class PriceCalculatorTest : public TestCase
{
public:
    std::vector<std::function<void()> > getTests() override
    {
        return {
            [this]() { this->test_getPriceFor(); },
            [this]() { this->test_getChange(); },
            [this]() { this->test_getChange_fails_when_not_enough_money_is_in_bank(); },
            [this]() { this->test_getChange_fails_when_the_required_coins_are_not_in_bank(); },
        };
    }

    void test_getPriceFor()
    {
        PriceCalculator *priceCalculator = new PriceCalculator(new Bank(), 10);

        this->assertIntegerEquals(30, priceCalculator->getPriceFor(new Stop("", 3)));
    }

    void test_getChange()
    {
        PriceCalculator *priceCalculator = new PriceCalculator(new Bank(), 10);

        std::map<unsigned int, unsigned int> expectedChange;

        expectedChange = {{100, 2}};
        this->makeAssertion((expectedChange == priceCalculator->getChange(200)));

        expectedChange = {{20, 1}};
        this->makeAssertion((expectedChange == priceCalculator->getChange(20)));

        expectedChange = {{20, 1}};
        this->makeAssertion((expectedChange == priceCalculator->getChange(20)));

        expectedChange = {{100, 1}, {20, 2}};
        this->makeAssertion((expectedChange == priceCalculator->getChange(140)));
    }

    void test_getChange_fails_when_not_enough_money_is_in_bank()
    {
        PriceCalculator *priceCalculator = new PriceCalculator(new Bank(), 10);

        std::map<unsigned int, unsigned int> expectedChange;

        this->expectException();
        priceCalculator->getChange(250);
    }

    void test_getChange_fails_when_the_required_coins_are_not_in_bank()
    {
        PriceCalculator *priceCalculator = new PriceCalculator(new Bank(), 10);

        std::map<unsigned int, unsigned int> expectedChange;

        this->expectException();
        priceCalculator->getChange(1);
    }
};

unsigned int Bank::getCoinQuantity(const unsigned int &coin)
{
    if (coin == 100 || coin == 20)
    {
        return 2;
    }

    return 0;
}

std::array<unsigned int, 7> Bank::getDescendingCoinTypes()
{
    return {
        100,
        50,
        20,
        10,
        5,
        2,
        1,
    };
}

Stop::Stop(std::string name, unsigned int distance)
{
    this->distance = distance;
}

unsigned int Stop::getDistance()
{
    return this->distance;
}