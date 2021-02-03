#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "TestCase.hpp"

class TestSuit
{
public:
    TestSuit(std::string name, std::vector<TestCase *> cases)
    {
        this->name = name;
        this->cases = cases;
    }

    void run()
    {
        std::cout << "= TestSuite(" << this->name << ") =" << std::endl;
        std::cout << "Starting " << this->cases.size() << " Test Cases:" << std::endl
                  << std::endl;

        std::map<std::string, int> endResult = {
            {"total", 0},
            {"assertions", 0},
            {"errors", 0},
            {"failures", 0},
            {"succeeded", 0},
        };

        for (const auto &test : this->cases)
        {
            std::map<std::string, int> result = test->run();

            for (auto const &[key, value] : result)
            {
                endResult[key] += value;
            }
        }

        std::cout << std::endl
                  << std::endl;

        if (this->succeeded(endResult))
        {
            std::cout << "SUCCEEDED!" << std::endl;
        }
        else
        {
            std::cerr << "FAILED!" << std::endl;
        }

        std::cout << "Tests: " << endResult["total"] << ", ";
        std::cout << "Assertions: " << endResult["assertions"] << ", ";
        std::cout << "Failures: " << endResult["failures"] << ", ";
        std::cout << "Erros: " << endResult["errors"] << ", ";
        std::cout << "Succeeded: " << endResult["succeeded"] << std::endl
                  << std::endl;
    }

protected:
    std::string name;
    std::vector<TestCase *> cases;

    bool succeeded(std::map<std::string, int> result)
    {
        return result["total"] == result["succeeded"];
    }
};
