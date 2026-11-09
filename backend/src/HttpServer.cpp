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