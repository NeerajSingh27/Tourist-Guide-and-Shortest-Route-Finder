#include "HttpServer.h"
#include "Booking.h"
#include "AuthService.h"
#include "Destination.h"
#include "FileHandler.h"
#include "Guide.h"
#include "HttpUtils.h"
#include "Tourist.h"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
using socket_t = SOCKET;
#define CLOSESOCKET closesocket
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
using socket_t = int;
#define CLOSESOCKET close
#endif
namespace fs = std::filesystem;
namespace
{
    std::string routeJson(const RouteResult &result)
    {
        if (!result.found)
            return "{\"ok\":false,\"message\":\"No route found. Check the selected locations.\"}";
        std::ostringstream out;
        out << "{\"ok\":true,\"distance\":" << result.distance << ",\"path\":[";
        for (std::size_t i = 0; i < result.path.size(); ++i)
        {
            if (i)
                out << ',';
            out << '\"' << HttpUtils::jsonEscape(result.path[i]) << '\"';
        }
        out << "]}";
        return out.str();
    }
    std::string destinationJson()
    {
        const std::vector<Destination> destinations = {
            {1, "Mussoorie", "Queen of the Hills", "Garhwal", "Misty viewpoints, pine forests and colonial-era charm.", "https://images.unsplash.com/photo-1597074866923-dc0589150358?auto=format&fit=crop&w=900&q=85"},
            {2, "Nainital", "The Lake District", "Kumaon", "A beautiful lake town surrounded by green hills.", "https://images.unsplash.com/photo-1626621341517-bbf3d9990a23?auto=format&fit=crop&w=900&q=85"},
            {3, "Rishikesh", "Yoga & Adventure", "Garhwal", "Riverside spirituality, rafting and suspension bridges.", "https://images.unsplash.com/photo-1581793745862-99fde7fa73d2?auto=format&fit=crop&w=900&q=85"},
            {4, "Auli", "Snow & Scenic Views", "Chamoli", "Alpine meadows, mountain panoramas and winter sports.", "https://images.unsplash.com/photo-1519681393784-d120267933ba?auto=format&fit=crop&w=900&q=85"},
            {5, "Kedarnath", "Faith & Peace", "Rudraprayag", "A revered Himalayan temple surrounded by dramatic peaks.", "https://images.unsplash.com/photo-1605649487212-47bdab064df7?auto=format&fit=crop&w=900&q=85"},
            {6, "Dehradun", "Gateway to the Hills", "Garhwal", "A relaxed valley city and a starting point for mountain trips.", "https://images.unsplash.com/photo-1500530855697-b586d89ba3ee?auto=format&fit=crop&w=900&q=85"}};
        std::ostringstream out;
        out << '[';
        for (std::size_t i = 0; i < destinations.size(); ++i)
        {
            const auto &d = destinations[i];
            if (i)
                out << ',';
            out << "{\"id\":" << d.getId() << ",\"name\":\"" << HttpUtils::jsonEscape(d.getName()) << "\",\"subtitle\":\"" << HttpUtils::jsonEscape(d.getSubtitle()) << "\",\"region\":\"" << HttpUtils::jsonEscape(d.getRegion()) << "\",\"description\":\"" << HttpUtils::jsonEscape(d.getDescription()) << "\",\"image\":\"" << HttpUtils::jsonEscape(d.getImage()) << "\"}";
        }
        out << ']';
        return out.str();
    }
    std::string guidesJson()
    {
        const std::vector<Guide> guides = {
            {101, "Ravi Rawat", "", 7, 4.9, "Mountain trails", true}, {102, "Meera Bisht", "", 5, 4.8, "Culture & heritage", true}, {103, "Karan Negi", "", 9, 4.9, "Adventure & rafting", true}, {104, "Pooja Rana", "", 4, 4.7, "Family-friendly tours", true}};
        std::ostringstream out;
        out << '[';
        for (std::size_t i = 0; i < guides.size(); ++i)
        {
            const auto &g = guides[i];
            if (i)
                out << ',';
            std::string initials;
            bool startWord = true;
            for (char c : g.getName())
            {
                if (c == ' ')
                    startWord = true;
                else if (startWord)
                {
                    initials += c;
                    startWord = false;
                    if (initials.size() == 2)
                        break;
                }
            }
            out << "{\"id\":" << g.getId() << ",\"name\":\"" << HttpUtils::jsonEscape(g.getName()) << "\",\"experience\":" << g.getExperience() << ",\"rating\":" << g.getRating() << ",\"specialization\":\"" << HttpUtils::jsonEscape(g.getSpecialization()) << "\",\"available\":" << (g.isAvailable() ? "true" : "false") << ",\"initials\":\"" << initials << "\"}";
        }
        out << ']';
        return out.str();
    }
}
HttpServer::HttpServer(fs::path root) : root_(fs::absolute(std::move(root)).lexically_normal()), webRoot_(root_ / "frontend"), dataRoot_(root_ / "data")
{
    fs::create_directories(dataRoot_);
    graph_ = FileHandler::loadRoadGraph(dataRoot_ / "roads.txt");
}
std::string HttpServer::handleRequest(const std::string &request)
{
    const auto headEnd = request.find("\r\n\r\n");
    const std::string head = headEnd == std::string::npos ? request : request.substr(0, headEnd);
    const std::string body = headEnd == std::string::npos ? "" : request.substr(headEnd + 4);
    std::istringstream stream(head);
    std::string method, target, version;
    stream >> method >> target >> version;
    if (method == "OPTIONS")
        return HttpUtils::response(200, "text/plain", "ok");
    if (target == "/api/register" && method == "POST")
    {
        const auto result = AuthService::registerUser(dataRoot_ / "users.txt",
                                                      HttpUtils::jsonField(body, "name"), HttpUtils::jsonField(body, "email"), HttpUtils::jsonField(body, "password"));
        const int status = result.ok ? 201 : 400;
        std::ostringstream out;
        out << "{\"ok\":" << (result.ok ? "true" : "false")
            << ",\"message\":\"" << HttpUtils::jsonEscape(result.message) << "\"";
        if (result.ok)
            out << ",\"name\":\"" << HttpUtils::jsonEscape(result.name)
                << "\",\"email\":\"" << HttpUtils::jsonEscape(result.email) << "\"";
        out << '}';
        return HttpUtils::response(status, "application/json; charset=utf-8", out.str());
    }
    if (target == "/api/login" && method == "POST")
    {
        const auto result = AuthService::loginUser(dataRoot_ / "users.txt",
                                                   HttpUtils::jsonField(body, "email"), HttpUtils::jsonField(body, "password"));
        std::ostringstream out;
        out << "{\"ok\":" << (result.ok ? "true" : "false")
            << ",\"message\":\"" << HttpUtils::jsonEscape(result.message) << "\"";
        if (result.ok)
            out << ",\"name\":\"" << HttpUtils::jsonEscape(result.name)
                << "\",\"email\":\"" << HttpUtils::jsonEscape(result.email) << "\"";
        out << '}';
        return HttpUtils::response(result.ok ? 200 : 400, "application/json; charset=utf-8", out.str());
    }
    if (target.rfind("/api/route", 0) == 0 && method == "GET")
    {
        const auto from = HttpUtils::queryValue(target, "from"), to = HttpUtils::queryValue(target, "to");
        if (from.empty() || to.empty())
            return HttpUtils::response(400, "application/json", "{\"ok\":false,\"message\":\"Select both source and destination.\"}");
        return HttpUtils::response(200, "application/json; charset=utf-8", routeJson(graph_.dijkstra(from, to)));
    }
    if (target == "/api/locations" && method == "GET")
    {
        auto locations = graph_.locations();
        std::ostringstream out;
        out << '[';
        for (std::size_t i = 0; i < locations.size(); ++i)
        {
            if (i)
                out << ',';
            out << '\"' << HttpUtils::jsonEscape(locations[i]) << '\"';
        }
        out << ']';
        return HttpUtils::response(200, "application/json; charset=utf-8", out.str());
    }
    if (target == "/api/destinations" && method == "GET")
        return HttpUtils::response(200, "application/json; charset=utf-8", destinationJson());
    if (target == "/api/guides" && method == "GET")
        return HttpUtils::response(200, "application/json; charset=utf-8", guidesJson());
    if (target == "/api/bookings" && method == "GET")
    {
        auto data = FileHandler::readAll(dataRoot_ / "bookings.json");
        return HttpUtils::response(200, "application/json; charset=utf-8", data.empty() ? "[]" : data);
    }
    if (target == "/api/bookings" && method == "POST")
    {
        Booking booking(HttpUtils::jsonField(body, "tourist"), HttpUtils::jsonField(body, "guide"), HttpUtils::jsonField(body, "destination"), HttpUtils::jsonField(body, "date"));
        if (!booking.isValid())
            return HttpUtils::response(400, "application/json", "{\"ok\":false,\"message\":\"Please complete all booking fields.\"}");
        std::string error;
        if (!FileHandler::appendBookingJson(dataRoot_ / "bookings.json", booking.getTourist(), booking.getGuide(), booking.getDestination(), booking.getDate(), error))
            return HttpUtils::response(500, "application/json", "{\"ok\":false,\"message\":\"" + HttpUtils::jsonEscape(error) + "\"}");
        return HttpUtils::response(201, "application/json", "{\"ok\":true,\"message\":\"Booking saved successfully.\"}");
    }
    if (method != "GET")
        return HttpUtils::response(405, "application/json", "{\"error\":\"Method not allowed\"}");
    std::string path = target.substr(0, target.find('?'));
    if (path == "/")
        path = "/index.html";
    const fs::path file = (webRoot_ / fs::path(path).relative_path()).lexically_normal();
    auto webString = webRoot_.string(), fileString = file.string();
    if (fileString.compare(0, webString.size(), webString) != 0)
        return HttpUtils::response(400, "text/plain", "Invalid path");
    const auto content = FileHandler::readAll(file);
    if (content.empty())
        return HttpUtils::response(404, "text/plain", "Not found");
    return HttpUtils::response(200, HttpUtils::mimeType(file), content);
}
int HttpServer::run(int port)
{
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
#endif
    socket_t server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0)
    {
        std::cerr << "Could not create socket\n";
        return 1;
    }
    int opt = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char *>(&opt), sizeof(opt));
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(static_cast<unsigned short>(port));
    if (bind(server, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0 || listen(server, 16) < 0)
    {
        std::cerr << "Could not bind the selected port. Is it already in use?\n";
        CLOSESOCKET(server);
        return 1;
    }
    std::cout << "Tourist Guide and Shortest Route Finder running at http://localhost:" << port << "\nPress Ctrl+C to stop.\n";
    while (true)
    {
        sockaddr_in clientAddress{};
#ifdef _WIN32
        int length = sizeof(clientAddress);
#else
        socklen_t length = sizeof(clientAddress);
#endif
        socket_t client = accept(server, reinterpret_cast<sockaddr *>(&clientAddress), &length);
        if (client < 0)
            continue;
        std::string request;
        char buffer[8192];
        std::size_t expectedTotal = std::string::npos;
        while (true)
        {
            const int received = static_cast<int>(recv(client, buffer, sizeof(buffer), 0));
            if (received <= 0)
                break;
            request.append(buffer, static_cast<std::size_t>(received));
            const auto separator = request.find("\r\n\r\n");
            if (separator != std::string::npos && expectedTotal == std::string::npos)
            {
                const std::string headers = request.substr(0, separator);
                std::istringstream headerStream(headers);
                std::string headerLine;
                std::getline(headerStream, headerLine); // request line
                while (std::getline(headerStream, headerLine))
                {
                    if (!headerLine.empty() && headerLine.back() == '\r')
                        headerLine.pop_back();
                    const auto colon = headerLine.find(':');
                    if (colon != std::string::npos)
                    {
                        std::string key = headerLine.substr(0, colon);
                        std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c)
                                       { return static_cast<char>(std::tolower(c)); });
                        if (key == "content-length")
                        {
                            try
                            {
                                expectedTotal = separator + 4 + static_cast<std::size_t>(std::stoul(HttpUtils::trim(headerLine.substr(colon + 1))));
                            }
                            catch (...)
                            {
                                expectedTotal = separator + 4;
                            }
                        }
                    }
                }
                if (expectedTotal == std::string::npos)
                    expectedTotal = separator + 4;
            }
            if (expectedTotal != std::string::npos && request.size() >= expectedTotal)
                break;
        }
        const std::string output = handleRequest(request);
        std::size_t sent = 0;
        while (sent < output.size())
        {
            int count = static_cast<int>(send(client, output.data() + sent, static_cast<int>(output.size() - sent), 0));
            if (count <= 0)
                break;
            sent += static_cast<std::size_t>(count);
        }
        CLOSESOCKET(client);
    }
    CLOSESOCKET(server);
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}
