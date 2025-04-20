#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
using namespace std;

/**
 * @brief Represents a directed edge with a weight in the graph.
 */
struct Edge {
    /**
     * @brief The index of the destination node.
     */
    int toNode;

    /**
     * @brief The weight of the edge.
     */
    int weight;
};


/**
 * @brief Generate a Directed graph with weighted edges.
 * @param num_nodes The total number of nodes in the graph.
 * @param avg_degree The average number of outgoing edges per node.
 * @param min_weight The minimum weight for any edge.
 * @param max_weight The maximum weight for any edge.
 * @return adjacency list.
 */
vector<vector<Edge>> generateDirectedGraph(int num_nodes, int avg_degree, int min_weight, int max_weight);

/**
 * @brief Generates a Directed Acyclic Graph (DA Graph) with weighted edges.
 * @param num_nodes The total number of nodes in the graph.
 * @param avg_degree The average number of outgoing edges per node.
 * @param min_weight The minimum weight allowed for any edge.
 * @param max_weight The maximum weight allowed for any edge.
 * @return A vector of adjacency lists representing the DA Graph.
 */
vector<vector<Edge>> generateDAGraph(int num_nodes, int avg_degree, int min_weight, int max_weight);

/**
 * @brief Computes the shortest path from a source node to a target node and its corresponding distance using the Dijkstra's algorithm.
 * @param num_nodes The total number of nodes in the graph.
 * @param source The source node.
 * @param target The target node.
 * @param adjacencyList The adjacency list representation of the graph.
 * @return A pair containing:
 *    - A vector of node indices representing the shortest path from source to target.
 *    - An integer representing the total distance of that shortest path.
 */
pair<vector<int>, int> Dijkstra(int num_nodes, int source, int target, const vector<vector<Edge>>& adjacencyList);

/**
 * @brief Computes the shortest path from a starting node to a target node and its corresponding distance using the Bellman-Ford algorithm.
 * @param num_nodes The total number of vertices in the graph.
 * @param source The starting node.
 * @param target The ending node.
 * @param adjacencyList The adjacency list representation of the graph.
 * @return A pair containing:
 *    - A vector of node indices representing the shortest path from source to target.
 *    - An integer representing the total distance of that shortest path.
 */
pair<vector<int>, int> BellmanFord(int num_nodes, int source, int target, const vector<vector<Edge>>& adjacencyList);

#endif //ALGORITHM_H
