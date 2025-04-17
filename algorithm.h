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
    int to_node;

    /**
     * @brief The weight of the edge.
     */
    int weight;
};


/**
 * @brief Generate the graph for Dijkstra's Algorithm.
 * @param num_nodes The total number of nodes in the graph.
 * @param avg_degree The average number of outgoing edges per node.
 * @param min_weight The minimum weight for any edge.
 * @param max_weight The maximum weight for any edge.
 * @return adjacency list.
 */
vector<vector<Edge>> generateDijkstraGraph(int num_nodes, int avg_degree, int min_weight, int max_weight);


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

#endif //ALGORITHM_H