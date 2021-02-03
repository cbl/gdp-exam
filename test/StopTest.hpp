#pragma once

#include <exception>
#include <stdexcept>
#include <iostream>
#include <functional>

#include "TestCase.hpp"
#include "src/Stop.cpp"

class StopTest : public TestCase
{
public:
    std::vector<std::function<void()>> getTests() override
    {
        return {
            [this]() { this->test_getName_method_returns_name(); },
            [this]() { this->test_getDistance_method_returns_distance(); }};
    }

    void test_getName_method_returns_name()
    {
        Stop *stop = new Stop("foo", 5);
        this->assertStringEquals("foo", stop->getName());
    }

    void test_getDistance_method_returns_distance()
    {
        Stop *stop = new Stop("foo", 5);
        this->assertIntegerEquals(5, stop->getDistance());
    }
};