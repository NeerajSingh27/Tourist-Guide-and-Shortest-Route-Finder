#include "Graph.h"
#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
bool Graph::addEdge(const std::string &from, const std::string &to, int distance)
{
    if (from.empty() || to.empty() || distance < 0)
        return false;
    adjacency_[from].push_back({to, distance});
    adjacency_[to].push_back({from, distance});
    return true;
}
bool Graph::hasLocation(const std::string &name) const { return adjacency_.find(name) != adjacency_.end(); }
std::vector<std::string> Graph::locations() const
{
    std::vector<std::string> result;
    for (const auto &entry : adjacency_)
        result.push_back(entry.first);
    return result;
}