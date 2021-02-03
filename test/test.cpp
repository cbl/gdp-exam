#include "TestSuit.hpp"
#include "StopTest.hpp"
#include "FilesystemTest.hpp"
#include "BankTest.hpp"

int main()
{
    TestSuit *test = new TestSuit(
        "Bank, Filesystem, Stop",
        {
            new BankTest(),
            new FilesystemTest(),
            new StopTest(),
        });

    return test->run();
}