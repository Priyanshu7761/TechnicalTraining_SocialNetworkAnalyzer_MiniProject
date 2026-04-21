#include "Graph.h"
#include <iostream>
#include <sstream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

Graph socialNetwork;

string urlDecode(const string& str) {
    string result;
    char ch;
    int i, ii;
    for (i = 0; i < str.length(); i++) {
        if (str[i] == '%') {
            sscanf(str.substr(i + 1, 2).c_str(), "%x", &ii);
            ch = static_cast<char>(ii);
            result += ch;
            i = i + 2;
        } else if (str[i] == '+') {
            result += ' ';
        } else {
            result += str[i];
        }
    }
    return result;
}

string getQueryParam(const string& query, const string& param) {
    size_t pos = query.find(param + "=");
    if (pos == string::npos) return "";
    
    pos += param.length() + 1;
    size_t end = query.find("&", pos);
    if (end == string::npos) end = query.length();
    
    return urlDecode(query.substr(pos, end - pos));
}

string extractJsonValue(const string& json, const string& key) {
    size_t pos = json.find("\"" + key + "\"");
    if (pos == string::npos) return "";
    
    pos = json.find(":", pos);
    if (pos == string::npos) return "";
    
    pos = json.find("\"", pos);
    if (pos == string::npos) return "";
    pos++;
    
    size_t end = json.find("\"", pos);
    if (end == string::npos) return "";
    
    return json.substr(pos, end - pos);
}

string vectorToJson(const vector<string>& vec) {
    string result = "[";
    for (size_t i = 0; i < vec.size(); i++) {
        result += "\"" + vec[i] + "\"";
        if (i < vec.size() - 1) result += ",";
    }
    result += "]";
    return result;
}

string handleRequest(const string& method, const string& path, const string& query, const string& body) {
    string response;
    string contentType = "application/json";
    
    if (method == "OPTIONS") {
        response = "";
    }
    else if (method == "POST" && path == "/add-user") {
        string user = extractJsonValue(body, "user");
        if (user.empty()) {
            response = "{\"success\":false,\"message\":\"User name cannot be empty\"}";
        } else if (socialNetwork.userExists(user)) {
            response = "{\"success\":false,\"message\":\"User already exists\"}";
        } else {
            socialNetwork.addUser(user);
            response = "{\"success\":true,\"message\":\"User added successfully\"}";
        }
    }
    else if (method == "POST" && path == "/add-friend") {
        string user1 = extractJsonValue(body, "user1");
        string user2 = extractJsonValue(body, "user2");
        if (user1.empty() || user2.empty()) {
            response = "{\"success\":false,\"message\":\"Both user names are required\"}";
        } else if (user1 == user2) {
            response = "{\"success\":false,\"message\":\"Cannot add friendship with yourself\"}";
        } else {
            socialNetwork.addFriendship(user1, user2);
            response = "{\"success\":true,\"message\":\"Friendship added successfully\"}";
        }
    }
    else if (method == "GET" && path == "/friends") {
        string user = getQueryParam(query, "user");
        if (user.empty()) {
            response = "{\"success\":false,\"message\":\"User parameter is required\"}";
        } else if (!socialNetwork.userExists(user)) {
            response = "{\"success\":false,\"message\":\"User does not exist\"}";
        } else {
            vector<string> friends = socialNetwork.getFriends(user);
            response = "{\"success\":true,\"friends\":" + vectorToJson(friends) + "}";
        }
    }
    else if (method == "GET" && path == "/mutual") {
        string user1 = getQueryParam(query, "user1");
        string user2 = getQueryParam(query, "user2");
        if (user1.empty() || user2.empty()) {
            response = "{\"success\":false,\"message\":\"Both user1 and user2 parameters are required\"}";
        } else if (!socialNetwork.userExists(user1) || !socialNetwork.userExists(user2)) {
            response = "{\"success\":false,\"message\":\"One or both users do not exist\"}";
        } else {
            vector<string> mutual = socialNetwork.getMutualFriends(user1, user2);
            response = "{\"success\":true,\"mutualFriends\":" + vectorToJson(mutual) + "}";
        }
    }
    else if (method == "GET" && path == "/shortest-path") {
        string user1 = getQueryParam(query, "user1");
        string user2 = getQueryParam(query, "user2");
        if (user1.empty() || user2.empty()) {
            response = "{\"success\":false,\"message\":\"Both user1 and user2 parameters are required\"}";
        } else if (!socialNetwork.userExists(user1) || !socialNetwork.userExists(user2)) {
            response = "{\"success\":false,\"message\":\"One or both users do not exist\"}";
        } else {
            vector<string> path = socialNetwork.shortestPath(user1, user2);
            if (path.empty()) {
                response = "{\"success\":true,\"message\":\"No path exists between users\",\"path\":[]}";
            } else {
                response = "{\"success\":true,\"path\":" + vectorToJson(path) + "}";
            }
        }
    }
    else if (method == "GET" && (path == "/" || path == "/index.html")) {
        ifstream file("../frontend/index.html");
        if (file.is_open()) {
            stringstream buffer;
            buffer << file.rdbuf();
            response = buffer.str();
            contentType = "text/html";
        } else {
            response = "<html><body><h1>404 Not Found</h1></body></html>";
            contentType = "text/html";
        }
    }
    else if (method == "GET" && path == "/style.css") {
        ifstream file("../frontend/style.css");
        if (file.is_open()) {
            stringstream buffer;
            buffer << file.rdbuf();
            response = buffer.str();
            contentType = "text/css";
        }
    }
    else if (method == "GET" && path == "/script.js") {
        ifstream file("../frontend/script.js");
        if (file.is_open()) {
            stringstream buffer;
            buffer << file.rdbuf();
            response = buffer.str();
            contentType = "application/javascript";
        }
    }
    else {
        response = "{\"success\":false,\"message\":\"Endpoint not found\"}";
    }
    
    stringstream httpResponse;
    httpResponse << "HTTP/1.1 200 OK\r\n";
    httpResponse << "Content-Type: " << contentType << "\r\n";
    httpResponse << "Access-Control-Allow-Origin: *\r\n";
    httpResponse << "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n";
    httpResponse << "Access-Control-Allow-Headers: Content-Type\r\n";
    httpResponse << "Content-Length: " << response.length() << "\r\n";
    httpResponse << "Connection: close\r\n";
    httpResponse << "\r\n";
    httpResponse << response;
    
    return httpResponse.str();
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed" << endl;
        return 1;
    }
    
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        cerr << "Socket creation failed" << endl;
        WSACleanup();
        return 1;
    }
    
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);
    
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Bind failed" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        cerr << "Listen failed" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    
    cout << "========================================" << endl;
    cout << "Server starting on http://localhost:8080" << endl;
    cout << "Social Network Analyzer is ready!" << endl;
    cout << "Open http://localhost:8080 in your browser" << endl;
    cout << "Press Ctrl+C to stop the server" << endl;
    cout << "========================================" << endl;
    
    while (true) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            continue;
        }
        
        char buffer[4096] = {0};
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        
        if (bytesReceived > 0) {
            string request(buffer);
            
            stringstream ss(request);
            string method, fullPath, httpVersion;
            ss >> method >> fullPath >> httpVersion;
            
            string path = fullPath;
            string query = "";
            size_t qPos = fullPath.find("?");
            if (qPos != string::npos) {
                path = fullPath.substr(0, qPos);
                query = fullPath.substr(qPos + 1);
            }
            
            string body = "";
            size_t bodyPos = request.find("\r\n\r\n");
            if (bodyPos != string::npos) {
                body = request.substr(bodyPos + 4);
            }
            
            string response = handleRequest(method, path, query, body);
            send(clientSocket, response.c_str(), response.length(), 0);
        }
        
        closesocket(clientSocket);
    }
    
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
