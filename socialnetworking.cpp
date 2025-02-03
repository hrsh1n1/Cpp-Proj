#include<bits/stdc++.h>

using namespace std;

// Graph class to represent the social network
class SocialNetwork {
private:
    unordered_map<string, vector<string>> adjList; // Adjacency list to store friendships

public:
    // Add a new user to the social network
    void addUser(const string& user) {
        if (adjList.find(user) == adjList.end()) {
            adjList[user] = vector<string>();
            cout << "User " << user << " added to the social network.\n";
        } else {
            cout << "User " << user << " already exists.\n";
        }
    }

    // Add a friendship between two users
    void addFriendship(const string& user1, const string& user2) {
        if (adjList.find(user1) == adjList.end() || adjList.find(user2) == adjList.end()) {
            cout << "One or both users do not exist.\n";
            return;
        }
        adjList[user1].push_back(user2);
        adjList[user2].push_back(user1);
        cout << "Friendship added between " << user1 << " and " << user2 << ".\n";
    }

    // Find the shortest path between two users using BFS
    vector<string> shortestPath(const string& start, const string& end) {
        if (adjList.find(start) == adjList.end() || adjList.find(end) == adjList.end()) {
            cout << "One or both users do not exist.\n";
            return {};
        }

        queue<string> q;
        unordered_map<string, string> parent; // To store the path
        unordered_set<string> visited;

        q.push(start);
        visited.insert(start);
        parent[start] = "";

        while (!q.empty()) {
            string current = q.front();
            q.pop();

            if (current == end) {
                // Reconstruct the path
                vector<string> path;
                string node = end;
                while (node != "") {
                    path.push_back(node);
                    node = parent[node];
                }
                reverse(path.begin(), path.end());
                return path;
            }

            for (const string& friendUser : adjList[current]) {
                if (visited.find(friendUser) == visited.end()) {
                    visited.insert(friendUser);
                    parent[friendUser] = current;
                    q.push(friendUser);
                }
            }
        }

        cout << "No path exists between " << start << " and " << end << ".\n";
        return {};
    }

    // Suggest friends for a user (friends of friends)
    vector<string> suggestFriends(const string& user) {
        if (adjList.find(user) == adjList.end()) {
            cout << "User does not exist.\n";
            return {};
        }

        unordered_set<string> suggestions;
        unordered_set<string> userFriends(adjList[user].begin(), adjList[user].end());

        for (const string& friendUser : adjList[user]) {
            for (const string& friendOfFriend : adjList[friendUser]) {
                if (friendOfFriend != user && userFriends.find(friendOfFriend) == userFriends.end()) {
                    suggestions.insert(friendOfFriend);
                }
            }
        }

        return vector<string>(suggestions.begin(), suggestions.end());
    }

    // Display the social network
    void displayNetwork() {
        cout << "Social Network:\n";
        for (const auto& [user, friends] : adjList) {
            cout << user << " -> ";
            for (const string& friendUser : friends) {
                cout << friendUser << " ";
            }
            cout << "\n";
        }
    }
};

// Main function
int main() {
    SocialNetwork network;
    int choice;
    string user1, user2;

    while (true) {
        cout << "\nSocial Network Analysis\n";
        cout << "1. Add User\n";
        cout << "2. Add Friendship\n";
        cout << "3. Find Shortest Path\n";
        cout << "4. Suggest Friends\n";
        cout << "5. Display Network\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter user name: ";
                cin >> user1;
                network.addUser(user1);
                break;

            case 2:
                cout << "Enter first user: ";
                cin >> user1;
                cout << "Enter second user: ";
                cin >> user2;
                network.addFriendship(user1, user2);
                break;

            case 3:
                cout << "Enter start user: ";
                cin >> user1;
                cout << "Enter end user: ";
                cin >> user2;
                {
                    vector<string> path = network.shortestPath(user1, user2);
                    if (!path.empty()) {
                        cout << "Shortest path: ";
                        for (const string& user : path) {
                            cout << user << " ";
                        }
                        cout << "\n";
                    }
                }
                break;

            case 4:
                cout << "Enter user name: ";
                cin >> user1;
                {
                    vector<string> suggestions = network.suggestFriends(user1);
                    if (!suggestions.empty()) {
                        cout << "Suggested friends for " << user1 << ": ";
                        for (const string& friendUser : suggestions) {
                            cout << friendUser << " ";
                        }
                        cout << "\n";
                    } else {
                        cout << "No suggestions found.\n";
                    }
                }
                break;

            case 5:
                network.displayNetwork();
                break;

            case 6:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}