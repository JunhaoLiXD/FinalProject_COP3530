#include <QLayout>
#include <QStackedLayout>
#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/constants.h"
#include "../include/algorithm.h"

// Constructor for the MainWindow class
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) // Initialize UI pointer
{
    ui->setupUi(this); // Set up widgets from .ui file
    setWindowTitle(Const::WINDOW_TITLE()); // Set window title

    // Configure node count spin box
    ui->nodeSpinBox->setRange(Const::MIN_NODES_NUM, Const::MAX_NODES_NUM); // Allow between 3 and 10 nodes
    ui->nodeSpinBox->setValue(Const::DEFAULT_NODES_NUM);   // Default value is 5

    ui->generateButton->setToolTip("Generate a graph with 3-10 nodes");
    ui->computeButton->setToolTip("Compute shortest path between selected nodes");

    graphWidget = new GraphWidget(this);
    graphWidget->setMinimumSize(Const::MIN_WIDGET_WIDTH, Const::MIN_WIDGET_HEIGHT); // Set a minimum size

    // Use a QStackedLayout to toggle between instruction text and graph view
    QStackedLayout *stackedLayout = new QStackedLayout(ui->graphContainer);
    stackedLayout->addWidget(ui->instructionLabel); // index 0: instructions shown initially
    stackedLayout->addWidget(graphWidget);          // index 1: graph view after generation
    stackedLayout->setCurrentIndex(0); // Start with instruction

    // Hide the distance label
    ui->distanceLabel->hide();

    // When "Generate Graph" button is clicked
    connect(ui->generateButton, &QPushButton::clicked, this, [=](){
        int nodes = ui->nodeSpinBox->value(); // Read number of nodes
        QString type = ui->graphTypeComboBox->currentText(); // Graph type: DAG or normal

        // Generate appropriate graph
        if(type == "Directed Acyclic Graph"){
            graph = generateDAGraph(nodes, Const::DAG_AVG_DEGREE, Const::DAG_MIN_WEIGHT, Const::DAG_MAX_WEIGHT); // DAG with possible negative weights
        }
        else{
            graph = generateDirectedGraph(nodes, Const::DG_AVG_DEGREE, Const::DG_MIN_WEIGHT, Const::DG_MAX_WEIGHT); // Standard directed graph
        }

        // Update graph view
        graphWidget->setGraph(graph);
        graphWidget->setPath({}); // Clear existing path (if any)
        stackedLayout->setCurrentIndex(1); // Switch from instruction text to graph view

        // Populate the combo boxes with node indices for path selection
        ui->fromComboBox->clear();
        ui->toComboBox->clear();
        for(int i = 0; i < nodes; i++){
            QString label = QString::number(i);
            ui->fromComboBox->addItem(label);
            ui->toComboBox->addItem(label);
        }
        ui->distanceLabel->hide();
    });

    // When "Compute Path" button is clicked
    connect(ui->computeButton, &QPushButton::clicked, this, [=](){
        int from = ui->fromComboBox->currentText().toInt(); // Source node
        int to = ui->toComboBox->currentText().toInt();     // Destination node
        QString type = ui->graphTypeComboBox->currentText();// DAR or normal

        pair<vector<int>, int> result;

        // Run appropriate algorithm
        if(type == "Directed Acyclic Graph"){
            result = BellmanFord(graph.size(), from, to, graph);
        }
        else{
            result = Dijkstra(graph.size(), from, to, graph);
            graphWidget->setPath(result.first);
        }

        // Update path visualization
        const vector<int>& path = result.first;
        graphWidget->setPath(path);

        // Show distance result to user
        int distance = result.second;
        if (path.empty() || distance == std::numeric_limits<int>::max()) {
            ui->distanceLabel->setText("Unreachable.");
        } else {
            ui->distanceLabel->setText("Shortest distance: " + QString::number(distance));
        }
        ui->distanceLabel->show();
    });

}

// Destructor to clean up UI
MainWindow::~MainWindow()
{
    delete ui;
}

