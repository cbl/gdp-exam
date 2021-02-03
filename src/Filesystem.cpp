#include <string>
#include <vector>
#include <fstream>
#include "include/Filesystem.hpp"

namespace fs = std::filesystem;

/*! @copydoc Filesystem::getLines()
 *  
 * Reads the lines fo the file using fstream.
 */
std::vector<std::string> Filesystem::getLines(const std::string &path)
{
    std::string line;
    std::vector<std::string> lines;
    std::ifstream file(path);

    if (!file)
    {
        throw std::runtime_error("Could not get file from path " + path);
    }

    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    return lines;
}