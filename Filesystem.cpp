#include <string>
#include <vector>
#include <fstream>

#include "Filesystem.hpp"

/*! @copydoc Filesystem::getLines()
 *  
 * Reads the lines of the file using fstream.
 */
std::vector<std::string> Filesystem::getLines(const std::string &path)
{
    std::string line;
    std::vector<std::string> lines;
    std::ifstream file(path);

    if (!file)
    {
        throw std::runtime_error("Could not read file with path " + path);
    }

    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    return lines;
}
