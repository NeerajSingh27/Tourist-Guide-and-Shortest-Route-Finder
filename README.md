# 🗺️ Tourist Guide and Shortest Route Finder

A **C++ console-based project** that helps tourists explore destinations, find suitable tourist guides, make bookings, and find the shortest route between locations.

This project is developed as an academic project to demonstrate the practical use of **Object-Oriented Programming (OOP), Data Structures and Algorithms (DSA), STL, and File Handling in C++**.

---

## Project Overview

Tourists often need to manage different parts of a trip separately, such as finding destinations, selecting a suitable tourist guide, checking guide availability, making a booking, and deciding the best route to travel.

The **Tourist Guide and Shortest Route Finder** combines these basic functionalities into a single C++ console application.

The application allows a tourist to:

* Register and log in
* View available tourist destinations
* Search for destinations
* View tourist guide details
* Check guide availability
* Book a suitable guide
* View booking information
* Find the shortest route between locations
* Calculate the total distance between locations

The project uses a **weighted graph** to represent roads between locations. **Dijkstra's algorithm with a priority queue** is used to find the shortest route.

---

## Problem Statement

Tourists may face difficulty while planning a trip because different tasks such as finding destinations, selecting a reliable guide, checking guide availability, making bookings, and finding an efficient route are often handled separately.

The purpose of this project is to develop a simple console-based application that brings these basic facilities together.

The project also addresses the route-finding problem. Since multiple roads may exist between two tourist locations, the locations are represented as vertices and roads as weighted edges. The distance of each road is used as its weight, and Dijkstra's shortest-path algorithm is used to determine the shortest route.

---

## Objectives

The main objectives of the project are:

1. To provide a simple platform for tourists to explore destinations.
2. To allow tourists to register and log in.
3. To display available tourist guides.
4. To provide guide information such as experience, rating, specialization, and availability.
5. To allow tourists to book available guides.
6. To store tourist, guide, destination, booking, and road information using files.
7. To represent tourist locations and roads using a weighted graph.
8. To find the shortest route using Dijkstra's algorithm.
9. To use a priority queue for efficient shortest-path processing.
10. To demonstrate important OOP and DSA concepts in a practical project.

---

# Features

### 👤 Tourist Module

* Tourist registration
* Tourist login
* Tourist profile
* Destination search
* Destination viewing
* Guide selection
* Guide booking
* Booking information

### Guide Module

Guide information can include:

* Guide ID
* Guide name
* Experience
* Rating
* Specialization
* Availability

### Destination Module

Tourists can view information about available destinations such as:

* Destination ID
* Destination name
* Location
* Description

### Booking Module

The booking module connects:

```text
Tourist
   ↓
Guide
   ↓
Destination
   ↓
Booking
```

Booking information is stored permanently in `bookings.txt`.

### Shortest Route Finder

The application represents locations and roads using a weighted graph.

```text
Location = Vertex
Road = Edge
Distance = Edge Weight
```

Dijkstra's algorithm is used to calculate the shortest route.

A priority queue is used to efficiently select the location with the minimum current distance.

---

# OOP Concepts Used

The project is designed around real-world entities using classes and objects.

## 1. Classes and Objects

Main classes include:

```text
Person
Tourist
Guide
Destination
Booking
Graph
```

Objects of these classes represent actual entities in the application.

---

## 2. Encapsulation

Data members are kept private and accessed through public member functions.

Example:

```cpp
class Tourist {
private:
    string name;
    string phone;

public:
    void setName(string name);
    string getName();
};
```

This protects the internal data of the object.

---

## 3. Data Hiding

Important information such as tourist details and login information can be kept private inside classes.

---

## 4. Inheritance

A common base class can be used for Tourist and Guide.

```text
             Person
             /    \
            /      \
       Tourist    Guide
```

Common properties such as name and contact information can be placed in the `Person` class.

---

## 5. Polymorphism

Virtual functions can be used to allow different derived classes to provide their own implementation.

For example:

```cpp
class Person {
public:
    virtual void displayProfile() = 0;
};
```

`Tourist` and `Guide` can override `displayProfile()`.

---

## 6. Constructors

Constructors are used to initialize objects when they are created.

Parameterized constructors can initialize objects with values such as:

```text
Name
ID
Experience
Rating
```

---

## 7. Destructors

Destructors are used when objects are destroyed and can be used for resource cleanup.

---

## 8. Static Data Members

Static members can be used to maintain information shared by all objects, such as the number of created Tourist or Guide objects.

---

## 9. `this` Pointer

The `this` pointer can be used to distinguish between class data members and function parameters.

Example:

```cpp
this->name = name;
```

---

## 10. Operator Overloading

The stream insertion operator can be overloaded to display objects conveniently.

Example:

```cpp
cout << guide;
```

---

# 📊 DSA Concepts Used

## 1. Graph

The road network is represented as a weighted graph.

```text
        220
Delhi -------- Haridwar
  |               |
290              55
  |               |
  |            Dehradun
  |               |
  +---- Mussoorie-+
          35
```

Locations are vertices and roads are edges.

---

## 2. Weighted Graph

Each road has a distance associated with it.

Example:

```text
Delhi → Haridwar = 220 km
Dehradun → Mussoorie = 35 km
```

---

## 3. Adjacency List

The graph can be represented using an adjacency list.

Conceptually:

```text
Delhi
 ├── Haridwar (220)
 ├── Mussoorie (290)
 └── Nainital (320)

Haridwar
 ├── Delhi (220)
 ├── Rishikesh (25)
 └── Dehradun (55)
```

---

## 4. Dijkstra's Algorithm

Dijkstra's algorithm is used to find the shortest path between two locations when road distances are non-negative.

The basic process is:

```text
Start Location
      ↓
Initialize distances
      ↓
Insert source into priority queue
      ↓
Select minimum-distance location
      ↓
Relax connected edges
      ↓
Update distances
      ↓
Repeat
      ↓
Shortest Route
```

---

## 5. Priority Queue

A min-priority queue is used to process the location having the smallest current distance.

Example C++ declaration:

```cpp
priority_queue<
    pair<int, int>,
    vector<pair<int, int>>,
    greater<pair<int, int>>
> pq;
```

---

## 6. STL

The project can use several C++ Standard Template Library components:

* `vector`
* `map`
* `priority_queue`
* `pair`
* `sort`
* `string`

---


# 📂 Folder Description

| File / Folder      | Purpose                                    |
| ------------------ | ------------------------------------------ |
| `main.cpp`         | Main program and menu                      |
| `classes/`         | Contains OOP classes                       |
| `Person`           | Base class for common person information   |
| `Tourist`          | Handles tourist information and operations |
| `Guide`            | Handles guide information and availability |
| `Destination`      | Handles destination information            |
| `Booking`          | Handles booking information                |
| `dsa/`             | Contains DSA implementation                |
| `Graph`            | Represents locations and roads             |
| `Dijkstra`         | Finds shortest routes                      |
| `data/`            | Stores persistent project data             |
| `tourists.txt`     | Tourist records                            |
| `guides.txt`       | Guide records                              |
| `destinations.txt` | Destination records                        |
| `bookings.txt`     | Booking records                            |
| `roads.txt`        | Road connections and distances             |
| `utils/`           | Helper functions                           |
| `FileHandler`      | Reads/writes files                         |
| `InputValidation`  | Handles invalid input                      |
| `docs/`            | Project documentation and diagrams         |
| `README.md`        | Project documentation                      |

---

# 💾 File Handling

File handling is used to provide **persistent data storage**.

Without file handling, the information entered during program execution would be lost when the program closes.

The project uses:

```cpp
#include <fstream>
```

### `ifstream`

Used for reading data from files.

```cpp
ifstream file("data/tourists.txt");
```

### `ofstream`

Used for writing data into files.

```cpp
ofstream file("data/tourists.txt", ios::app);
```

### Data Files

```text
tourists.txt
     ↓
Registered tourists

guides.txt
     ↓
Guide information

destinations.txt
     ↓
Destination information

bookings.txt
     ↓
Booking records

roads.txt
     ↓
Roads + distances
     ↓
Weighted Graph
     ↓
Dijkstra
```

---

# Sample Road Data

The `roads.txt` file can contain:

```text
Delhi|Haridwar|220
Delhi|Mussoorie|290
Delhi|Nainital|320

Haridwar|Rishikesh|25
Haridwar|Dehradun|55
Haridwar|Nainital|285

Rishikesh|Dehradun|45
Rishikesh|Auli|250

Dehradun|Mussoorie|35
Dehradun|Nainital|290

Mussoorie|Nainital|320

Nainital|Auli|260
```

The program reads this information and creates the weighted graph.

---

# 🔄 Project Workflow

```text
                 START
                   │
                   ▼
             Main Menu
                   │
        ┌──────────┴──────────┐
        ▼                     ▼
    Register/Login       Find Route
        │                     │
        ▼                     ▼
 Tourist Dashboard       Select Source
        │                     │
   ┌────┼────┐               ▼
   ▼    ▼    ▼          Select Destination
  View  Find Book             │
  Dest. Guide                 ▼
        │                 Build Graph
        │                     │
        │                     ▼
        │                  Dijkstra
        │                     │
        │                     ▼
        │               Shortest Route
        │
        ▼
  Make Booking
        │
        ▼
 Save Data to File
        │
        ▼
       END
```

---

# Technologies Used

* **Programming Language:** C++
* **IDE:** Visual Studio Code
* **Compiler:** MinGW / G++
* **Data Structures:** Graph, Adjacency List, Priority Queue
* **Algorithm:** Dijkstra's Shortest Path Algorithm
* **OOP:** Classes, Objects, Encapsulation, Inheritance, Polymorphism
* **STL:** Vector, Map, Priority Queue, Algorithms
* **Storage:** Text Files
* **Version Control:** Git
* **Repository:** GitHub

---

# How to Run

## Step 1: Clone the Repository

```bash
git clone <YOUR-GITHUB-REPOSITORY-URL>
```

## Step 2: Enter the Project Folder

```bash
cd Tourist-Guide-and-Shortest-Route-Finder
```

## Step 3: Compile the Program

If all `.cpp` files are present in the folders:

```bash
g++ main.cpp classes/*.cpp dsa/*.cpp utils/*.cpp -o tourist_guide
```

## Step 4: Run

### Windows

```bash
tourist_guide.exe
```

### Linux / macOS

```bash
./tourist_guide
```

---

# 🖥️ Example Application Menu

The final application can provide a menu similar to:

```text
=========================================
   TOURIST GUIDE AND SHORTEST ROUTE FINDER
=========================================

1. Tourist Registration
2. Tourist Login
3. View Destinations
4. Search Destination
5. View Tourist Guides
6. Book a Guide
7. View Booking
8. Find Shortest Route
9. Exit

Enter your choice:
```

---

# Testing

The project will be tested for:

* Tourist registration
* Tourist login
* Invalid login details
* Destination search
* Guide availability
* Guide booking
* File reading and writing
* Invalid menu input
* Route with multiple possible paths
* Source and destination validation
* Shortest route calculation
* Unreachable locations

---

# ⏱️ Complexity of Dijkstra

For an adjacency-list implementation using a binary-heap priority queue:

```text
Time Complexity:  O((V + E) log V)

Space Complexity: O(V + E)
```

Where:

* `V` = number of vertices/locations
* `E` = number of roads/edges

---

# Project Assumptions

* The project uses predefined/sample destination and guide data.
* Road distances are fixed sample values.
* Road distances are not obtained from live maps.
* A guide can only be booked if they are available.
* Data is stored in text files instead of a database.
* The project is designed as a console-based academic application.
* Internet connectivity is not required for the basic application.

---

# Future Scope

The project can be extended in the future with:

* Web-based interface
* Database integration
* Online guide profiles
* Reviews and ratings
* Online booking and payment
* Multiple route suggestions

---

# 👥 Team Contribution

The project can be divided into the following modules:

### Member 1 — OOP / Tourist Module

* Person class
* Tourist class
* Registration
* Login
* Tourist profile

### Member 2 — Guide / Booking Module

* Guide class
* Destination class
* Booking class
* Guide availability
* Booking functionality

### Member 3 — DSA / Route Finder

* Graph implementation
* Adjacency list
* Dijkstra's algorithm
* Priority queue
* Route reconstruction

### Member 4 — Integration / Testing

* Main menu
* Module integration
* File handling
* Input validation
* Testing
* Documentation

---

# 🎓 Academic Concepts Demonstrated

This project demonstrates the practical application of:

### OOP

```text
Classes & Objects
Encapsulation
Data Hiding
Constructors
Destructors
Inheritance
Polymorphism
Virtual Functions
Operator Overloading
Static Members
This Pointer
```

### DSA

```text
Graph
Weighted Graph
Adjacency List
Priority Queue
Dijkstra's Algorithm
Searching
Sorting
```

### C++ / STL

```text
Vector
Map
Pair
Priority Queue
Algorithms
Strings
File Handling
Exception Handling
```

---

# Project Status

🚧 **Currently under development**

The project is being developed incrementally, starting with the core OOP and DSA implementation and later integrating all modules into a complete console application.

---

# 👨‍💻 Developed For

**Academic C++ Project**

**Project:** Tourist Guide and Shortest Route Finder

**Focus:**
`OOP + DSA + STL + File Handling`

---

## Conclusion

The **Tourist Guide and Shortest Route Finder** is a practical C++ console application that combines tourism-related functionality with important programming concepts.

The project demonstrates how **OOP can be used to model real-world entities**, how **file handling can provide persistent storage**, and how **DSA can solve the shortest-route problem using graphs, Dijkstra's algorithm, and priority queues**.

The main goal is not only to build a working application but also to demonstrate how theoretical concepts from **Object-Oriented Programming and Data Structures & Algorithms** can be applied to a real-world problem.
