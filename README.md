# Tourist Guide and Shortest Route Finder

A responsive travel website with a C++17 backend. Explore destinations, view local guide profiles, save demo bookings, and calculate shortest routes using Dijkstra's algorithm and a min-priority queue.

## Features
- Responsive travel-inspired UI based on the supplied visual references
- Smooth reveal animations, hover transitions, mobile layout, and reduced-motion support
- Destination search and trip-style filtering
- Local guide cards and sample booking form
- C++ HTTP server with registration/login, destination, guide, booking, and route endpoints
- Weighted graph loaded from `data/roads.txt`; `backend/src/Graph.cpp` implements Dijkstra using `std::priority_queue`, a distance map, predecessor tracking, and path reconstruction
- Persistent sample bookings in `data/bookings.json`
- Demo registration/login stored in `data/users.txt` (password hash is for academic demonstration only, not production security)
- Browser-only fallback for route calculations and bookings when opened with a static web server

## Tech stack
- Frontend: HTML, CSS, JavaScript
- Backend: C++17 and standard library sockets (no third-party C++ framework required)
- DSA: weighted graph, adjacency list, Dijkstra, `std::priority_queue`, maps and vectors
- Sample bus image: `frontend/assets/uttarakhand-bus.png`

## Run on Windows (MinGW-w64 / g++)

Open the project folder in VS Code and double-click `run-windows.bat`, or run it from the terminal:

```bat
run-windows.bat
```

The script compiles all modular C++ source files and starts the server. Then open **http://localhost:8090** in your browser.

## Run on Linux

```bash
g++ -std=c++17 -O2 -Wall -Wextra -I backend/include backend/src/*.cpp -o tourist_server
./tourist_server . 8090
```

Open **http://localhost:8090**. Stop the server with `Ctrl+C`.


## API endpoints
- `POST /api/register` — create an account with `name`, `email`, and `password`
- `POST /api/login` — verify `email` and `password`
- `GET /api/destinations` — sample destination data
- `GET /api/guides` — sample guide data
- `GET /api/locations` — graph locations
- `GET /api/route?from=Delhi&to=Mussoorie` — shortest path and total sample distance
- `GET /api/bookings` — saved bookings
- `POST /api/bookings` — save a booking (`tourist`, `guide`, `destination`, `date`)

## Notes
- Road distances in `data/roads.txt` are sample academic values, not verified live driving distances.
- Destination photography is loaded from Unsplash URLs and therefore needs an internet connection. The included bus image is local.
- This is an academic demonstration, not a production booking service. Login/registration is implemented for demonstration, but its dependency-free hash is not production-grade; replace it with Argon2id/bcrypt/scrypt before real deployment. Payment, live maps/traffic, sessions, and production-grade account security are not implemented.
- Smooth motion respects the device's `prefers-reduced-motion` setting.


## Modular C++ backend

The backend is split into focused header/source files under `backend/include` and `backend/src`: `Person`, `Tourist`, `Guide`, `Destination`, `Booking`, `Graph`, `FileHandler`, `HttpUtils`, and `HttpServer`. The frontend and its visual styling are kept separate and unchanged.
