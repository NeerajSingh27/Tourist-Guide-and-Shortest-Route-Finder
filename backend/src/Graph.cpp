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
RouteResult Graph::dijkstra(const std::string &source, const std::string &destination) const
{
    RouteResult result;
    if (!hasLocation(source) || !hasLocation(destination))
        return result;
    const int INF = std::numeric_limits<int>::max() / 4;
    std::map<std::string, int> distance;
    std::map<std::string, std::string> previous;
    for (const auto &entry : adjacency_)
        distance[entry.first] = INF;
    using State = std::pair<int, std::string>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> pending;
    distance[source] = 0;
    pending.push({0, source});
    while (!pending.empty())
    {
        const auto current = pending.top();
        pending.pop();
        const int cost = current.first;
        const std::string &node = current.second;
        if (cost != distance[node])
            continue;
        if (node == destination)
            break;
        for (const auto &edge : adjacency_.at(node))
        {
            const std::string &next = edge.first;
            const int weight = edge.second;
            if (cost + weight < distance[next])
            {
                distance[next] = cost + weight;
                previous[next] = node;
                pending.push({distance[next], next});
            }
        }
    }
    if (distance[destination] == INF)
        return result;
    result.found = true;
    result.distance = distance[destination];
    for (std::string at = destination;; at = previous.at(at))
    {
        result.path.push_back(at);
        if (at == source)
            break;
        if (previous.find(at) == previous.end())
        {
            result.path.clear();
            result.found = false;
            return result;
        }
    }
    std::reverse(result.path.begin(), result.path.end());
    return result;
}