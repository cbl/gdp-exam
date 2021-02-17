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

        std::map<Bank::Coin, unsigned int> expectedChange;

        expectedChange = {{Bank::COIN_100, 2}};
        this->makeAssertion((expectedChange == priceCalculator->getChange(200)));

        expectedChange = {{Bank::COIN_20, 1}};
        this->makeAssertion((expectedChange == priceCalculator->getChange(20)));

        expectedChange = {{Bank::COIN_20, 1}};
        this->makeAssertion((expectedChange == priceCalculator->getChange(20)));

        expectedChange = {{Bank::COIN_100, 1}, {Bank::COIN_20, 2}};
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

unsigned int Bank::getCoinQuantity(const Bank::Coin &coin)
{
    if (coin == Bank::COIN_100 || coin == Bank::COIN_20)
    {
        return 2;
    }

    return 0;
}

std::array<Bank::Coin, 7> Bank::getDescendingCoinTypes()
{
    return {Bank::COIN_100, Bank::COIN_50, Bank::COIN_20, Bank::COIN_10, Bank::COIN_5, Bank::COIN_2, Bank::COIN_1};
}

Stop::Stop(std::string name, unsigned int distance)
{
    this->distance = distance;
}

unsigned int Stop::getDistance()
{
    return this->distance;
}