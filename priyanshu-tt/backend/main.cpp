#include "Graph.h"
#include "httplib.h"
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;
using namespace httplib;

Graph socialNetwork;

int main() {
    Server svr;

    svr.set_mount_point("/", "../frontend");

    svr.Post("/add-user", [](const Request& req, Response& res) {
        json response;
        try {
            json body = json::parse(req.body);
            string user = body["user"];
            
            if (user.empty()) {
                response["success"] = false;
                response["message"] = "User name cannot be empty";
                res.set_content(response.dump(), "application/json");
                return;
            }
            
            if (socialNetwork.userExists(user)) {
                response["success"] = false;
                response["message"] = "User already exists";
            } else {
                socialNetwork.addUser(user);
                response["success"] = true;
                response["message"] = "User added successfully";
            }
        } catch (exception& e) {
            response["success"] = false;
            response["message"] = "Invalid request";
        }
        
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(response.dump(), "application/json");
    });

    svr.Post("/add-friend", [](const Request& req, Response& res) {
        json response;
        try {
            json body = json::parse(req.body);
            string user1 = body["user1"];
            string user2 = body["user2"];
            
            if (user1.empty() || user2.empty()) {
                response["success"] = false;
                response["message"] = "Both user names are required";
                res.set_content(response.dump(), "application/json");
                return;
            }
            
            if (user1 == user2) {
                response["success"] = false;
                response["message"] = "Cannot add friendship with yourself";
                res.set_content(response.dump(), "application/json");
                return;
            }
            
            socialNetwork.addFriendship(user1, user2);
            response["success"] = true;
            response["message"] = "Friendship added successfully";
        } catch (exception& e) {
            response["success"] = false;
            response["message"] = "Invalid request";
        }
        
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(response.dump(), "application/json");
    });

    svr.Get("/friends", [](const Request& req, Response& res) {
        json response;
        
        if (!req.has_param("user")) {
            response["success"] = false;
            response["message"] = "User parameter is required";
            res.set_content(response.dump(), "application/json");
            return;
        }
        
        string user = req.get_param_value("user");
        
        if (!socialNetwork.userExists(user)) {
            response["success"] = false;
            response["message"] = "User does not exist";
        } else {
            vector<string> friends = socialNetwork.getFriends(user);
            response["success"] = true;
            response["friends"] = friends;
        }
        
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(response.dump(), "application/json");
    });

    svr.Get("/mutual", [](const Request& req, Response& res) {
        json response;
        
        if (!req.has_param("user1") || !req.has_param("user2")) {
            response["success"] = false;
            response["message"] = "Both user1 and user2 parameters are required";
            res.set_content(response.dump(), "application/json");
            return;
        }
        
        string user1 = req.get_param_value("user1");
        string user2 = req.get_param_value("user2");
        
        if (!socialNetwork.userExists(user1) || !socialNetwork.userExists(user2)) {
            response["success"] = false;
            response["message"] = "One or both users do not exist";
        } else {
            vector<string> mutualFriends = socialNetwork.getMutualFriends(user1, user2);
            response["success"] = true;
            response["mutualFriends"] = mutualFriends;
        }
        
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(response.dump(), "application/json");
    });

    svr.Get("/shortest-path", [](const Request& req, Response& res) {
        json response;
        
        if (!req.has_param("user1") || !req.has_param("user2")) {
            response["success"] = false;
            response["message"] = "Both user1 and user2 parameters are required";
            res.set_content(response.dump(), "application/json");
            return;
        }
        
        string user1 = req.get_param_value("user1");
        string user2 = req.get_param_value("user2");
        
        if (!socialNetwork.userExists(user1) || !socialNetwork.userExists(user2)) {
            response["success"] = false;
            response["message"] = "One or both users do not exist";
        } else {
            vector<string> path = socialNetwork.shortestPath(user1, user2);
            response["success"] = true;
            if (path.empty()) {
                response["message"] = "No path exists between users";
                response["path"] = json::array();
            } else {
                response["path"] = path;
            }
        }
        
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(response.dump(), "application/json");
    });

    cout << "Server starting on http://localhost:8080" << endl;
    cout << "Social Network Analyzer is ready!" << endl;
    
    svr.listen("0.0.0.0", 8080);
    
    return 0;
}
