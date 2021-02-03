
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <filesystem>

#include "TestCase.hpp"
#include "StopTest.hpp"
#include "BankTest.hpp"

class TestSuit
{
public:
    TestSuit(std::vector<TestCase *> cases)
    {
        this->cases = cases;
    }

    void run()
    {
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
            std::cout << "FAILED!" << std::endl;
        }

        std::cout << "Tests: " << endResult["total"] << ", ";
        std::cout << "Assertions: " << endResult["assertions"] << ", ";
        std::cout << "Failures: " << endResult["failures"] << ", ";
        std::cout << "Erros: " << endResult["errors"] << ", ";
        std::cout << "Succeeded: " << endResult["succeeded"] << std::endl;
    }

protected:
    std::vector<TestCase *> cases;

    bool succeeded(std::map<std::string, int> result)
    {
        return result["total"] == result["succeeded"];
    }
};

int main()
{
    TestSuit *test = new TestSuit({new BankTest(), new StopTest()});

    test->run();
}