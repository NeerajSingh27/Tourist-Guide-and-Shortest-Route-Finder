#include "FileHandler.h"
#include "HttpUtils.h"
#include <fstream>
#include <sstream>
#include <vector>
namespace fs = std::filesystem;
std::string FileHandler::readAll(const fs::path &path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file)
        return {};
    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}
Graph FileHandler::loadRoadGraph(const fs::path &path)
{
    Graph graph;
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line))
    {
        line = HttpUtils::trim(line);
        if (line.empty() || line[0] == '#')
            continue;
        std::stringstream row(line);
        std::string from, to, rawDistance;
        if (!std::getline(row, from, '|') || !std::getline(row, to, '|') || !std::getline(row, rawDistance))
            continue;
        try
        {
            graph.addEdge(HttpUtils::trim(from), HttpUtils::trim(to), std::stoi(HttpUtils::trim(rawDistance)));
        }
        catch (...)
        { /* Ignore malformed sample records instead of stopping server startup. */
        }
    }
    return graph;
}