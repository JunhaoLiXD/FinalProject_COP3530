#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "graphwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class provides the main application window and UI logic.
 *
 * This class connects the user interface with the underlying graph algorithms and
 * visualization logic. It allows the user to:
 * - Select graph parameters (node count, graph type)
 * - Generate a graph (either Directed or DAG)
 * - Select two nodes and compute the shortest path
 * - Display the graph and highlighted path using a GraphWidget
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the main window and initializes the UI.
     * @param parent The parent widget (optional).
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for cleaning up the UI.
     */
    ~MainWindow();

private:
    Ui::MainWindow *ui; // Pointer to the auto-generated UI object
    GraphWidget *graphWidget; // Widget used for visualizing the graph and paths
    std::vector<std::vector<Edge>> graph; // The current graph represented as an adjacency list
};
#endif // MAINWINDOW_H
