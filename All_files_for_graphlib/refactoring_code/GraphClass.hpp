#include<bits/stdc++.h>
#include <cstdarg>
#include "DSU.hpp"
#include "EdgeClass.hpp"
#define ll long long int

using namespace std;

const double INF = numeric_limits<double>::max();



template<typename T, typename W>
class Graph
{
    map<T,int> enc;
    map<int,T> dec;
    int idx;

    vector<vector<pair<ll,double>>> adjList;
    vector<Edge<T,W>> edgeList;
    map<pair<int,int>,bool> isEdgeInEdgeList;

    int size;
    bool directed;

    public:
        Graph(bool _directed);//1
        void addNode(const T& data); //2
        void addEdge(const T& src, const T& dest, const W& weight = W());//3
        vector<T> bfs(T start);//4
        vector<T> dfs(T start);//5
        vector<T> iterativeDFS(T start);//6
        bool hasCycle();//7
        vector<T> shortestPath(const T& start , const T& goal , const string method = "bfs" , std::function<double(T, T)> heuristic = [](T a,T b){return 0;});//8
        vector<int> shortestPathBfs(const int& start , const int& goal);//9
        vector<int> shortestPathDijkstra(const int& start, const int& goal);//10
        vector<int> shortestPathUniformCostSearch(const int& start, const int& goal);//11
        vector<int> shortestPathBellmanFord(const int& start, const int& goal);//12
        vector<int> shortestPathAStar(const int& start, const int& goal, function<double(T,T)> heuristic);//13
        map<T,vector<T>> singleSourceShortestPaths(const T& source, const string& method = "bfs");//14
        vector<vector<int>> singleSourceShortestPathsDijkstra(const int& source);//15
        vector<vector<int>> singleSourceShortestPathsBellmanFord(const int& source);//16
        map<T,map<T,vector<T>>> allPairsShortestPaths(const string& method = "bfs");//17
        vector<vector<vector<int>>> allPairsShortestPathsDijkstra();//18
        vector<vector<vector<int>>> allPairsShortestPathsFloydWarshall();//19
        vector<vector<vector<int>>> allPairsShortestPathsJhonson();//20
        vector<Edge<T,W>> minimumSpanningTree(const string& method = "kruskal");//21
        vector<pair<pair<int,int>,double>> mstKruskal();//22
        vector<pair<pair<int,int>,double>> mstPrim();//23
        vector<pair<pair<int,int>,double>> mstBoruvka();//24
        vector<T> topologicalSort();//25
        vector<int> nodeColoringHelper();//26
        map<T,int> nodeColoring();//27
        map<pair<int,int>,int> edgeColoring();//28
        bool isBipartite();//29
        vector<T> articulationPoints();//30
        bool isBiconnected();//31
        vector<Edge<T,W>> bridges();//32
        vector<vector<Edge<T,W>>> eulerianPathFromSource(T source);//33
        map<T,vector<vector<Edge<T,W>>>> allSourceEulerianPaths();//34
        vector<vector<Edge<T,W>>> eulerianCircuitsFromSource(T source);//35
        map<T,vector<vector<Edge<T,W>>>> allSourceEulerianCircuits();//36
        bool isEulerian();//37
        vector<std::vector<T>> connectedComponents();//38
        vector<vector<T>> stronglyConnectedComponents(const string& method = "tarjan");//39
        vector<vector<int>> tarjanSCC();//40
        vector<vector<int>> kosarajuSCC();//41



        //only for debugging
        void printGraph();

};
