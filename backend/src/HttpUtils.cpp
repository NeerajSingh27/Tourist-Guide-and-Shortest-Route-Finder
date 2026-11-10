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

     // Stores the final escaped string.
    std::string out;

    // Visit each character of the input string one by one.
    for (char c : value) {

        // Add a backslash before existing backslashes and double quotes.
        // This prevents them from breaking the JSON string.
        if (c == '\\' || c == '"') out += '\\';

        // Convert an actual newline into the escaped sequence "\n".
        if (c == '\n') out += "\\n";

        // Ignore carriage returns; otherwise, append the current character.
        else if (c != '\r') out += c;
    }

    // Return the final escaped string.
    return out;
}
