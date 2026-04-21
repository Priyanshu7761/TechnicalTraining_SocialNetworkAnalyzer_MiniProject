# 🌐 Social Network Analyzer

A graph-based social network system demonstrating fundamental Data Structures and Algorithms (DSA) concepts including Graph, BFS, DFS, and Hashing.

---

## 📊 DSA Concepts Explained

### 1. **Graph using Adjacency List**

**What is it?**
- A Graph is a non-linear data structure consisting of nodes (vertices) and edges
- In our social network: **Users = Nodes**, **Friendships = Edges**
- We use an **undirected graph** (friendship is bidirectional)

**Implementation:**
```cpp
unordered_map<string, vector<string>> adjList;
```

**Why Adjacency List?**
- **Space Efficient**: O(V + E) where V = vertices, E = edges
- **Fast Friend Lookup**: O(1) average case to find a user's friends
- Better than adjacency matrix for sparse graphs (social networks are typically sparse)

**Time Complexity:**
- Add User: **O(1)**
- Add Friendship: **O(1)** amortized
- Get Friends: **O(1)** to access, O(k) to return k friends

---

### 2. **BFS (Breadth-First Search)**

**What is it?**
- Explores graph level by level using a **queue**
- Visits all neighbors before moving to next level
- **Guarantees shortest path** in unweighted graphs

**Use Case:** Finding shortest path between two users

**Algorithm:**
1. Start from source user, mark as visited
2. Add to queue
3. While queue not empty:
   - Dequeue current user
   - For each friend of current user:
     - If not visited, mark visited and enqueue
     - Track parent to reconstruct path
4. Backtrack from destination using parent pointers

**Time Complexity:** **O(V + E)**
- V = number of users (vertices)
- E = number of friendships (edges)
- We visit each user once and check each friendship once

**Space Complexity:** **O(V)**
- Queue, visited set, and parent map

**Why BFS for Shortest Path?**
- BFS explores nodes in order of distance from source
- First time we reach destination = shortest path

---

### 3. **DFS (Depth-First Search)**

**What is it?**
- Explores graph by going as deep as possible before backtracking
- Uses **recursion** (implicit stack) or explicit stack
- Explores one branch completely before trying another

**Use Case:** Graph traversal, finding connected components

**Algorithm:**
1. Start from a user, mark as visited
2. Add to result
3. For each friend:
   - If not visited, recursively call DFS on that friend

**Time Complexity:** **O(V + E)**
- Visits each vertex once
- Checks each edge once

**Space Complexity:** **O(V)**
- Recursion stack in worst case (linear graph)
- Visited set

**DFS vs BFS:**
- DFS: Goes deep, uses stack/recursion
- BFS: Goes wide, uses queue
- BFS finds shortest path, DFS doesn't guarantee it

---

### 4. **Hashing / Set**

**What is it?**
- Hash-based data structure for O(1) average lookup
- We use `unordered_set` for finding mutual friends

**Use Case:** Finding mutual friends efficiently

**Algorithm:**
1. Put all friends of User1 into a hash set: **O(k₁)**
2. For each friend of User2: **O(k₂)**
   - Check if exists in hash set: **O(1)**
   - If yes, add to mutual friends list

**Time Complexity:** **O(k₁ + k₂)**
- k₁ = number of friends of User1
- k₂ = number of friends of User2

**Without Hashing:**
- Would need nested loops: **O(k₁ × k₂)**
- Much slower for users with many friends

**Space Complexity:** **O(k₁)**
- Hash set stores User1's friends

---

## 🏗️ Project Structure

```
priyanshu-tt/
├── backend/
│   ├── main.cpp          # HTTP server with REST APIs
│   ├── Graph.h           # Graph class declaration
│   └── Graph.cpp         # Graph implementation (BFS, DFS, etc.)
├── frontend/
│   ├── index.html        # UI structure
│   ├── style.css         # Styling
│   └── script.js         # API calls using fetch
└── README.md             # This file
```

---

## 🔗 API Endpoints

| Method | Endpoint | Description | Request Body | Response |
|--------|----------|-------------|--------------|----------|
| POST | `/add-user` | Add a new user | `{"user": "Alice"}` | `{"success": true, "message": "..."}` |
| POST | `/add-friend` | Create friendship | `{"user1": "Alice", "user2": "Bob"}` | `{"success": true, "message": "..."}` |
| GET | `/friends?user=Alice` | Get user's friends | - | `{"success": true, "friends": ["Bob", "Charlie"]}` |
| GET | `/mutual?user1=Alice&user2=Bob` | Find mutual friends | - | `{"success": true, "mutualFriends": ["Charlie"]}` |
| GET | `/shortest-path?user1=Alice&user2=David` | Find shortest path (BFS) | - | `{"success": true, "path": ["Alice", "Bob", "David"]}` |

---

## 🚀 How to Run

### Prerequisites

1. **C++ Compiler** (g++ with C++11 or higher)
2. **cpp-httplib** library
3. **nlohmann/json** library

### Step 1: Install Dependencies

**On Windows (using vcpkg):**
```bash
vcpkg install cpp-httplib nlohmann-json
```

**On Linux/Mac:**
```bash
# cpp-httplib (header-only)
git clone https://github.com/yhirose/cpp-httplib.git
sudo cp cpp-httplib/httplib.h /usr/local/include/

# nlohmann/json (header-only)
git clone https://github.com/nlohmann/json.git
sudo cp json/single_include/nlohmann/json.hpp /usr/local/include/nlohmann/
```

### Step 2: Compile Backend

```bash
cd backend

# Windows (MSVC)
cl /EHsc /std:c++17 /I"path\to\vcpkg\installed\x64-windows\include" main.cpp Graph.cpp

# Linux/Mac (g++)
g++ -std=c++11 -o server main.cpp Graph.cpp -lpthread

# Or use the provided compile command:
g++ -std=c++11 -I/usr/local/include main.cpp Graph.cpp -o server -lpthread
```

### Step 3: Run Backend Server

```bash
./server
# Server will start on http://localhost:8080
```

### Step 4: Open Frontend

Open `frontend/index.html` in your browser, or navigate to:
```
http://localhost:8080/index.html
```

---

## 💡 Usage Example

1. **Add Users:**
   - Add "Alice"
   - Add "Bob"
   - Add "Charlie"
   - Add "David"

2. **Create Friendships:**
   - Alice ↔ Bob
   - Bob ↔ Charlie
   - Charlie ↔ David
   - Alice ↔ Charlie

3. **Get Friends:**
   - Search "Alice" → Shows: Bob, Charlie

4. **Find Mutual Friends:**
   - Alice & Charlie → Shows: Bob

5. **Find Shortest Path:**
   - Alice → David → Shows: Alice → Charlie → David (2 hops)

---

## 🧪 Testing the Graph

### Test Case 1: Simple Path
```
Users: A, B, C
Edges: A-B, B-C
Shortest Path A→C: A → B → C (2 hops)
```

### Test Case 2: Multiple Paths
```
Users: A, B, C, D
Edges: A-B, B-D, A-C, C-D
Shortest Path A→D: A → B → D (2 hops)
                   OR A → C → D (2 hops)
BFS will find one of them
```

### Test Case 3: No Path
```
Users: A, B, C, D
Edges: A-B, C-D
Shortest Path A→C: No path exists
```

---

## 📈 Complexity Summary

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Add User | O(1) | O(1) |
| Add Friendship | O(1) | O(1) |
| Get Friends | O(k) | O(1) |
| Mutual Friends | O(k₁ + k₂) | O(k₁) |
| Shortest Path (BFS) | O(V + E) | O(V) |
| DFS Traversal | O(V + E) | O(V) |

Where:
- V = number of users (vertices)
- E = number of friendships (edges)
- k = number of friends for a user
- k₁, k₂ = friends count for two users

---

## 🎯 Key Features Implemented

✅ Graph using Adjacency List  
✅ BFS for Shortest Path  
✅ DFS for Graph Traversal  
✅ Hashing for Mutual Friends  
✅ REST API Backend (C++)  
✅ Interactive Frontend (HTML/CSS/JS)  
✅ In-memory storage  
✅ JSON responses  

---

## 🔍 Code Highlights

### Graph Representation
```cpp
// Adjacency List: O(1) access to friends
unordered_map<string, vector<string>> adjList;
```

### BFS Implementation
```cpp
queue<string> q;                    // FIFO for level-order
unordered_set<string> visited;      // Track visited nodes
unordered_map<string, string> parent; // Reconstruct path
```

### Mutual Friends with Hashing
```cpp
unordered_set<string> friends1(adjList[user1].begin(), adjList[user1].end());
// O(1) lookup instead of O(n) search
```

---

## 🛠️ Technologies Used

**Backend:**
- C++11
- cpp-httplib (lightweight HTTP server)
- nlohmann/json (JSON parsing)

**Frontend:**
- HTML5
- CSS3 (Gradient design, animations)
- Vanilla JavaScript (Fetch API)

**Data Structures:**
- Graph (Adjacency List)
- Queue (BFS)
- Hash Set (Mutual Friends)
- Hash Map (Graph storage)

---

## 📝 Notes

- Data is stored **in-memory** (resets on server restart)
- Graph is **undirected** (friendship is mutual)
- No database required (simple and lightweight)
- CORS enabled for local development
- Frontend uses async/await for clean API calls

---

## 🎓 Learning Outcomes

After completing this project, you understand:

1. ✅ How to implement a Graph using Adjacency List
2. ✅ BFS algorithm and its application in finding shortest paths
3. ✅ DFS algorithm for graph traversal
4. ✅ Using hash sets for efficient set operations
5. ✅ Time and space complexity analysis
6. ✅ Building REST APIs in C++
7. ✅ Frontend-backend integration
8. ✅ Real-world application of DSA concepts

---

## 🚧 Future Enhancements (Optional)

- Add friend suggestions using DFS/BFS
- Find all connected components
- Detect cycles in friendship network
- Add persistence (file/database storage)
- Visualize graph using D3.js or Cytoscape.js
- Add authentication and user profiles

---

**Built with ❤️ for learning DSA concepts through practical implementation**
