#pragma once

#include <exception>
#include <stdexcept>
#include <iostream>
#include <functional>

#include "TestCase.hpp"
#include "Database.cpp"
#include "Stop.hpp"
#include "StopCollection.hpp"
#include "Filesystem.hpp"

class DatabaseTest : public TestCase
{
public:
    std::vector<std::function<void()> > getTests() override
    {
        return {
            [this]() { this->test_getStops(); },
            [this]() { this->test_getPricePerDistance(); },
        };
    }

    void test_getStops()
    {
        Database *db = new Database(new Filesystem(), "foo");
        StopCollection *stops = db->getStops();

        this->assertStringEquals("Foo", stops->getStops().at(0)->getName());
        this->assertIntegerEquals(4, stops->getStops().at(0)->getDistance());
        this->assertStringEquals("Bar", stops->getStops().at(1)->getName());
        this->assertIntegerEquals(3, stops->getStops().at(1)->getDistance());
    }

    void test_getPricePerDistance()
    {
        Database *db = new Database(new Filesystem(), "foo");

        this->assertIntegerEquals(15, db->getPricePerDistance());
    }
};

std::vector<std::string> Filesystem::getLines(const std::string &path)
{
    return {
        "15",
        "2",
        "Foo",
        "4",
        "Bar",
        "3",
    };
}

StopCollection::StopCollection(std::vector<Stop *> stops)
{
    this->stops = stops;
}

std::vector<Stop *> StopCollection::getStops()
{
    return this->stops;
}

Stop::Stop(std::string name, unsigned int distance)
{
    this->name = name;
    this->distance = distance;
};

std::string Stop::getName()
{
    return this->name;
}

unsigned int Stop::getDistance()
{
    return this->distance;
}