#include "Graph.h"
#include <algorithm>

void Graph::addUser(const string& user) {
    if (adjList.find(user) == adjList.end()) {
        adjList[user] = vector<string>();
    }
}

void Graph::addFriendship(const string& user1, const string& user2) {
    addUser(user1);
    addUser(user2);
    
    adjList[user1].push_back(user2);
    adjList[user2].push_back(user1);
}

vector<string> Graph::getFriends(const string& user) {
    if (adjList.find(user) != adjList.end()) {
        return adjList[user];
    }
    return vector<string>();
}

vector<string> Graph::getMutualFriends(const string& user1, const string& user2) {
    vector<string> mutualFriends;
    
    if (adjList.find(user1) == adjList.end() || adjList.find(user2) == adjList.end()) {
        return mutualFriends;
    }
    
    unordered_set<string> friends1(adjList[user1].begin(), adjList[user1].end());
    
    for (const string& friendOfUser2 : adjList[user2]) {
        if (friends1.find(friendOfUser2) != friends1.end()) {
            mutualFriends.push_back(friendOfUser2);
        }
    }
    
    return mutualFriends;
}

vector<string> Graph::shortestPath(const string& start, const string& end) {
    vector<string> path;
    
    if (adjList.find(start) == adjList.end() || adjList.find(end) == adjList.end()) {
        return path;
    }
    
    if (start == end) {
        path.push_back(start);
        return path;
    }
    
    queue<string> q;
    unordered_map<string, string> parent;
    unordered_set<string> visited;
    
    q.push(start);
    visited.insert(start);
    parent[start] = "";
    
    bool found = false;
    
    while (!q.empty() && !found) {
        string current = q.front();
        q.pop();
        
        for (const string& neighbor : adjList[current]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent[neighbor] = current;
                q.push(neighbor);
                
                if (neighbor == end) {
                    found = true;
                    break;
                }
            }
        }
    }
    
    if (!found) {
        return path;
    }
    
    string current = end;
    while (current != "") {
        path.push_back(current);
        current = parent[current];
    }
    
    reverse(path.begin(), path.end());
    return path;
}

void Graph::dfsTraversal(const string& start, vector<string>& result) {
    if (adjList.find(start) == adjList.end()) {
        return;
    }
    
    unordered_set<string> visited;
    dfsHelper(start, visited, result);
}

void Graph::dfsHelper(const string& current, unordered_set<string>& visited, vector<string>& result) {
    visited.insert(current);
    result.push_back(current);
    
    for (const string& neighbor : adjList[current]) {
        if (visited.find(neighbor) == visited.end()) {
            dfsHelper(neighbor, visited, result);
        }
    }
}

bool Graph::userExists(const string& user) {
    return adjList.find(user) != adjList.end();
}
