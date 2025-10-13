#pragma GCC optimize("O3")
#include "../GraphNew.hpp"
#include <chrono>
using namespace std::chrono;


#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)

using namespace std;

void init_code()
{
    fastio;
    freopen("../output.txt", "w", stdout);
}

int main()
{
    init_code();
    Graph<char,int> grp(false);

    grp.addNode('a');
    grp.addNode('c');
    grp.addNode('d');
    grp.addNode('b');
    grp.addNode('e');
    grp.addNode('f');
    grp.addNode('g');

    grp.addEdge('c','a',23);
    grp.addEdge('a','b',20);
    grp.addEdge('b','c',45);
    grp.addEdge('d','a',56);
    grp.addEdge('d','c',99);
    grp.addEdge('d','b');
    grp.addEdge('e','a',90);
    grp.addEdge('e','f',213);
    grp.addEdge('f','g',987);
    grp.addEdge('g','e',7);

    grp.printGraph();

    auto bfs = grp.bfs('c');
    for(auto it:bfs)
    {
        cout<<it<<" ";
    }
    cout<<endl<<endl;

    auto dfs = grp.iterativeDFS('a');
    for(auto it:dfs)
    {
        cout<<it<<" ";
    }
    cout<<endl<<endl;

    bool hasCycle = grp.hasCycle();
    if(hasCycle) cout<<"cyclic graph"<<endl;
    else cout<<"no cycle"<<endl;
    cout<<endl;

    cout<<"shortest path bfs(un weighted)"<<endl;
    auto shortestPathBfs = grp.shortestPath('a','d');
    for(auto it:shortestPathBfs)
    {
        cout<<it<<" ";
    }
    cout<<endl<<endl;

    cout<<"shortest path dijkstra"<<endl;
    auto shortestPathDikstra = grp.shortestPath('a','d',"dijkstra");
    for(auto it:shortestPathDikstra)
    {
        cout<<it<<" ";
    }
    cout<<endl<<endl;    

    cout<<"shortest path uniform cost search"<<endl;
    auto shortestPathUniformCostSearch = grp.shortestPath('a','d',"uniform_cost_search");
    for(auto it:shortestPathUniformCostSearch)
    {
        cout<<it<<" ";
    }
    cout<<endl<<endl;  

    cout<<"shortest path bellman ford"<<endl;
    auto shortestPathBellmanFord = grp.shortestPath('a','d',"bellman_ford");
    for(auto it:shortestPathBellmanFord)
    {
        cout<<it<<" ";
    }
    cout<<endl<<endl;

    cout<<"shortest path A Star huristic"<<endl;
    function<double(char,char)> heuristic = [](char a, char b)
    {
        return int(a)-int(b);
    };
    auto shortestPathAStar = grp.shortestPath('a','d',"bellman_ford", heuristic);
    for(auto it:shortestPathAStar)
    {
        cout<<it<<" ";
    }
    cout<<endl<<endl;

    cout<<"single source shortest paths for 'a' using bfs"<<endl;
    auto singleSourceShortestPathBfs = grp.singleSourceShortestPaths('a',"bfs");
    for(auto it:singleSourceShortestPathBfs)
    {
        cout<<"dest : "<<it.first<<" ::: ";
        for(auto xd:it.second)
        {
            cout<<xd<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;

    cout<<"single source shortest paths for 'a' using dijkstra"<<endl;
    auto singleSourceShortestPathDijkstra = grp.singleSourceShortestPaths('a',"dijkstra");
    //cout<<singleSourceShortestPathBfs.size()<<endl;
    for(auto it:singleSourceShortestPathDijkstra)
    {
        cout<<"dest : "<<it.first<<" ::: ";
        for(auto xd:it.second)
        {
            cout<<xd<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;    

    cout<<"single source shortest paths for 'a' using BellMan Ford"<<endl;
    auto singleSourceShortestPathBellmanFord = grp.singleSourceShortestPaths('a',"bellman_ford");
    //cout<<singleSourceShortestPathBfs.size()<<endl;
    for(auto it:singleSourceShortestPathBellmanFord)
    {
        cout<<"dest : "<<it.first<<" ::: ";
        for(auto xd:it.second)
        {
            cout<<xd<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;  

    cout<<"all pair shortest paths using bfs"<<endl;
    auto allPairsShortestPathsBfs = grp.allPairsShortestPaths();
    for(auto it:allPairsShortestPathsBfs)
    {
        cout<<"source : "<< it.first <<" ------ "<<endl;
        for(auto xd:it.second)
        {
            cout<<"dest : "<<xd.first<<" ::: ";
            for(auto jk:xd.second)
            {
                cout<<jk<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    cout<<endl<<endl;

    cout<<"all pair shortest paths using Dijkstra"<<endl;
    auto allPairsShortestPathsDijkstra = grp.allPairsShortestPaths("dijkstra");
    for(auto it:allPairsShortestPathsDijkstra)
    {
        cout<<"source : "<< it.first <<" ------ "<<endl;
        for(auto xd:it.second)
        {
            cout<<"dest : "<<xd.first<<" ::: ";
            for(auto jk:xd.second)
            {
                cout<<jk<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    cout<<endl<<endl;

    cout<<"all pair shortest paths using Floyd Warshall"<<endl;
    auto allPairsShortestPathsFloydWarshall = grp.allPairsShortestPaths("floyd_warshall");
    for(auto it:allPairsShortestPathsFloydWarshall)
    {
        cout<<"source : "<< it.first <<" ------ "<<endl;
        for(auto xd:it.second)
        {
            cout<<"dest : "<<xd.first<<" ::: ";
            for(auto jk:xd.second)
            {
                cout<<jk<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    cout<<endl<<endl;

    cout<<"all pair shortest paths using Jhonson's"<<endl;
    auto allPairsShortestPathsJhonson = grp.allPairsShortestPaths("jhonson");
    for(auto it:allPairsShortestPathsJhonson)
    {
        cout<<"source : "<< it.first <<" ------ "<<endl;
        for(auto xd:it.second)
        {
            cout<<"dest : "<<xd.first<<" ::: ";
            for(auto jk:xd.second)
            {
                cout<<jk<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    cout<<endl<<endl;

    return 0;
}