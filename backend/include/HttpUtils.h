#pragma once
#include <filesystem>
#include <string>
namespace HttpUtils {
std::string trim(const std::string& value);
std::string jsonEscape(const std::string& value);
std::string queryValue(const std::string& target, const std::string& key);
std::string jsonField(const std::string& body, const std::string& key);
std::string mimeType(const std::filesystem::path& path);
std::string response(int status, const std::string& contentType, const std::string& body);
}
