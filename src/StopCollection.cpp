#include <stdexcept>
#include "include/Stop.hpp"
#include "include/StopCollection.hpp"

StopCollection::StopCollection(std::vector<Stop *> stops)
{
    this->stops = stops;
}

Stop *StopCollection::findFirst(std::function<bool(Stop *)> finder)
{
    for (const auto &stop : this->stops)
    {
        if (finder(stop))
        {
            return stop;
        }
    }

    throw new std::invalid_argument("No stop found.");
}

void StopCollection::forEach(std::function<void(Stop *)> handler)
{
    for (const auto &stop : this->stops)
    {
        handler(stop);
    }
}