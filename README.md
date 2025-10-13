# GraphLib

GraphLib is a C++ library with Python bindings for graph data structures and algorithms. It provides a simple and efficient way to create, manipulate, and analyze graphs.

## Features

*   **Generic Graph Representation:** Supports both directed and undirected graphs.
*   **Variety of Algorithms:** Implements a wide range of graph algorithms, including:
    *   **Cycle Detection:** `hasCycle()`
    *   **Graph Traversal:** `iterativeDFS()`
    *   **Pathfinding:** `uniformCostSearch()`, `aStarSearch()`
    *   **Minimum Spanning Tree:** `primMST()`, `kruskalMST()`
    *   **Community Detection:** `connectedComponents()`
    *   **Centrality Measures:** `katzCentrality()`
    *   **Graph Coloring:** `nodeColoring()`, `edgeColoring()`
    *   **Bipartite Checking:** `isBipartite()`

## Getting Started

### Prerequisites

*   C++ compiler (supporting C++11 or later)
*   CMake (version 3.4 or later)
*   Python (version 3.6 or later)
*   pybind11 (included as a submodule)

### Building the Library

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/your-username/GraphLib.git
    cd GraphLib
    ```

2.  **Initialize the pybind11 submodule:**
    ```bash
    git submodule update --init
    ```

3.  **Build the project:**
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

4.  **Verify the build:**
    After a successful build, you should find a `graphlib.cpython-*.so` (on Linux/macOS) or `graphlib.pyd` (on Windows) file in the `build` directory.

## Usage (Python)

Here's a simple example of how to use the `GraphLib` in Python:

```python
import graphlib

# Create a new undirected graph
g = graphlib.Graph(False)

# Add nodes
g.addNode("A")
g.addNode("B")
g.addNode("C")
g.addNode("D")

# Add edges with weights
g.addEdge("A", "B", 1)
g.addEdge("B", "C", 2)
g.addEdge("C", "D", 3)
g.addEdge("D", "A", 4)

# Perform some analysis
print("Connected Components:", g.connectedComponents())
print("Node Coloring:", g.nodeColoring())

# Find the shortest path using Uniform Cost Search
path = g.uniformCostSearch("A", "C")
print("Shortest path from A to C:", path)
```

## Testing

The project includes a `tests` directory with several C++ files for testing different functionalities of the library. To run the tests, you'll need to compile and run them individually. For example:

```bash
g++ -std=c++11 All_files_for_graphlib/tests/Test_path_finding.cpp -o test_path
./test_path
```

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue if you find a bug or have a feature request.
