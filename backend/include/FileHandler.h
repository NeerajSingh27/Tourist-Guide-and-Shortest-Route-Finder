#pragma once
#include "Graph.h"
#include <filesystem>
#include <string>
class FileHandler {
public:
    static std::string readAll(const std::filesystem::path& path);
    static Graph loadRoadGraph(const std::filesystem::path& path);
    static bool appendBookingJson(const std::filesystem::path& path,
                                  const std::string& tourist, const std::string& guide,
                                  const std::string& destination, const std::string& date,
                                  std::string& error);
};
