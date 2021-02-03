#include "include/Stop.hpp"

Stop::Stop(std::string name, unsigned int distance)
{
    this->name = name;
    this->distance = distance;
};

std::string Stop::getName()
{
    return this->name;
}

unsigned int Stop::getDistance()
{
    return this->distance;
}