
#pragma once

#include <iostream>
#include <functional>

class TestCase
{
public:
    std::map<std::string, int> run()
    {
        this->result = {
            {"errors", 0},
            {"failures", 0},
            {"succeeded", 0},
            {"assertions", 0},
            {"total", 0}};

        for (const std::function<void()> &test : this->getTests())
        {
            this->result["total"]++;

            const int failures = this->result["failures"];

            try
            {
                test();
            }
            catch (...)
            {
                this->result["errors"]++;
                std::cout << "E";
                continue;
            }

            if (failures != this->result["failures"])
            {
                std::cout << "F";
            }
            else
            {
                this->result["succeeded"]++;
                std::cout << ".";
            }
        }

        return this->result;
    }

    virtual std::vector<std::function<void()>> getTests()
    {
        return {};
    }

protected:
    std::map<std::string, int> result;

    void makeAssertion(const bool &assertion)
    {
        this->result["assertions"]++;

        if (!assertion)
        {
            this->result["failures"]++;
        }
    }

    void assertStringEquals(const std::string &a, const std::string &b)
    {
        this->makeAssertion(a == b);
    }

    void assertIntegerEquals(const int &a, const int &b)
    {
        this->makeAssertion(a == b);
    }
};