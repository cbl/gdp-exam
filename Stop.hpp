#pragma once

#include <string>

class Stop
{
protected:
    std::string name;
    unsigned int distance;

public:
    /**
     * Construct a new Stop object.
     * 
     * @param name The name of the stop.
     * @param distance The distance from the current location to the stop.
     */
    Stop(std::string name, unsigned int distance);

    /**
     * Get the name of the stop.
     * 
     * @return std::string Name of the stop.
     */
    std::string getName();

    /**
     * Get the distance to the stop.
     * 
     * @return unsigned int The distance from the current location to the stop.
     */
    unsigned int getDistance();
};
