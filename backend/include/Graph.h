#pragma once
#include <map>
#include <string>
#include <utility>
#include <vector>
struct RouteResult
{
    bool found{false};
    int distance{0};
    std::vector<std::string> path;
};
class Graph
{
private:
    std::map<std::string, std::vector<std::pair<std::string, int>>> adjacency_;

public:

};