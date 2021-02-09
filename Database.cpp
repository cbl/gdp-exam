#include "Database.hpp"
#include "Stop.hpp"
#include "StopCollection.hpp"
#include "Filesystem.hpp"

/*! @copydoc Database::Database()
 *
 */
Database::Database(Filesystem *files, const std::string path)
{
    this->files = files;
    this->path = path;
};

/*! @copydoc Database::getStops()
 *
 */
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

/*! @copydoc Database::getLines()
 *
 */
std::vector<std::string> Database::getLines()
{
    if (!this->lines.empty())
    {
        return this->lines;
    }

    return this->lines = this->files->getLines(this->path);
}

/*! @copydoc Database::getPricePerDistance()
 *
 */
unsigned int Database::getPricePerDistance()
{
    return std::stoi(this->getLines().at(0));
}
