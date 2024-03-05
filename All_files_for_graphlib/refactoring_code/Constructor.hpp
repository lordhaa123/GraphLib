#include "GraphClass.hpp"

template<typename T,typename W>
Graph<T,W> :: Graph(bool _directed)
{
    this->directed = _directed;
    size = 0;
}