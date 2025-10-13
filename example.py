import sys
sys.path.append("./build/Debug")

import gphl

# Create a new undirected graph
g = gphl.Graph(False)

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
