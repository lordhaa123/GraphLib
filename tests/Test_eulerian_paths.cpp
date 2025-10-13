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
    grp.addNode('f');
    //grp.addNode('g');

    grp.addEdge('a', 'b');
    grp.addEdge('a', 'd');
    grp.addEdge('b', 'c');
    grp.addEdge('b', 'e');
    grp.addEdge('c', 'f');
    grp.addEdge('d', 'e');
    grp.addEdge('e', 'f');

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

    cout<<"eulerian path for graph with eulerian path, but no circuit , starting from source 'b' "<<endl;
    auto eulerianPathFromSource = grp.eulerianPathFromSource('b');
    int p = 0;
    for(auto it:eulerianPathFromSource)
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


    cout<<"eulerian path from all sources, if it exists!!!!"<<endl;
    auto allSourceEulerianPaths = grp.allSourceEulerianPaths();
    for(auto it:allSourceEulerianPaths)
    {
        int ptNum = 0;
        cout<<"source : "<<it.first<<endl;
        if(it.second.size())
        {        
            for(auto xd:it.second)
            {
                cout<<"path : "<<ptNum<<" ::: ";
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
            cout<<"no Eulerian path for the source : "<<it.first<<endl;
        }
        cout<<endl;
    }
    cout<<endl<<endl<<endl;

    return 0;
}