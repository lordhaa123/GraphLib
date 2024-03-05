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
    freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/new_implemetation/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-108,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/new_implemetation/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-4882,10.dimacs","r",stdin);
    freopen("output.txt", "w", stdout);
}

int main()
{

    init_code();
    auto start = std::chrono::high_resolution_clock::now();
    Graph<int,int> grp(true);

    string a,b;
    cin>>a>>b;
    int nodes , edges;


    cin>>nodes>>edges;

    for(int i=0;i<nodes;i++)
    {
        grp.addNode(i);
    }

    for(int i=0;i<edges;i++)
    {
        cin>>a;
        int u,v,w;cin>>u>>v>>w;
        grp.addEdge(u-1,v-1,w);
    }

    int src = 0;
    int dest = 107;
    //int dest = 4023;
    auto start_time = std::chrono::high_resolution_clock::now();
    vector<int> path = grp.shortestPath(src,dest);
    auto end_time = std::chrono::high_resolution_clock::now();

    for(auto it:path)
    {
        cout<<it<<" --> ";
    }
    cout<<endl;
    auto algo = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    cout<<"algorithm run time = "<<algo.count()<<" microseconds"<<endl;

    auto complete = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start);
    cout<<"complete run time = "<<complete.count()<<" microseconds"<<endl;

    return 0;

}