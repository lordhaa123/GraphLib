//#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#include "graph.hpp"

#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)

void init_code()
{
    fastio;
    freopen("output.txt", "w", stdout);
}

using namespace std;


int main()
{
    init_code();

    Graph<char,int> grp(false,'a','d','c');

    // grp.addNode('a');
    // grp.addNode('c');
    // grp.addNode('d');
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

    grp.print_graph();

    cout<<endl<<endl<<endl;


    if(grp.hasCycle() == 1)
        cout<<"has Cycle"<<endl;
    else
        cout<<"no Cycle"<<endl;

    cout<<endl<<endl;

    cout<<"Node colors:-"<<endl;
    auto node_colors = grp.nodeColoring();
    for(auto it:node_colors)
    {
        cout<<it<<" ";
    }
    cout<<endl<<endl;
    
    if(grp.isBipartite())
    {
        cout<<"it is bipartite"<<endl;
    }
    else
    {
        cout<<"not bipartite"<<endl;
    }

    cout<<endl;

    cout<<"Connected compoents"<<endl;
    auto connectedComponents = grp.connectedComponents();
    for(auto it:connectedComponents)
    {
        for(auto xd:it)
        {
            cout<<xd<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    cout<<"Kartz Centrality:-"<<endl;
    auto kratz_centrality = grp.katzCentrality(0.1,0.2);
    for(auto it:kratz_centrality)
    {
        cout<<it<<" "<<endl;
    }
    cout<<endl;

    cout<<"Prim's MST"<<endl;
    auto primMST = grp.primMST();
    for(auto it:primMST)
    {
        if(it.getSource() == it.getDestination())
            continue;
        cout<<'('<<it.getSource()<<" "<<it.getDestination()<<')'<<"  , ";
    }
    cout<<endl<<endl;

    cout<<"Krushkal MST"<<endl;
    auto kruskalMST = grp.kruskalMST();
    for(auto it:kruskalMST)
    {
        if(it.getSource() == it.getDestination())
            continue;
        cout<<'('<<it.getSource()<<" "<<it.getDestination()<<')'<<"  , ";
    }
    cout<<endl<<endl;
    
    cout<<"Iterative DFS"<<endl;
    auto iterativeDFS = grp.iterativeDFS('b');
    for(auto it:iterativeDFS)
    {
        cout<<it<<"-->";
    }
    cout<<endl<<endl;

    cout<<"Uniform Cost Search"<<endl;
    auto unifromCostSearch = grp.uniformCostSearch('a','g');
    for(auto it:unifromCostSearch)
    {
        cout<<it<<"-->";
    }
    cout<<endl<<endl;   

    cout<<"A* huristic search"<<endl;
    function<double(char,char)> huristic = [&](char node1 , char node2)
    {
        if(node1 > node2)
        {
            return 0.04335;
        }
        
        return 0.012;
    };

    auto A_start_search = grp.aStarSearch('a','g',huristic);
    for(auto it:A_start_search)
    {
        cout<<it<<"-->";
    }
    cout<<endl<<endl;

    return 0;
}

