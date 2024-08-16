#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

// Structure to represent a station
struct Station {
    string name;
    vector<pair<int, int>> connections; // {station_id, distance/time}
};

// Class to represent the Metro Network
class MetroNetwork {
private:
    unordered_map<int, Station> stations;
    int numStations;

public:
    MetroNetwork(int numStations) : numStations(numStations) {}

    // Add a station to the network
    void addStation(int id, const string &name) {
        stations[id] = Station{name, {}};
    }

    // Add a connection between two stations
    void addConnection(int from, int to, int distance) {
        stations[from].connections.push_back({to, distance});
        stations[to].connections.push_back({from, distance});
    }

    // Display connections for a given station
    void displayConnections(int id) {
        cout << "Connections for " << stations[id].name << ":\n";
        for (auto &connection : stations[id].connections) {
            cout << " -> " << stations[connection.first].name << " (Distance/Time: " << connection.second << ")\n";
        }
    }

    // Find the shortest path between two stations using Dijkstra's algorithm
    vector<int> findShortestPath(int start, int end) {
        vector<int> dist(numStations, INF);
        vector<int> prev(numStations, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int current = pq.top().second;
            pq.pop();

            if (current == end) break;

            for (auto &connection : stations[current].connections) {
                int next = connection.first;
                int weight = connection.second;

                if (dist[current] + weight < dist[next]) {
                    dist[next] = dist[current] + weight;
                    prev[next] = current;
                    pq.push({dist[next], next});
                }
            }
        }

        // Reconstruct path
        vector<int> path;
        for (int at = end; at != -1; at = prev[at])
            path.push_back(at);
        reverse(path.begin(), path.end());

        if (dist[end] == INF) {
            cout << "No path found between " << stations[start].name << " and " << stations[end].name << ".\n";
            return {};
        }

        return path;
    }

    // Calculate the fare between two stations
    int calculateFare(int start, int end) {
        vector<int> path = findShortestPath(start, end);
        if (path.empty()) return -1;

        int fare = 10; // Base fare
        int distance = 0;

        for (size_t i = 0; i < path.size() - 1; ++i) {
            int from = path[i];
            int to = path[i + 1];
            for (auto &connection : stations[from].connections) {
                if (connection.first == to) {
                    distance += connection.second;
                    break;
                }
            }
        }

        fare += (distance / 2); // Simple fare calculation based on distance
        return fare;
    }

    // User Interface: Find Route
    void findRouteUI() {
        int start, end;
        cout << "Enter starting station ID: ";
        cin >> start;
        cout << "Enter destination station ID: ";
        cin >> end;
        if((start>=0 || start==10) && (end<=18 || end==10)) {
            cout<<"Orange Line"<<endl;
        }
        if((start>=19 || start==10) && ((end>=19 && end<=33) || end==10)) {
            cout<<"Apua Line"<<endl;
        }
        if(start<=18 && end>=19 && start!=10 && end!=10) {
            cout<<"Change Orange Line to Aqua Line at Sitabuldi Exchange"<<endl;
        }
        if(start>=19 && end<=18 && start!=10 && end!=10) {
            cout<<"Change Aqua Line to Orange Line at Sitabuldi Exchange"<<endl;
        }
        vector<int> path = findShortestPath(start, end);
        if (path.empty()) return;

        cout << "Shortest path from " << stations[start].name << " to " << stations[end].name << ":\n";
        for (int station : path) {
            cout << stations[station].name << " ";
            if (station != end) cout << "-> ";
        }
        cout << endl;
    }

    // User Interface: Calculate Fare
    void calculateFareUI() {
        int start, end;
        cout << "Enter starting station ID: ";
        cin >> start;
        cout << "Enter destination station ID: ";
        cin >> end;

        int fare = calculateFare(start, end);
        if (fare != -1) {
            cout << "Fare from " << stations[start].name << " to " << stations[end].name << " is: " << fare << " units.\n";
        }
    }

    // User Interface: Display Station Information
    void displayStationInfoUI() {
        int id;
        cout << "Enter station ID: ";
        cin >> id;
        cout << "Station: " << stations[id].name << endl;
        displayConnections(id);
    }

    int searchstationid() {
        string NGPSTATnames[] = { "khapri", "new_airport", "airport_south", "airport","ujjwal_Nagar", "jaiprakash_nagar", "chhatrapati_square", "ajni_square",
        "rahate_colony", "congress_nagar", "sitabuldi_interchange", "zero_mile_freedom_park","kasturchand_park", 
        "gaddigodam", "kadvi_chowk", "indora_square","nari_road", "kamptee_road", "automotive_square", "lokmanya_nagar",
        "subhash_nagar", "rachana_ring_road_junction", "vasudev_nagar", "rto_office","university_campus", "law_college_square",
        "shankar_nagar",/*"Sitabuldi Interchange"*/ "nagpur_railway_station", "dosar_vaishya_square", "agrasen_square", 
        "chitari_oli_square", "jagnade_square", "wardhaman_nagar", "prajapati_nagar" };
        string initstat;
        string endstat;
        cout<<"If station have 2 word name have underscore in between (example:- sitabuldi_interchange)"<<endl;
        cout<<"Enter the starting station name:- ";
        cin>>initstat;
        int flagx=0;
        while(flagx!=1) {
            for(int i=0;i<34;i++) {
                if(NGPSTATnames[i] == initstat) {
                   cout<<"Station Code is :- "<<i<<endl;
                   flagx=1;
                }
            }
            if(flagx==0) {
            cout<<"Enter correct name of Station (no Capital Words):-  ";
            cin>>initstat;
            }
        }
        flagx=0;
        cout<<"enter the destination station name:- ";
        cin>>endstat;
        int flagy=0;
        int out1=0;
        while(flagy!=1) {
            for(int i=0;i<34;i++) {
                if(NGPSTATnames[i] == endstat) {
                   cout<<"Station Code is :- "<<i<<endl;
                   flagy=1;
                }
            }
            if(flagy==0) {
            cout<<"Enter correct name of Station (no Capital Words):-  ";
            cin>>endstat;
            }
        }
        flagy=1;
        return 0;
    }
    // Main User Interface
    void userInterface() {
        int choice;
        do {
            cout << "\nNagpur Metro App\n";
            cout<<  "1. Search Station Codes By Station Name\n";
            cout << "2. Find Route\n";
            cout << "3. Calculate Fare\n";
            cout << "4. Display Station Information\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    searchstationid();
                    break;
                case 2:
                    findRouteUI();
                    break;
                case 3:
                    calculateFareUI();
                    break;
                case 4:
                    displayStationInfoUI();
                    break;
                case 5:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }
};

int main() {
    // Total number of stations (Orange Line: 19, Aqua Line: 17)
    MetroNetwork metro(35);

    // Add stations for Orange Line (Line 1)
    metro.addStation(0, "Khapri");
    metro.addStation(1, "New Airport");
    metro.addStation(2, "Airport South");
    metro.addStation(3, "Airport");
    metro.addStation(4, "Ujjwal Nagar");
    metro.addStation(5, "Jaiprakash Nagar");
    metro.addStation(6, "Chhatrapati Square");
    metro.addStation(7, "Ajni Square");
    metro.addStation(8, "Rahate Colony");
    metro.addStation(9, "Congress Nagar");
    metro.addStation(10, "Sitabuldi Interchange");
    metro.addStation(11, "Zero Mile Freedom Park");
    metro.addStation(12, "Kasturchand Park");
    metro.addStation(13, "Gaddigodam");
    metro.addStation(14, "Kadvi Chowk");
    metro.addStation(15, "Indora Square");
    metro.addStation(16, "Nari Road");
    metro.addStation(17, "Kamptee Road");
    metro.addStation(18, "Automotive Square");

    // Add stations for Aqua Line (Line 2)
    metro.addStation(19, "Lokmanya Nagar");
    metro.addStation(20, "Subhash Nagar");
    metro.addStation(21, "Rachana Ring Road Junction");
    metro.addStation(22, "Vasudev Nagar");
    metro.addStation(23, "RTO Office");
    metro.addStation(24, "University Campus");
    metro.addStation(25, "Law College Square");
    metro.addStation(26, "Shankar Nagar");
    //metro.addStation(9, "Congress Nagar"); // Congress Nagar (Common Station)
    metro.addStation(10, "Sitabuldi Interchange"); // Sitabuldi Interchange (Common Station)
    metro.addStation(27, "Nagpur Railway Station");
    metro.addStation(28, "Dosar Vaishya Square");
    metro.addStation(29, "Agrasen Square");
    metro.addStation(30, "Chitari Oli Square");
    metro.addStation(31, "Jagnade Square");
    metro.addStation(32, "Wardhaman Nagar");
    metro.addStation(33, "Prajapati Nagar");

    // Add connections for Orange Line (Line 1)
    metro.addConnection(0, 1, 5);
    metro.addConnection(1, 2, 3);
    metro.addConnection(2, 3, 4);
    metro.addConnection(3, 4, 2);
    metro.addConnection(4, 5, 4);
    metro.addConnection(5, 6, 3);
    metro.addConnection(6, 7, 4);
    metro.addConnection(7, 8, 2);
    metro.addConnection(8, 9, 3);
    metro.addConnection(9, 10, 2);  // Connection to Sitabuldi Interchange
    metro.addConnection(10, 11, 3);
    metro.addConnection(11, 12, 2);
    metro.addConnection(12, 13, 3);
    metro.addConnection(13, 14, 2);
    metro.addConnection(14, 15, 4);
    metro.addConnection(15, 16, 3);
    metro.addConnection(16, 17, 4);
    metro.addConnection(17, 18, 2);

    // Add connections for Aqua Line (Line 2)
    metro.addConnection(19, 20, 3);
    metro.addConnection(20, 21, 2);
    metro.addConnection(21, 22, 4);
    metro.addConnection(22, 23, 2);
    metro.addConnection(23, 24, 3);
    metro.addConnection(24, 25, 2);
    metro.addConnection(25, 26, 3);
    //metro.addConnection(26, 9, 2);  // Connection to Congress Nagar
    metro.addConnection(26, 10, 2);  // Connection to Sitabuldi Interchange
    metro.addConnection(10, 27, 3);
    metro.addConnection(27, 28, 2);
    metro.addConnection(28, 29, 4);
    metro.addConnection(29, 30, 3);
    metro.addConnection(30, 31, 2);
    metro.addConnection(31, 32, 3);
    metro.addConnection(32, 33, 2);

    // Run the user interface
    metro.userInterface();

    return 0;
}
