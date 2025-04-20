cmake_minimum_required(VERSION 3.16)

project(GraphVisualization VERSION 0.1 LANGUAGES CXX)

# Enable automatic handling of Qt-specific build steps
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# ============================
# Define source and header files
# ============================
set(PROJECT_SOURCES
    main.cpp
    src/mainwindow.cpp
    src/algorithm.cpp
    src/graphwidget.cpp
    ui/mainwindow.ui
)

set(PROJECT_HEADERS
    include/mainwindow.h
    include/graphwidget.h
    include/algorithm.h
    include/constants.h
)

# ============================
# Build the GUI application
# ============================
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GraphVisualization
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
    )
else()
    add_executable(GraphVisualization
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
    )
endif()

target_link_libraries(GraphVisualization PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# ============================
# Build the console benchmark tool
# ============================
add_executable(Benchmark
    src/benchmark.cpp
    src/algorithm.cpp)
set_target_properties(Benchmark PROPERTIES WIN32_EXECUTABLE FALSE)
target_include_directories(Benchmark PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ============================
# Optional: Bundle config for Windows/macOS
# ============================
set_target_properties(GraphVisualization PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# ============================
# Installation rules
# ============================
include(GNUInstallDirs)
install(TARGETS GraphVisualization
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GraphVisualization)
endif()
