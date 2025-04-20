#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>

namespace Const{
    // Graph visual properties
    const int NODE_RADIUS = 15;
    const int GRAPH_RADIUS = 250;

    // Arrow styling
    const double ARROW_SIZE = 10.0;
    const double ARROW_OFFSET = 15.0;

    // Font
    const int FONT_SIZE = 10;
    inline QString FONT_FAMILY() {
        return "Arial";
    }

    // Canvas size
    const int MIN_WIDGET_WIDTH = 800;
    const int MIN_WIDGET_HEIGHT = 600;

    // Node numbers
    const int MIN_NODES_NUM = 3;
    const int MAX_NODES_NUM = 10;
    const int DEFAULT_NODES_NUM = 5;

    // Window title
    inline QString WINDOW_TITLE() {
        return "Graph Visualizer - Dijkstra & Bellman-Ford";
    }

    // DAG avg_degree, min_weight, max_weight
    const int DAG_AVG_DEGREE = 2;
    const int DAG_MIN_WEIGHT = -10;
    const int DAG_MAX_WEIGHT = 10;

    // Directed graph avg_degree, min_weight, max_weight
    const int DG_AVG_DEGREE = 2;
    const int DG_MIN_WEIGHT = 1;
    const int DG_MAX_WEIGHT = 10;
}
#endif // CONSTANTS_H
