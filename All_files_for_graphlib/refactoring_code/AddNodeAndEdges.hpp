#include "GraphClass.hpp"

template<typename T, typename W>
Graph<T,W> :: void addNode(const T& data)
{
    if(enc.find(data) == enc.end())
    {
        enc[data] = size;
        dec[size] = data;

        adjList.push_back(vector<pair<ll,double>>());
        size++;
    }
    else
    {
        cout<<"duplicate nodes are not allowes"<<endl;
    }
}

template<typename T, typename W>
Graph<T,W> :: void addEdge(const T& src, const T& dest, const W& weight = W())
{
    int encSrc = enc[src];
    int encDest = enc[dest];
    double castWeight = (double)weight;
    //cout<<this->directed<<endl<<endl;
    if(this->directed == true)
    {
        //cout<<"hi"<<endl;
        adjList[encSrc].push_back(make_pair(encDest,castWeight));
        //edgeList.insert(Edge<T,W>(src,dest,weight));
    }
    else
    {
        adjList[encSrc].push_back(make_pair(encDest,castWeight));
        adjList[encDest].push_back(make_pair(encSrc,castWeight));
        //edgeList.insert(Edge<T,W>(src,dest,weight));
        //edgeList.insert(Edge<T,W>(dest,src,weight));
        if(!isEdgeInEdgeList[make_pair(src,dest)] && !isEdgeInEdgeList[make_pair(dest,src)])
        {     
            isEdgeInEdgeList[make_pair(src,dest)] = true;
            isEdgeInEdgeList[make_pair(dest,src)] = true;
            edgeList.push_back(Edge<T,W>(src,dest,weight));
            edgeList.push_back(Edge<T,W>(dest,src,weight));
        }

    }
}