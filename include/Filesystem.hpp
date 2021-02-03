#pragma once

#include <string>
#include <vector>

class Filesystem
{
public:
    /**
     * Outputs a vector containing all lines of the file located at the 
     * specified file path.
     * 
     * @param path The absolute path to the file to be read.
     * @return Lines of the file.
     * 
     * @throws std::runtime_error Thrown if file at `path` could not be read.
     */
    std::vector<std::string> getLines(const std::string &path);
};