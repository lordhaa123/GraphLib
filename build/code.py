import graphlib

# Create an undirected graph
g = graphlib.Graph(False)

# Add nodes
g.addNode("A")
g.addNode("B")
g.addNode("C")

# Add edges
g.addEdge("A", "B", 1)
#g.addEdge("B", "C", 2)

g.print_graph()

katz = g.katzCentrality(0.1,0.2)
print(katz)
# # Run algorithms
# connected_components = g.connectedComponents()
# katz_centrality = g.katzCentrality(0.1, 1)
# prim_mst = g.primMST()

# # Print results
# print("Connected Components:", connected_components)
# print("Katz Centrality:", katz_centrality)
# print("Prim's MST:", [(e.getSource(), e.getDestination(), e.getWeight()) for e in prim_mst])
