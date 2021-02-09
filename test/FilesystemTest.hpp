#pragma once

#include <exception>
#include <stdexcept>
#include <iostream>
#include <functional>

#include "TestCase.hpp"
#include "Filesystem.cpp"

class FilesystemTest : public TestCase
{
public:
    std::vector<std::function<void()> > getTests() override
    {
        return {
            [this]() { this->test_getLines(); },
        };
    }

    void test_getLines()
    {
        Filesystem *files = new Filesystem();

        std::vector<std::string> expectedLines = {"foo", "bar"};
        std::vector<std::string> result = files->getLines("test/Fixtures/dummy_db.txt");

        this->makeAssertion((expectedLines == result));
    }
};
