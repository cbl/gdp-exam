#include "TestSuit.hpp"
#include "DatabaseTest.hpp"

int main()
{
    TestSuit *test = new TestSuit(
        "Database",
        {
            new DatabaseTest(),
        });

    test->run();
}