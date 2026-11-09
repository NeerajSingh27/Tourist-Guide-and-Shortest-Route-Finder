#include "HttpUtils.h"
#include <sstream>
namespace HttpUtils
{
    std::string trim(const std::string &value)
    {
        // Finds the first character that isn't a space, newline, carriage return or tab.

        const auto first = value.find_first_not_of(" \r\n\t");

        if (first == std::string::npos)
            return {};

        // Finds the last character that isn't whitespace and.
        // Extracts the string between the first and last non-whitespace characters.
        return value.substr(first, value.find_last_not_of(" \r\n\t") - first + 1);
    }