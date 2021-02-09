#pragma once

#include <exception>
#include <stdexcept>
#include <iostream>
#include <functional>

#include "TestCase.hpp"
#include "StopCollection.cpp"
#include "Stop.hpp"

class StopCollectionTest : public TestCase
{
public:
    std::vector<std::function<void()> > getTests() override
    {
        return {
            [this]() { this->test_findFirst(); },
            [this]() { this->test_findFirst_fails_when_nothing_is_found(); },
        };
    }

    void test_findFirst()
    {
        Stop *found;
        Stop *foo = new Stop("Foo", 3);
        Stop *bar = new Stop("Bar", 3);

        StopCollection *stops = new StopCollection({
            foo,
            bar,
        });

        found = stops->findFirst([](Stop *stop) -> bool {
            return stop->getName() == "Foo";
        });
        this->makeAssertion((foo == found));

        found = stops->findFirst([](Stop *stop) -> bool {
            return stop->getName() == "Bar";
        });
        this->makeAssertion((bar == found));
    }

    void test_findFirst_fails_when_nothing_is_found()
    {
        Stop *foo = new Stop("Foo", 3);
        Stop *bar = new Stop("Bar", 3);

        StopCollection *stops = new StopCollection({
            foo,
            bar,
        });

        this->expectException();

        stops->findFirst([](Stop *stop) -> bool {
            return false;
        });
    }
};
Stop::Stop(std::string name, unsigned int distance)
{
    this->name = name;
}

std::string Stop::getName()
{
    return this->name;
}