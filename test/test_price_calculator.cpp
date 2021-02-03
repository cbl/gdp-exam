#include "TestSuit.hpp"
#include "PriceCalculatorTest.hpp"

int main()
{
    TestSuit *test = new TestSuit(
        "PriceCalculator",
        {
            new PriceCalculatorTest(),
        });

    test->run();
}