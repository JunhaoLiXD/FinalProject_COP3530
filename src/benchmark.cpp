#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "../include/algorithm.h"
using namespace std;


/**
 * @brief Entry point for benchmarking graph algorithms.
 *
 * This program compares the execution time of Dijkstra's and
 * Bellman-Ford algorithms on randomly generated graphs of various sizes.
 * The results are printed in a formatted table.
 */
int main() {
    // Different sizes of graphs to test performance
    vector<int> nodeCounts = {100, 1000, 10000, 100000};

    // Benchmark 1: Both Dijkstra and Bellman-Ford on general directed graphs
    cout << "| Nodes     | Dijkstra Time (s)   | Bellman-Ford Time (s) |\n";
    cout << "|-----------|---------------------|-----------------------|\n";
    for (int num_nodes : nodeCounts) {
        // Generate a random directed graph
        vector<vector<Edge>> graph_DG = generateDirectedGraph(num_nodes, 10, 1, 10);
        int source = 0;
        int target = num_nodes - 1;

        // Time Dijkstra algorithm
        auto startD = chrono::high_resolution_clock::now();
        Dijkstra(num_nodes, source, target, graph_DG);
        auto endD = chrono::high_resolution_clock::now();
        chrono::duration<double> durationD = endD - startD;

        // Time Bellman-Ford algorithm
        auto startB = chrono::high_resolution_clock::now();
        BellmanFord(num_nodes, source, target, graph_DG);
        auto endB = chrono::high_resolution_clock::now();
        chrono::duration<double> durationB = endB - startB;

        // Output formatted results for this graph size
        cout << "| " << setw(10) << left << num_nodes
             << "| " << fixed << setw(20) << setprecision(6) << durationD.count()
             << "| " << fixed << setw(22) << setprecision(6) << durationB.count()
             << "|\n";
    }

    cout << "\n\n";

    // Benchmark 2: Bellman-Ford on Directed Acyclic Graphs (DAGs)
    cout << "| Nodes     | Bellman-Ford Time (s) |\n";
    cout << "|-----------|-----------------------|\n";
    for(int num_nodes : nodeCounts) {
        // Generate a DAG
        vector<vector<Edge>> graph_DAG = generateDAGraph(num_nodes, 10, -10, 10);
        int source = 1, target = num_nodes - 1;

        // Time Bellman-Ford algorithm on the DAG
        auto startB2 = chrono::high_resolution_clock::now();
        BellmanFord(num_nodes, source, target, graph_DAG);
        auto endB2 = chrono::high_resolution_clock::now();
        chrono::duration<double> durationB2 = endB2 - startB2;

        // Output formatted result
        cout << "| " << setw(10) << left << num_nodes
             << "| " << fixed << setw(22) << setprecision(6) << durationB2.count()
             << "|\n";

    }

    return 0;
}
