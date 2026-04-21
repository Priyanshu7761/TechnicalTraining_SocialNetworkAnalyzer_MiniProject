# Social Network Analyzer - Project Documentation

---

## Abstract

The Social Network Analyzer is a graph-based system designed to demonstrate fundamental Data Structures and Algorithms (DSA) concepts through practical implementation. This project transforms theoretical computer science concepts into an interactive web application that simulates a social network where users can be added, friendships can be formed, and various graph algorithms can be visualized in real-time. The system implements an undirected graph using adjacency list representation, Breadth-First Search (BFS) for shortest path finding, Depth-First Search (DFS) for graph traversal, and hashing techniques for efficient mutual friend discovery. Built with C++ backend and HTML/CSS/JavaScript frontend, the application provides a comprehensive platform for understanding and experimenting with graph data structures and their real-world applications.

---

## Introduction

Social networks represent one of the most practical applications of graph theory in computer science. This project bridges the gap between theoretical DSA concepts and practical implementation by creating an interactive social network analyzer. The application serves as both a learning tool and a demonstration of how fundamental algorithms like BFS and DFS power real-world applications such as social media platforms, recommendation systems, and network analysis.

The project addresses the need for visualizing abstract algorithms through an intuitive interface where users can:
- Create and manage a social network of users
- Establish friendships between users
- Analyze network connections using various graph algorithms
- Understand the complexity and efficiency of different algorithmic approaches

By implementing these concepts in a web-based application, the project makes DSA education more accessible and engaging while maintaining technical rigor and accuracy.

---

## Software/Hardware Requirements

### Software Requirements

**Development Environment:**
- **Operating System:** Windows, macOS, or Linux
- **C++ Compiler:** GCC (g++) with C++11 support or higher
- **Text Editor/IDE:** Visual Studio Code, CLion, or similar

**Backend Dependencies:**
- **cpp-httplib:** Header-only HTTP server library
- **nlohmann/json:** Modern JSON parsing library for C++
- **Standard Library:** STL containers (unordered_map, vector, queue, etc.)

**Frontend Requirements:**
- **Web Browser:** Chrome, Firefox, Safari, or Edge (modern browser with ES6 support)
- **No additional dependencies** - pure HTML/CSS/JavaScript

### Hardware Requirements

**Minimum Requirements:**
- **RAM:** 2GB
- **Storage:** 100MB (including all source files and dependencies)
- **Processor:** Any modern CPU with 1GHz+ clock speed

**Recommended Requirements:**
- **RAM:** 4GB or more
- **Storage:** 500MB for development and testing
- **Processor:** Multi-core CPU for better compilation performance

**Network Requirements:**
- **Localhost access:** Port 8080 must be available
- **No internet connection required** for basic functionality

---

## Model Used/System Design

### Graph Data Structure Model

The system uses an **undirected graph** model implemented using adjacency list representation:

```cpp
unordered_map<string, vector<string>> adjList;
```

**Key Design Decisions:**
- **Adjacency List over Matrix:** More space-efficient for sparse social networks
- **String-based Node Identification:** Usernames serve as unique identifiers
- **Undirected Edges:** Friendships are bidirectional by nature

### Algorithm Models

**BFS Model for Shortest Path:**
- Queue-based level-order traversal
- Parent tracking for path reconstruction
- O(V + E) time complexity

**DFS Model for Traversal:**
- Recursive implementation with visited tracking
- Stack-based exploration (implicit recursion stack)
- O(V + E) time complexity

**Hashing Model for Mutual Friends:**
- unordered_set for O(1) lookup operations
- Set intersection algorithm
- O(k1 + k2) time complexity vs naive O(k1 × k2)

### System Architecture Model

**Three-Tier Architecture:**
1. **Presentation Layer:** HTML/CSS/JS frontend
2. **Business Logic Layer:** C++ graph algorithms
3. **Data Layer:** In-memory adjacency list storage

**RESTful API Model:**
- HTTP methods for CRUD operations
- JSON for data interchange
- Stateless server design

---

## System Architecture Design

### High-Level Architecture

```
+---------------------+     HTTP/JSON     +---------------------+
|   Frontend (Web)    | <---------------> |   Backend (C++)      |
|                     |                   |                     |
| - HTML/CSS/JS       |                   | - HTTP Server        |
| - User Interface    |                   | - Graph Algorithms   |
| - API Calls         |                   | - JSON Processing    |
+---------------------+                   +---------------------+
                                                    |
                                                    v
                                           +---------------------+
                                           |   Data Layer        |
                                           |                     |
                                           | - Adjacency List    |
                                           | - In-memory Storage |
                                           | - Graph State       |
                                           +---------------------+
```

### Component Architecture

**Frontend Components:**
- **UI Controller:** Handles user interactions and form submissions
- **API Client:** Manages HTTP requests to backend
- **Result Renderer:** Displays algorithm outputs dynamically
- **Error Handler:** Provides user feedback for errors

**Backend Components:**
- **HTTP Server:** cpp-httplib based web server
- **Router:** Maps API endpoints to appropriate handlers
- **Graph Engine:** Core graph data structure and algorithms
- **JSON Parser:** Handles request/response serialization

**Data Components:**
- **Graph Storage:** Adjacency list in memory
- **User Registry:** Maintains user existence
- **Edge Registry:** Maintains friendship connections

### Communication Flow

```
User Action -> Frontend Event -> API Request -> Backend Processing -> Algorithm Execution -> JSON Response -> Frontend Update -> User Feedback
```

---

## Flow Chart of Application

### Main Application Flow

```
+-------------------+
|   Start Application   |
+-------------------+
          |
          v
+-------------------+
|   Initialize Server   |
|   (Port 8080)         |
+-------------------+
          |
          v
+-------------------+
|   Load Frontend       |
|   (index.html)        |
+-------------------+
          |
          v
+-------------------+
|   User Interface      |
|   Displayed           |
+-------------------+
          |
          v
+-------------------+
|   User Input          |
|   (Add User/Friend)   |
+-------------------+
          |
          v
+-------------------+
|   Form Validation     |
+-------------------+
          |
          v
+-------------------+
|   API Request         |
|   (HTTP + JSON)       |
+-------------------+
          |
          v
+-------------------+
|   Backend Processing  |
+-------------------+
          |
          v
+-------------------+
|   Graph Algorithm     |
|   Execution           |
+-------------------+
          |
          v
+-------------------+
|   JSON Response       |
|   Generation          |
+-------------------+
          |
          v
+-------------------+
|   Frontend Update     |
|   & Display           |
+-------------------+
```

### Algorithm Selection Flow

```
+-------------------+
|   User Request        |
+-------------------+
          |
          v
+-------------------+
|   Request Type?       |
+-------------------+
          |
    +-----+-----+-----+-----+
    |     |     |     |     |
    v     v     v     v     v
Add User  Add Friend  Get Friends  Mutual Friends  Shortest Path
    |     |     |     |     |
    v     v     v     v     v
O(1)    O(1)    O(k)    O(k1+k2)    O(V+E)
```

---

## Snapshots

### User Interface Screenshots

**Main Dashboard:**
- User addition form
- Friendship creation interface
- Real-time result display

**Algorithm Results:**
- Friends list visualization
- Mutual friends discovery
- Shortest path demonstration

**Interactive Features:**
- Form validation feedback
- Success/error message display
- Responsive design on mobile devices

*(Note: Actual screenshots would be included here in a final report)*

---

## Conclusion

The Social Network Analyzer successfully demonstrates the practical application of fundamental Data Structures and Algorithms concepts through an interactive web-based platform. The project achieves its primary objectives of:

1. **Educational Value:** Provides visual and interactive understanding of graph algorithms
2. **Technical Excellence:** Implements efficient algorithms with optimal time/space complexity
3. **Practical Application:** Shows real-world relevance of theoretical concepts
4. **User Experience:** Offers intuitive interface for exploring graph operations

The project effectively bridges the gap between theoretical computer science education and practical implementation, making complex algorithms accessible and engaging for learners. The modular architecture and clean separation of concerns make the system maintainable and extensible for future enhancements.

The implementation of BFS for shortest path finding, DFS for graph traversal, and hashing for mutual friend discovery showcases the power and efficiency of different algorithmic approaches in solving real-world problems. The project serves as both a learning tool and a foundation for more complex graph-based applications.

---

## Future Improvements

### Algorithm Enhancements
- **Weighted Graph Support:** Implement Dijkstra's algorithm for weighted shortest paths
- **Advanced Graph Algorithms:** Add minimum spanning tree, maximum flow, and graph coloring
- **Performance Optimization:** Implement parallel algorithms for large-scale networks
- **Path Finding Variations:** Add A* algorithm and other heuristic-based pathfinding

### Feature Expansions
- **User Profiles:** Add detailed user information and profile management
- **Friend Suggestions:** Implement recommendation algorithms based on common friends
- **Network Visualization:** Add interactive graph visualization using D3.js or Cytoscape.js
- **Social Network Analysis:** Add centrality measures, clustering coefficients, and community detection

### Technical Improvements
- **Database Integration:** Replace in-memory storage with persistent database (SQLite, MongoDB)
- **Authentication System:** Add user authentication and authorization
- **Real-time Updates:** Implement WebSocket for live network updates
- **Scalability:** Design for handling millions of users and connections

### User Experience Enhancements
- **Mobile Application:** Develop native mobile apps for iOS and Android
- **Export Features:** Allow exporting network data and analysis results
- **Batch Operations:** Support bulk user and friendship operations
- **Analytics Dashboard:** Comprehensive network statistics and insights

### Performance and Scalability
- **Caching Layer:** Implement Redis for frequently accessed data
- **Load Balancing:** Support multiple server instances
- **Distributed Computing:** Design for distributed graph processing
- **Memory Optimization:** Optimize for large-scale graph storage

---

## References

### Academic Sources
1. **Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C.** (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.
2. **Sedgewick, R., & Wayne, K.** (2011). *Algorithms* (4th ed.). Addison-Wesley Professional.
3. **Knuth, D. E.** (1997). *The Art of Computer Programming, Volume 1: Fundamental Algorithms* (3rd ed.). Addison-Wesley.

### Graph Theory References
4. **West, D. B.** (2000). *Introduction to Graph Theory* (2nd ed.). Prentice Hall.
5. **Bollobás, B.** (1998). *Modern Graph Theory*. Springer-Verlag.

### Web Development References
6. **Flanagan, D.** (2020). *JavaScript: The Definitive Guide* (7th ed.). O'Reilly Media.
7. **Freeman, A.** (2014). *Head First HTML and CSS*. O'Reilly Media.

### C++ References
8. **Stroustrup, B.** (2013). *The C++ Programming Language* (4th ed.). Addison-Wesley.
9. **Josuttis, N. M.** (2012). *The C++ Standard Library: A Tutorial and Reference* (2nd ed.). Addison-Wesley.

### Online Resources
10. **GeeksforGeeks:** Graph Algorithms and Data Structures
11. **MIT OpenCourseWare:** Introduction to Algorithms
12. **cpp-httplib Documentation:** https://github.com/yhirose/cpp-httplib
13. **nlohmann/json Documentation:** https://github.com/nlohmann/json

---

## GitHub Link

**Repository:** https://github.com/YOUR_USERNAME/priyanshu-tt

**Project Structure:**
```
priyanshu-tt/
|
+-- backend/
|   +-- Graph.h              # Graph class declaration
|   +-- Graph.cpp            # Graph implementation
|   +-- main.cpp             # HTTP server with REST APIs
|   +-- server_simple.cpp    # Cross-platform server alternative
|   +-- httplib.h            # HTTP server library
|   +-- json.hpp             # JSON parsing library
|
+-- frontend/
|   +-- index.html           # User interface
|   +-- style.css            # Styling and design
|   +-- script.js            # Frontend logic and API calls
|
+-- README.md                # Project documentation
+-- PROJECT_DOCUMENTATION.md # This comprehensive documentation
```

**Installation and Setup:**
```bash
# Clone the repository
git clone https://github.com/YOUR_USERNAME/priyanshu-tt.git
cd priyanshu-tt

# Compile the backend
cd backend
g++ -std=c++11 -I/usr/local/include main.cpp Graph.cpp -o server -lpthread

# Run the server
./server

# Open http://localhost:8080 in your browser
```

**Contributing Guidelines:**
- Fork the repository
- Create a feature branch
- Submit a pull request with detailed description
- Follow coding standards and documentation practices

---
