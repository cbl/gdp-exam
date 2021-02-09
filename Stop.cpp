#include "Stop.hpp"

/*! @copydoc Stop::Stop()
 *
 */
Stop::Stop(std::string name, unsigned int distance)
{
    this->name = name;
    this->distance = distance;
};

/*! @copydoc Stop::getName()
 *
 */
std::string Stop::getName()
{
    return this->name;
}

/*! @copydoc Stop::getDistance()
 *
 */
unsigned int Stop::getDistance()
{
    return this->distance;
}