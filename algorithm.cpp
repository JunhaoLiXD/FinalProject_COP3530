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