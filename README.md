# Final Project - Graph Visualizer (COP3530)
A C++ application with a Qt GUI to generate, visualize, and analyze graphs using **Dijkstra** and **Bellman-Ford** algorithms.

---

## Features
- Supports both **Directed Graphs** and **Directed Acyclic Graphs (DAGs)**
- Generates random graphs with adjustable number
- Computes shortest path between any two selected nodes
- Displays result distance or "Unreachable" if no path exists
- Clear graphical layout with:
  - Circular node positioning
  - Arrows to indicate edge direction
  - Visual offset for bidirectional edges
  - Highlighted shortest path in blue

---

## Built With
- **Language:** C++
- **Framework:** Qt 6
- **Build System:** CMake
- **IDE:** CLion (compatible with Qt Creator)

---

## How to Run
### Option 1: Download Pre-built Release (Recommended / For Windows Only)
1. Go to the Releases page (https://github.com/JunhaoLiXD/FinalProject_COP3530/releases)
2. Download the latest '.zip' file
3. Extract the folder
4. Go to GraphVisualization\build\Desktop_Qt_6_8_3_MinGW_64_bit-Debug
5. Run GraphVisualization.exe

### Option 2: Build from Source (Advanced / Developer mode)
> Only needed if you want to edit the code or customize the build
#### Requirements:
- Qt 6.x
- CMake
- C++ compiler
- Qt Creator

```bash
git clone https://github.com/JunhaoLiXD/FinalProject_COP3530.git
cd FinalProject_COP3530
mkdir build && cd build
cmake ..
cmkae --build .
