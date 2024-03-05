#include<bits/stdc++.h>
#include "graph.hpp"
#include<pybind11/pybind11.h>
#include<pybind11/stl.h>
#include<pybind11/complex.h>
#include<pybind11/functional.h>
#include <cstdarg>

namespace py = pybind11;
using namespace std;

PYBIND11_MODULE(graphlib,m)
{
	template<T,W>
	{
py::class_<Graph<string,int>>(m,"Graph").def("addNode",&Graph<string,int>::addNode).def(py::init<bool>()).def("addEdge",&Graph<string,int>::addEdge).def("hasCycle",&Graph<string,int>::hasCycle).def("nodeColoring",&Graph<string,int>::nodeColoring).def("edgeColoring",&Graph<string,int>::edgeColoring).def("connectedComponents",&Graph<string,int>::connectedComponents).def("katzCentrality",&Graph<string,int>::katzCentrality).def("primMST",&Graph<string,int>::primMST).def("kruskalMST",&Graph<string,int>::kruskalMST).def("iterativeDFS",&Graph<string,int>::iterativeDFS).def("uniformCostSearch",&Graph<string,int>::uniformCostSearch).def("aStarSearch",&Graph<string,int>::aStarSearch).def("print_graph",&Graph<string,int>::print_graph);
	}
}
