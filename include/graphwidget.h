#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <vector>
#include "algorithm.h"
using namespace std;


/**
 * @brief A custom QWidget for visualizing graphs and shortest paths.
 *
 * This widget displays a directed graph using circular node layout and
 * draws arrows between connected nodes. It also supports rendering
 * the shortest path between two nodes using a highlighted color.
 */
class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructs the graph visualization widget.
     * @param parent The parent QWidget (optional).
     */
    explicit GraphWidget(QWidget *parent = nullptr);

    /**
     * @brief Sets the graph to be visualized.
     *
     * The graph should be provided as an adjacency list.
     * Calling this function triggers a repaint of the widget.
     *
     * @param graph The graph represented as an adjacency list.
     */
    void setGraph(const vector<vector<Edge>> &graph);

    /**
     * @brief Sets the path to be highlighted.
     *
     * The path should be a sequence of node indices indicating the
     * order of traversal. This is typically the result of a
     * shortest path algorithm like Dijkstra or Bellman-Ford.
     *
     * @param path A vector of node indices representing the path.
     */

    void setPath(const vector<int> &path);

protected:
    /**
     * @brief Handles the paint event to draw the graph and the path.
     * @param event The paint event information.
     */
    void paintEvent(QPaintEvent *event) override;

private:
    vector<vector<Edge>> graph; // The current graph to visualize
    vector<int> path; // The current path to highlight

signals:
};

#endif // GRAPHWIDGET_H
