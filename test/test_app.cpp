#include "AppIntegrationTest.hpp"

int main()
{
    TestSuit *test = new TestSuit(
        "App",
        {
            new AppIntegrationTest(),
        });

    return test->run();
}