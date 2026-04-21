#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Graph {
private:
    unordered_map<string, vector<string>> adjList;

public:
    void addUser(const string& user);
    
    void addFriendship(const string& user1, const string& user2);
    
    vector<string> getFriends(const string& user);
    
    vector<string> getMutualFriends(const string& user1, const string& user2);
    
    vector<string> shortestPath(const string& start, const string& end);
    
    void dfsTraversal(const string& start, vector<string>& result);
    
    bool userExists(const string& user);

private:
    void dfsHelper(const string& current, unordered_set<string>& visited, vector<string>& result);
};

#endif
