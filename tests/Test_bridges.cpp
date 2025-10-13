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

    auto bridges = grp.bridges();
    for(auto it:bridges)
    {
        cout<<"src: "<<it.getSource()<<" , dest: "<<it.getDestination()<<" , weight: "<<it.getWeight()<<endl;
    }
    cout<<endl;    

    return 0;
}