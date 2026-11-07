#pragma once
#include "Graph.h"
#include <filesystem>
#include <string>
class HttpServer {
private:
    std::filesystem::path root_;
    std::filesystem::path webRoot_;
    std::filesystem::path dataRoot_;
    Graph graph_;
    std::string handleRequest(const std::string& request);
public:
    explicit HttpServer(std::filesystem::path root);
    int run(int port);
};
