#pragma once

#include <string>
#include <vector>
#include "Filesystem.hpp"
#include "Stop.hpp"
#include "StopCollection.hpp"

class Database
{
protected:
    Filesystem *files;
    std::string path;
    std::vector<std::string> lines;

    std::vector<std::string> getLines();

public:
    Database(Filesystem *files, const std::string path);

    /**
     * Get the Stops.
     * 
     * @return StopCollection* The StopCollection instance containing all stops.
     */
    StopCollection *getStops();

    /**
     * Get the price per distance.
     * 
     * @return unsigned int The price per distance.
     */
    unsigned int getPricePerDistance();
};