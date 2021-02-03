#include "include/Database.hpp"
#include "include/Stop.hpp"
#include "include/StopCollection.hpp"
#include "include/Filesystem.hpp"

Database::Database(Filesystem *files, const std::string path)
{
    this->files = files;
    this->path = path;
};

StopCollection *Database::getStops()
{
    std::vector<Stop *> stops;
    std::vector<std::string> lines = this->getLines();

    for (unsigned int i = 2; i < lines.size(); i += 2)
    {
        std::string name = lines.at(i);
        unsigned int pricePerDistance = std::stoi(lines.at(i + 1));
        stops.push_back(new Stop(name, pricePerDistance));
    }

    return new StopCollection(stops);
}

std::vector<std::string> Database::getLines()
{
    if (!this->lines.empty())
    {
        return this->lines;
    }

    return this->lines = this->files->getLines(this->path);
}

unsigned int Database::getPricePerDistance()
{
    return std::stoi(this->getLines().at(1));
}
