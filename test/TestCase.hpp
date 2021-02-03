
#pragma once

#include <iostream>
#include <functional>

class TestCase
{
public:
    /**
     * Run all tests in the test case and return the result.
     * 
     * @return std::map<std::string, int> The result of the test case run.
     */
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

            this->exceptionExpected = false;

            try
            {
                test();
            }
            catch (...)
            {
                this->handleException(std::current_exception());

                if (!this->exceptionExpected)
                {
                    this->result["errors"]++;
                    std::cerr << "E";
                    continue;
                }
                else
                {
                    this->makeAssertion(this->exceptionExpected);
                    this->exceptionExpected = false;
                }
            }

            if (this->exceptionExpected)
            {
                this->makeAssertion(false);
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

    /**
     * Get all test cases.
     * 
     * @return std::vector<std::function<void()>> Vector containing anonymous 
     *      functions that run all test cases.
     */
    virtual std::vector<std::function<void()>> getTests()
    {
        return {};
    }

protected:
    std::map<std::string, int> result;
    bool exceptionExpected = false;

    /**
     * Make an assertion.
     * 
     * @param assertion 
     */
    void makeAssertion(const bool &assertion)
    {
        this->result["assertions"]++;

        if (!assertion)
        {
            this->result["failures"]++;
        }
    }

    /**
     * Expect an exception.
     * 
     */
    void expectException()
    {
        this->exceptionExpected = true;
    }

    /**
     * Assert that the given strings are equal.
     * 
     * @param a 
     * @param b 
     */
    void assertStringEquals(const std::string &a, const std::string &b)
    {
        this->makeAssertion(a == b);
    }

    /**
     * Assert that the given string ends with the given suffix.
     * 
     * @param str
     * @param suffix
     */
    void assertStringEndsWith(const std::string &str, const std::string &suffix)
    {
        this->makeAssertion(
            (str.size() >= suffix.size() &&
             str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0));
    }

    /**
     * Asset that the given integers are equal.
     * 
     * @param a 
     * @param b 
     */
    void assertIntegerEquals(const int &a, const int &b)
    {
        this->makeAssertion(a == b);
    }

private:
    void handleException(std::exception_ptr eptr)
    {
        //
    }
};