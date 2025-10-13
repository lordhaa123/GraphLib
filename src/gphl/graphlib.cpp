#include "graph.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

namespace py = pybind11;

PYBIND11_MODULE(gphl, m) {
    py::class_<gphl::Edge<std::string, int>>(m, "Edge")
        .def(py::init<const std::string&, const std::string&, const int&>())
        .def("getSource", &gphl::Edge<std::string, int>::getSource)
        .def("getDestination", &gphl::Edge<std::string, int>::getDestination)
        .def("getWeight", &gphl::Edge<std::string, int>::getWeight);

    py::class_<gphl::Graph<std::string, int>>(m, "Graph")
        .def(py::init<bool>())
        .def("addNode", &gphl::Graph<std::string, int>::addNode)
        .def("hasNode", &gphl::Graph<std::string, int>::hasNode)
        .def("addEdge", &gphl::Graph<std::string, int>::addEdge, py::arg("src"), py::arg("dest"), py::arg("weight") = 0)
        .def("hasCycle", &gphl::Graph<std::string, int>::hasCycle)
        .def("nodeColoring", &gphl::Graph<std::string, int>::nodeColoring)
        .def("isBipartite", &gphl::Graph<std::string, int>::isBipartite)
        .def("connectedComponents", &gphl::Graph<std::string, int>::connectedComponents)
        .def("katzCentrality", &gphl::Graph<std::string, int>::katzCentrality, py::arg("alpha") = 0.1, py::arg("beta") = 1.0, py::arg("max_iterations") = 1000, py::arg("tolerance") = 1e-6)
        .def("minimumSpanningTree", &gphl::Graph<std::string, int>::minimumSpanningTree, py::arg("method") = "kruskal")
        .def("iterativeDFS", &gphl::Graph<std::string, int>::iterativeDFS)
        .def("shortestPath", &gphl::Graph<std::string, int>::shortestPath, py::arg("start"), py::arg("goal"), py::arg("method") = "a_star", py::arg("heuristic"));
}