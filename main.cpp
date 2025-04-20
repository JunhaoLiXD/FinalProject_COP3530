#include <QApplication>
#include "include/mainwindow.h"

/**
 * @brief Entry point of the application.
 * @param argc Argument count (from command line)
 * @param argv Argument vector (from command line)
 * @return Application exit code
 */
int main(int argc, char *argv[]) {
    // Create the Qt application object
    QApplication app(argc, argv);

    // Create and display the main application window
    MainWindow w;
    w.show();

    // Enter the Qt main event loop
    return app.exec();
}
