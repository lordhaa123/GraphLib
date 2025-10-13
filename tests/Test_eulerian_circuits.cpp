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
    grp.addNode('b');
    grp.addNode('c');
    grp.addNode('d');
    grp.addNode('e');
    //grp.addNode('f');
    //grp.addNode('g');
    //('A', 'B'), ('B', 'C'), ('C', 'A'), ('C', 'D'), ('D', 'A'),('C','E'),('A','C'),('A','E')
    grp.addEdge('a', 'b');
    grp.addEdge('b', 'c');
    grp.addEdge('c', 'a');
    grp.addEdge('c', 'd');
    grp.addEdge('d', 'a');
    grp.addEdge('c', 'e');
    grp.addEdge('a', 'c');
    grp.addEdge('a', 'e');

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

    cout<<"eulerian circuits for graph with eulerian path, starting from source 'c' "<<endl;
    auto eulerianCircuitsFromSource = grp.eulerianCircuitsFromSource('c');
    int p = 0;
    for(auto it:eulerianCircuitsFromSource)
    {
        cout<<"path : "<<p<<" ::: ";
        //cout<<"("<<it.getSource()<<" , "<<it.getDestination()<<")"<<endl;
        for(auto xd:it)
        {
            cout<<"("<<xd.getSource()<<" , "<<xd.getDestination()<<") --> ";
        }
        p++;
        cout<<endl;
    }
    cout<<endl<<endl<<endl;


    cout<<"eulerian circuits from all sources, if it exists!!!!"<<endl;
    auto allSourceEulerianCircuits = grp.allSourceEulerianCircuits();
    for(auto it:allSourceEulerianCircuits)
    {
        int ptNum = 0;
        cout<<"source : "<<it.first<<endl;
        if(it.second.size())
        {        
            for(auto xd:it.second)
            {
                cout<<"circuit : "<<ptNum<<" ::: ";
                //cout<<"("<<it.getSource()<<" , "<<it.getDestination()<<")"<<endl;
                for(auto jk:xd)
                {
                    cout<<"("<<jk.getSource()<<" , "<<jk.getDestination()<<") --> ";
                }
                ptNum++;
                cout<<endl;            
            }
        }
        else
        {
            cout<<"no Eulerian circuit for the source : "<<it.first<<endl;
        }
        cout<<endl;
    }
    cout<<endl<<endl<<endl;

    return 0;
}