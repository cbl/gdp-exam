
#include "App.hpp"

int main()
{
    App *app = new App();

    try
    {
        app->run();
    }
    catch (const std::exception &e)
    {
        app->handleException(e);

        return 1;
    }

    return 0;
}