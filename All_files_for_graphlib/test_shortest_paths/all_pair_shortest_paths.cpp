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
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-108,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-136,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-171,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-214,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-268,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-335,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-419,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-524,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-655,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-819,1.dimacs","r",stdin);
    freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-1024,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-1280,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-1600,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-2000,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-2500,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-3125,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-3906,1.dimacs","r",stdin);
    //freopen("C:/Users/ksute/C lab/GP_graphlib/fin_proj/All_files_for_graphlib/Graph_lib_docs/doc_shortes_path_algos/dataset/ny-4882,10.dimacs","r",stdin);
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
        //cout<<u<<":"<<v<<":"<<w<<endl;
        grp.addEdge(u-1,v-1,w);
    }

    int src = 0;
    int dest = 106;
    //int dest = 134;
    //int dest = 169;
    //int dest = 212;
    //int dest = 266;
    //int dest = 333;
    //int dest = 417;
    //int dest = 522;
    //int dest = 653;
    //int dest = 817;
    //int dest = 1022;
    //int dest = 1198;
    //int dest = 1598;
    //int dest = 1998;
    //int dest = 2498;
    //int dest = 3123;
    //int dest = 3904;
    //int dest = 4023;

    auto start_time = std::chrono::high_resolution_clock::now();
    auto path = grp.allPairsShortestPaths();
    auto end_time = std::chrono::high_resolution_clock::now();

    for(auto it:path[src][dest])
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