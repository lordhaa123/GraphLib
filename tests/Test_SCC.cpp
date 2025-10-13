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
    Graph<char,int> grp(true);

    grp.addNode('a');
    grp.addNode('b');
    grp.addNode('c');
    grp.addNode('d');
    grp.addNode('e');
    grp.addNode('f');
    grp.addNode('g');
    grp.addNode('h');
    grp.addNode('i');
    grp.addNode('j');

/*edges = [('A', 'B'), ('B', 'C'), ('C', 'A'),
         ('D', 'E'), ('E', 'D'),
         ('F', 'G'), ('G', 'F'),
         ('H', 'I'), ('I', 'J'), ('J', 'H')]*/

    grp.addEdge('a','b');
    grp.addEdge('b','c');
    grp.addEdge('c','a');
    grp.addEdge('d','e');
    grp.addEdge('e','d');
    grp.addEdge('f','g');
    grp.addEdge('g','f');
    grp.addEdge('h','i');
    grp.addEdge('i','j');
    grp.addEdge('j','h');


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

    auto tarjanSCC = grp.stronglyConnectedComponents("tarjan");
    cout<<"tarjan SCC"<<endl;
    for(auto it:tarjanSCC)
    {
        for(auto xd:it)
        {
            cout<<xd<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;

    auto kosarajuSCC = grp.stronglyConnectedComponents("kosaraju");
    cout<<"kosaraju algo for SCC"<<endl;
    for(auto it:kosarajuSCC)
    {
        for(auto xd:it)
        {
            cout<<xd<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;

    return 0;
}