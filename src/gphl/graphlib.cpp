#include "graph.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

namespace py = pybind11;

PYBIND11_MODULE(gphl, m) {
    py::class_<Edge<std::string, int>>(m, "Edge")
        .def(py::init<const std::string&, const std::string&, const int&>())
        .def("getSource", &Edge<std::string, int>::getSource)
        .def("getDestination", &Edge<std::string, int>::getDestination)
        .def("getWeight", &Edge<std::string, int>::getWeight);

    py::class_<Graph<std::string, int>>(m, "Graph")
        .def(py::init<bool>())
        .def("addNode", &Graph<std::string, int>::addNode)
        .def("addEdge", &Graph<std::string, int>::addEdge, py::arg("src"), py::arg("dest"), py::arg("weight") = 0)
        .def("hasCycle", &Graph<std::string, int>::hasCycle)
        .def("nodeColoring", &Graph<std::string, int>::nodeColoring)
        .def("edgeColoring", &Graph<std::string, int>::edgeColoring)
        .def("isBipartite", &Graph<std::string, int>::isBipartite)
        .def("connectedComponents", &Graph<std::string, int>::connectedComponents)
        .def("katzCentrality", &Graph<std::string, int>::katzCentrality)
        .def("primMST", &Graph<std::string, int>::primMST)
        .def("kruskalMST", &Graph<std::string, int>::kruskalMST)
        .def("iterativeDFS", &Graph<std::string, int>::iterativeDFS)
        .def("uniformCostSearch", &Graph<std::string, int>::uniformCostSearch)
        .def("aStarSearch", &Graph<std::string, int>::aStarSearch);
}