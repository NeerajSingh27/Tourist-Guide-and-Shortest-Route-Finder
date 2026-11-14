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
    for (char c : value)
    {

        // Add a backslash before existing backslashes and double quotes.
        // This prevents them from breaking the JSON string.
        if (c == '\\' || c == '"')
            out += '\\';

        // Convert an actual newline into the escaped sequence "\n".
        if (c == '\n')
            out += "\\n";

        // Ignore carriage returns; otherwise, append the current character.
        else if (c != '\r')
            out += c;
    }

    // Return the final escaped string.
    return out;
    std::string queryValue(const std::string &target, const std::string &key)
    {
        const auto q = target.find('?');
        if (q == std::string::npos)
            return {};
        const std::string query = target.substr(q + 1), needle = key + "=";
        const auto p = query.find(needle);
        if (p == std::string::npos)
            return {};
        const auto start = p + needle.size(), end = query.find('&', start);
        const std::string encoded = query.substr(start, end == std::string::npos ? end : end - start);
        std::string out;
        for (std::size_t i = 0; i < encoded.size(); ++i)
        {
            if (encoded[i] == '+')
                out += ' ';
            else if (encoded[i] == '%' && i + 2 < encoded.size())
            {
                try
                {
                    out += static_cast<char>(std::stoi(encoded.substr(i + 1, 2), nullptr, 16));
                    i += 2;
                }
                catch (...)
                {
                    out += encoded[i];
                }
            }
            else
                out += encoded[i];
        }
        return out;
    }
    std::string jsonField(const std::string &body, const std::string &key)
    {
        const std::string needle = "\"" + key + "\"";
        auto p = body.find(needle);
        if (p == std::string::npos)
            return {};
        p = body.find(':', p + needle.size());
        if (p == std::string::npos)
            return {};
        p = body.find('"', p + 1);
        if (p == std::string::npos)
            return {};
        std::string out;
        bool escaped = false;
        for (std::size_t i = p + 1; i < body.size(); ++i)
        {
            const char c = body[i];
            if (escaped)
            {
                switch (c)
                {
                case 'n':
                    out += '\n';
                    break;
                case 'r':
                    out += '\r';
                    break;
                case 't':
                    out += '\t';
                    break;
                case '\\':
                    out += '\\';
                    break;
                case '"':
                    out += '"';
                    break;
                default:
                    out += c;
                    break;
                }
                escaped = false;
            }
            else if (c == '\\')
            {
                escaped = true;
            }
            else if (c == '"')
            {
                return out;
            }
            else
            {
                out += c;
            }
        }
        return {};
    }
    std::string mimeType(const std::filesystem::path &path)
    {
        const auto ext = path.extension().string();
        if (ext == ".html")
            return "text/html; charset=utf-8";
        if (ext == ".css")
            return "text/css; charset=utf-8";
        if (ext == ".js")
            return "application/javascript; charset=utf-8";
        if (ext == ".png")
            return "image/png";
        if (ext == ".jpg" || ext == ".jpeg")
            return "image/jpeg";
        if (ext == ".svg")
            return "image/svg+xml";
        if (ext == ".ico")
            return "image/x-icon";
        return "application/octet-stream";
    }
    std::string response(int status, const std::string &contentType, const std::string &body)
    {
        std::string label = "Internal Server Error";
        switch (status)
        {
        case 200:
            label = "OK";
            break;
        case 201:
            label = "Created";
            break;
        case 400:
            label = "Bad Request";
            break;
        case 404:
            label = "Not Found";
            break;
        case 405:
            label = "Method Not Allowed";
            break;
        case 500:
            label = "Internal Server Error";
            break;
        }
        std::ostringstream out;
        out << "HTTP/1.1 " << status << ' ' << label << "\r\nContent-Type: " << contentType
            << "\r\nContent-Length: " << body.size()
            << "\r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Methods: GET, POST, OPTIONS"
            << "\r\nAccess-Control-Allow-Headers: Content-Type\r\nConnection: close\r\n\r\n"
            << body;
        return out.str();
    }
}
