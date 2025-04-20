#include "../include/graphwidget.h"
#include "../include/constants.h"
#include <QPainter>
#include <cmath>
using namespace std;

// Function to draw a directional arrow between two points
void drawArrow(QPainter &painter, QPointF from, QPointF to, double size = 10.0, double offset = 15.0) {
    QLineF line(from, to);
    double length = line.length();
    if (length == 0) return; // Avoid division by zero

    // Shorten the arrow slightly so it doesn't overlap with the circle
    QPointF adjustedTo = from + (to - from) * ((length - offset) / length);

    // Calculate the arrow slightly so it doesn't overlap with the circle
    double angle = atan2(-line.dy(), line.dx());

    // Calculate the two points that form the sides of the arrowhead
    QPointF arrowP1 = adjustedTo - QPointF(cos(angle + M_PI / 6) * size, -sin(angle + M_PI / 6) * size);
    QPointF arrowP2 = adjustedTo - QPointF(cos(angle - M_PI / 6) * size, -sin(angle - M_PI / 6) * size);

    // Create the arrowhead triangle
    QPolygonF arrowHead;
    arrowHead << adjustedTo << arrowP1 << arrowP2;

    // Draw the arrowhead in black
    painter.setBrush(Qt::black);
    painter.drawPolygon(arrowHead);
}

// Constructor: initialize custom widght for graph visualization
GraphWidget::GraphWidget(QWidget *parent)
    : QWidget{parent}
{}

// Set the graph data (adjacency list) and refresh the widget
void GraphWidget::setGraph(const vector<vector<Edge>> &g){
    graph = g;
    update(); // Trigger repaint
}

// Set the path to highlight and refresh the widget
void GraphWidget::setPath(const vector<int> &p){
    path = p;
    update(); // Trigger repaint
}


void GraphWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    int radius = Const::NODE_RADIUS; // Raidus of each node circle
    int n = graph.size(); // Number of nodes

    if (n == 0) return; // Nothing to draw

    // Calculate positions of nodes placed in a circular layout
    vector<QPoint> positions(n);
    for (int i = 0; i < n; ++i) {
        double angle = 2 * M_PI * i / n;
        int graph_radius = Const::GRAPH_RADIUS;
        int x = width() / 2 + graph_radius * cos(angle);
        int y = height() / 2 + graph_radius * sin(angle);
        positions[i] = QPoint(x, y);

        // Draw the node
        painter.setBrush(Qt::white);
        painter.drawEllipse(positions[i], radius, radius);
        painter.drawText(x - 5, y + 5, QString::number(i)); // Node label
    }

    // Lambda to check for reverse edge
    auto hasReverse = [&](int from, int to) {
        for (const auto& e : graph[to]) {
            if (e.toNode == from) return true;
        }
        return false;
    };

    // Draw all edges with weights and arrows
    for (int from = 0; from < n; ++from) {
        for (const auto &edge : graph[from]) {
            QPointF p1 = positions[from];
            QPointF p2 = positions[edge.toNode];

            // Default drawing points
            QLineF edgeLine(p1, p2); // Line between node centers
            QLineF unitLine = edgeLine.unitVector(); // Unit vector of the edge
            QPointF direction = unitLine.p2() - unitLine.p1(); // Normalized direction vector
            QPointF drawP1 = edgeLine.p1() + direction * Const::NODE_RADIUS; // Start after leaving source circle
            QPointF drawP2 = edgeLine.p2() - direction * Const::NODE_RADIUS; // End before hitting target circle

            // Offset for bidirectional edges to separate overlapping lines
            bool isBidirectional = hasReverse(from, edge.toNode);
            if (isBidirectional && from < edge.toNode) {
                QPointF offset(-edgeLine.dy(), edgeLine.dx()); // Perpendicular vector
                double len = std::hypot(offset.x(), offset.y());
                offset = (len != 0) ? offset / len * 10 : QPointF(0, 0); // Normalize and scale
                drawP1 += offset;
                drawP2 += offset;
            }

            // Draw the edge line
            painter.setPen(QPen(Qt::black, 2));
            painter.drawLine(drawP1, drawP2);

            // Draw directional arrow
            drawArrow(painter, drawP1, drawP2);

            // Determine mid-point of edge to draw the weight label
            QPointF mid = (drawP1 + drawP2) / 2;

            // Offset the label if this is one of a pair of bidirectional edges
            if (isBidirectional && from < edge.toNode) {
                QPointF offset(-edgeLine.dy(), edgeLine.dx()); // Perpendicular direction for offset
                double len = std::hypot(offset.x(), offset.y());
                if (len != 0)
                    mid += offset / len * 10; // Normalize and apply offset to shift label
            }


            // Draw the weight label
            QString weightText = QString::number(edge.weight);
            painter.setPen(Qt::black);
            painter.setFont(QFont(Const::FONT_FAMILY(), Const::FONT_SIZE));
            painter.drawText(mid, weightText);
        }
    }

    // If a path is provided, draw it in blue
    if (!path.empty()) {
        painter.setPen(QPen(Qt::blue, 3)); // Use a blue pen for highlighting the path
        for (int i = 0; i + 1 < path.size(); ++i) {
            int from = path[i];
            int to = path[i + 1];

            QPointF p1 = positions[from];
            QPointF p2 = positions[to];

            QLineF pathLine(p1, p2); // Full line from source to destination
            QLineF unit = pathLine.unitVector(); // Unit vector in the same direction
            QPointF direction = unit.p2() - unit.p1(); // Normalized direction vector

            // Trim the path ends to stop short of the node circles
            QPointF drawP1 = p1 + direction * radius;
            QPointF drawP2 = p2 - direction * radius;

            // If there's a reverse edge, offset the line so it doesn't overlap with the other direction
            if (hasReverse(from, to) && from < to) {
                QPointF offset(-pathLine.dy(), pathLine.dx()); // Perpendicular offset direction
                double len = std::hypot(offset.x(), offset.y());
                if (len != 0) {
                    offset /= len; // Normalize the offset vector
                    offset *= 10;  // Scale the offset distance
                    drawP1 += offset; // Apply to both ends
                    drawP2 += offset;
                }
            }

            painter.drawLine(drawP1, drawP2); // Draw the line
        }
    }
}
