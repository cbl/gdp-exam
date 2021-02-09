#include <stdexcept>

#include "Stop.hpp"
#include "StopCollection.hpp"

/*! @copydoc StopCollection::StopCollection()
 *
 */
StopCollection::StopCollection(std::vector<Stop *> stops)
{
    this->stops = stops;
}

/*! @copydoc StopCollection::getStops()
 *
 */
std::vector<Stop *> StopCollection::getStops()
{
    return this->stops;
}

/*! @copydoc StopCollection::findFirst()
 *
 */
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

/*! @copydoc StopCollection::forEach()
 *
 */
void StopCollection::forEach(std::function<void(Stop *)> handler)
{
    for (const auto &stop : this->stops)
    {
        handler(stop);
    }
}