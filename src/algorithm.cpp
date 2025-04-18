#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <random>
#include <limits>
#include "algorithm.h"
using namespace std;

// Generate the graph for Dijkstra's Algorithm
vector<vector<Edge>> generateDijkstraGraph(const int num_nodes, const int avg_degree, const int min_weight, const int max_weight) {
    // use adjacency list to represent the graph
    vector<vector<Edge>> adjacencyList(num_nodes);

    // use set to store unique edges
    unordered_set<long long> edgeSet;

    srand(time(nullptr)); // seed the random number generator

    // Iterate through each node to assign outgoing edges
    for(int i = 0; i < num_nodes; i++) {

        // number of outgoing edges for the current node
        int degree = avg_degree;

        // keep assigning outgoing edges for the current node...
        while(degree > 0) {

            int from_node = i; // current node
            int to_node = rand() % num_nodes; // randomly select a target node from all nodes
            int weight; // weight for current edge
            long long edge_hash; // for identify the current edge

            // avoid self-loops
            if(from_node == to_node) {
                continue;
            }

            // Randomly generate a weight for the current outgoing edge
            weight = min_weight + rand() % (max_weight - min_weight + 1);

            // assign a unique number for the current edge
            edge_hash = static_cast<long long>(from_node) * num_nodes + to_node;

            // Check whether the current edge is unique
            if (edgeSet.find(edge_hash) == edgeSet.end()) {

                // push the target node and corresponding weight to the adjacent list
                adjacencyList[from_node].push_back({to_node, weight});
                // insert the unique edge to the set to avoid potential duplicates later
                edgeSet.insert(edge_hash);
                degree = degree-1; // finish assigning one outgoing edge for the current node
            }
        }
    }
    return adjacencyList;
}

// Generates a Directed Acyclic Graph (DA Graph) with weighted edges
// Ensures no duplicate edges and maintains acyclic property (from < to)
vector<vector<Edge>> generateDAGraph(int num_nodes, int avg_degree, int min_weight, int max_weight) {
    vector<vector<Edge>> adjacencyList(num_nodes); // Representation of the graph

    // Random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> weight_dist(min_weight, max_weight);
    uniform_int_distribution<int> node_dist(0, num_nodes - 1);

    // Small Graph (Nodes <=10)
    if(num_nodes <= 10) {
        vector<pair<int, int>> possibleEdges; // Stores all valid edges (from < to)

        // Generate all possible valid edges where from < to
        for (int from = 0; from < num_nodes; ++from) {
            for (int to = from + 1; to < num_nodes; ++to) {
                possibleEdges.emplace_back(from, to);
            }
        }

        // Shuffle the edge list to randomize edge selection
        shuffle(possibleEdges.begin(), possibleEdges.end(), gen);

        // Limit the number of edges
        int maxEdges = possibleEdges.size();
        int desiredEdges = min(avg_degree * num_nodes, maxEdges);

        // Select desired number of edges and assign random weights
        for (int i = 0; i < desiredEdges; ++i) {
            int from = possibleEdges[i].first;
            int to = possibleEdges[i].second;
            int weight = weight_dist(gen);
            adjacencyList[from].push_back({to, weight});
        }

        return adjacencyList;
    }

    // Large Graph (nodes>10)
    unordered_set<long long> edgeSet; // Store unique edges

    // Ensure each node (except the first one) has at least one incoming edge
    for(int i = 1; i < num_nodes; i++) {
        uniform_int_distribution<int> from_dist(0, i - 1);
        int fromNode = from_dist(gen);
        int toNode = i; // Ensure toNode > fromNode
        int weight = weight_dist(gen);
        long long edge_hash = static_cast<long long>(fromNode) * num_nodes + toNode; // Unique identifier for the edge

        // Add the edge if it does not already exist
        if (edgeSet.find(edge_hash) == edgeSet.end()) {
            adjacencyList[fromNode].push_back({toNode, weight});
            edgeSet.insert(edge_hash);
        }
    }

    // Add additional edges to achieve the desired average degree
    int numEdges = avg_degree * num_nodes; // Total desired edges = avg_degree * num_nodes
    while(numEdges > 0) {
        int fromNode = node_dist(gen);
        int toNode = node_dist(gen);

        // Ensure the edge maintains the acyclic property (fromNode < toNode)
        if(fromNode < toNode) {
            long long edge_hash = static_cast<long long>(fromNode) * num_nodes + toNode;
            if (edgeSet.find(edge_hash) == edgeSet.end()) { // Avoid duplicates
                int weight = weight_dist(gen);
                adjacencyList[fromNode].push_back({toNode, weight});
                edgeSet.insert(edge_hash);
                numEdges--;
            }
        }
    }
    return adjacencyList;
}


// Dijkstra's Algorithm
pair<vector<int>, int> Dijkstra(const int num_nodes, const int source, const int target, const vector<vector<Edge>>& adjacencyList) {
    // vector for updating distance
    vector<int> distance(num_nodes, numeric_limits<int>::max()); // initial distances: infinite
    // vector for updating predecessor
    vector<int> predecessor(num_nodes, -1); // initial predecessor: -1

    // min-heap priority queue
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;


    distance[source] = 0; // source node has a distance of 0
    pq.emplace(0, source);

    while(!pq.empty()) {
        // pull the top element from the priority queue
        pair<int,int> top_node = pq.top();
        int currentDist = top_node.first;
        int from_node = top_node.second;
        pq.pop();

        // if the distance found before is shorter than the current distance
        if(currentDist > distance[from_node]) {
            continue;
        }

        // Explore all neighbors of the current node
        for(auto& edge : adjacencyList[from_node]) {
            int to_node = edge.to_node;
            int weight = edge.weight;

            // Relaxation
            if(distance[from_node] + weight < distance[to_node]) {
                // update the distance
                distance[to_node] = distance[from_node] + weight;
                // update the predecessor
                predecessor[to_node] = from_node;

                pq.emplace(distance[to_node], to_node);
            }
        }
    }

    vector<int> finalPath;

    // if the target node has not been visited, which means that it is unreachable
    if (distance[target] == numeric_limits<int>::max()) {
        return {finalPath, distance[target]};
    }

    // use predecessor to track the path from the target node to source node
    for (int at = target; at != -1; at = predecessor[at]) {
        finalPath.push_back(at);
    }

    // reverse the path to get the path from the source node to target source
    reverse(finalPath.begin(), finalPath.end());

    return {finalPath, distance[target]};
}