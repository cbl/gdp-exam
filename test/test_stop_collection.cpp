#include "TestSuit.hpp"
#include "StopCollectionTest.hpp"

int main()
{
    TestSuit *test = new TestSuit(
        "StopCollection",
        {
            new StopCollectionTest(),
        });

    test->run();
}