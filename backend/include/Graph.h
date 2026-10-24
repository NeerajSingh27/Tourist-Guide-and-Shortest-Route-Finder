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
    bool addEdge(const std::string &from, const std::string &to, int distance);
    bool hasLocation(const std::string &name) const;
    std::vector<std::string> locations() const;
    RouteResult dijkstra(const std::string &source, const std::string &destination) const;
};