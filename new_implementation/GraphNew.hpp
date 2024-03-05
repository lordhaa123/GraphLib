#include <bits/stdc++.h>
#include <cstdarg>
#include <chrono>
#include "DSU.hpp"
#include <omp.h>
#define ll long long int

using namespace std;

const double INF = numeric_limits<double>::max();

template<typename T, typename W>
class Edge
{
    private:
        T src;
        T dest;
        W  weight;
    public:
        Edge(T _src, T _dest, W _weight)
        {
            this->src = _src;
            this->dest = _dest;
            this->weight = _weight;
        }

        T getSource() const
        {
            return this->src;        
        }

        T getDestination() const
        {
            return this->dest;
        }

        W getWeight() const
        {
            return this->weight;
        }
};



template<typename T, typename W>
class Graph
{
    public:
    map<T,int> enc;
    map<int,T> dec;
    int idx;

    //vector<vector<ll>> adjMat;
    vector<vector<pair<ll,double>>> adjList;
    vector<Edge<T,W>> edgeList;
    map<pair<int,int>,bool> isEdgeInEdgeList;

    int size;
    bool directed;

        Graph(bool _directed)
        {
            this->directed = _directed;
            size = 0;
        }
        // above codes are constructurs 

        void addNode(const T& data)
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

        void addEdge(const T& src, const T& dest, const W& weight = W())
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
        
        vector<T> bfs(T start)
        {
            int startEnc = enc[start];
            //cout<<startEnc<<endl;
            queue<int> que;
            vector<bool> vis(size-1,0);
            que.push(startEnc);
            vis[startEnc] = 1;
            vector<T> ans;
            vis[startEnc] = 1;
            while(!que.empty())
            {
                int curr = que.front();que.pop();
                //vis[curr] = 1;
                //cout<<curr<<endl;
                ans.push_back(dec[curr]);
                for(auto it:adjList[curr])
                {
                    if(!vis[it.first])
                    {
                        vis[it.first] = 1;
                        que.push(it.first);
                    }
                }
            }
            return ans;
        }

        vector<T> dfs(T start)
        {
            vector<T> ans;
            int startEnc = enc[start];
            vector<bool> vis(size-1,0);

            function<void(int curr)> dfs = [&](int curr)
            {
                vis[curr] = 1;
                ans.push_back(dec[curr]);
                for(auto it:adjList[curr])
                {
                    if(!vis[it.first])
                    {
                        dfs(it.first);
                    }
                }
            };

            dfs(startEnc);
            return ans;

        }

        vector<T> iterativeDFS(T start)
        {
            int startEnc = enc[start];
            //cout<<startEnc<<endl;
            stack<int> que;
            vector<bool> vis(size-1,0);
            que.push(startEnc);
            vis[startEnc] = 1;
            vector<T> ans;
            vis[startEnc] = 1;
            while(!que.empty())
            {
                int curr = que.top();que.pop();
                //vis[curr] = 1;
                //cout<<curr<<endl;
                ans.push_back(dec[curr]);
                for(auto it:adjList[curr])
                {
                    if(!vis[it.first])
                    {
                        vis[it.first] = 1;
                        que.push(it.first);
                    }
                }
            }
            return ans;            
        }
        
        bool hasCycle()
        {
            int numNodes = size;
            vector<bool> visited(numNodes, false);
            unordered_set<int> recursionStack;

            function<bool(int)> hasCycleDFS = [&](int node)
            {
                visited[node] = true;
                recursionStack.insert(node);

                for (const pair<int, double>& neighbor : adjList[node]) {
                    int neighborNode = neighbor.first;
                    
                    if (!visited[neighborNode]) {
                        if (hasCycleDFS(neighborNode)) {
                            return true;
                        }
                    } else if (recursionStack.count(neighborNode)) {
                        return true;
                    }
                }

                recursionStack.erase(node);
                return false;
            };

            for (int i = 0; i < numNodes; i++) {
                if (!visited[i] && hasCycleDFS(i)) {
                    return true;
                }
            }

            return false;
        }
        //----------------------------------------------------------------------------------------------------------------------------------------------------

        //below will be shortest path between src and dest finding algos

        vector<T> shortestPath(const T& start , const T& goal , const string method = "a_star" , std::function<double(T, T)> heuristic = [](T a,T b){return 0;})
        {
            if(start == goal)
            {
                return vector<T>(1,start);
            }

            if(method == "bfs")
            {
                vector<int> ans = shortestPathBfs(enc[start],enc[goal]);
                vector<T> res;
                for(auto it:ans)
                {
                    res.push_back(dec[it]);
                }
                return res;
            }
            else if(method == "dijkstra")
            {
                vector<int> ans = shortestPathDijkstra(enc[start],enc[goal]);
                vector<T> res;
                for(auto it:ans)
                {
                    res.push_back(dec[it]);
                }
                return res;
            }
            else if(method == "uniform_cost_search")
            {
                vector<int> ans = shortestPathUniformCostSearch(enc[start],enc[goal]);
                vector<T> res;
                for(auto it:ans)
                {
                    res.push_back(dec[it]);
                }
                return res;                
            }
            else if(method == "bellman_ford")
            {
                vector<int> ans = shortestPathBellmanFord(enc[start],enc[goal]);
                vector<T> res;
                for(auto it:ans)
                {
                    res.push_back(dec[it]);
                }
                return res;
            }
            else if(method == "a_star")
            {
                vector<int> ans = shortestPathAStar(enc[start],enc[goal],heuristic);
                vector<T> res;
                for(auto it:ans)
                {
                    res.push_back(dec[it]);
                }
                return res;                
            }
            else
            {
                throw runtime_error("wrong method name!!");
            }
            
            return {};
        }

        vector<int> shortestPathBfs(const int& start , const int& goal)
        {
            queue<pair<int, vector<int>>> q;
            q.push({start, {start}});
            //unordered_map<int, bool> visited;
            vector<bool> vis(size-1,0);
            vis[start] = true;
            
            while (!q.empty()) {
                int current = q.front().first;
                vector<int> path = q.front().second;
                q.pop();
                
                if (current == goal) {
                    return path;
                }
                
                for (auto it : adjList[current]) {
                    int neighbor = it.first;
                    if (!vis[neighbor]) {
                        vis[neighbor] = true;
                        vector<int> newPath = path;
                        newPath.push_back(neighbor);
                        q.push({neighbor, newPath});
                    }
                }
            }
            
            return {};
        }

        vector<int> shortestPathDijkstra(const int& start, const int& goal)
        {
            int n = size-1;
            
            vector<double> distances(n, numeric_limits<double>::max());
            distances[start] = 0.0;
            
            priority_queue<pair<double, int>> pq; // Min-heap of pairs: (-distance, vertex)
            pq.push({0, start});
            
            vector<int> parent(n, -1);
            
            while (!pq.empty()) {

                int current;
                double distance;
            #pragma omp critical
                {
                    current = pq.top().second;
                    distance = -pq.top().first;
                    pq.pop();
                }
                
                if (distance > distances[current]) {
                    continue;
                }

            #pragma omp parallel for
                for (const auto& neighbor : adjList[current]) {
                    int next = neighbor.first;
                    double weight = neighbor.second;
                    double newDistance = distance + weight;
                #pragma omp critical
                    {    
                        if (newDistance < distances[next]) {
                            distances[next] = newDistance;
                            parent[next] = current;
                            pq.push({-newDistance, next});
                        }
                    }
                }
            }
            
            vector<int> path;
            int current = goal;
            
            while (current != -1) {
                path.insert(path.begin(), current);
                current = parent[current];
            }
            
            return path;            
        }

        vector<int> shortestPathUniformCostSearch(const int& start, const int& goal)
        {
            priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
            vector<int> parent(size-1, -1);
            vector<double> cost(size-1, numeric_limits<double>::max());
            
            cost[start] = 0;
            pq.push(make_pair(0, start));

            while (!pq.empty()) {
                pair<double, int> current;
                int currentNode;
                double currentCost;
            #pragma omp critical
                {
                    pair<double, int> current = pq.top();
                    pq.pop();
                    currentNode = current.second;
                    currentCost = current.first;
                }

                if (currentNode == goal) {
                    break;
                }

            #pragma omp parallel for
                for (const pair<int, double>& neighbor : adjList[currentNode]) {
                    double newCost = currentCost + neighbor.second;
                #pragma omp critical
                    {
                        if (newCost < cost[neighbor.first]) {
                            cost[neighbor.first] = newCost;
                            parent[neighbor.first] = currentNode;
                            pq.push(make_pair(newCost, neighbor.first));
                        }
                    }
                }
            }

            vector<int> path;
            int currentNode = goal;
            while (currentNode != -1) {
                path.push_back(currentNode);
                currentNode = parent[currentNode];
            }
            reverse(path.begin(),path.end());
            return path;
 
        }

        vector<int> shortestPathBellmanFord(const int& start, const int& goal)
        {
            int V = size-1;
            vector<double> distances(V, INF);
            distances[start] = 0;
            vector<int> predecessors(V, -1);

        #pragma omp parallel for 
            for (int i = 1; i < V; i++) {
                for (int u = 0; u < V; u++) {
                    for (const pair<int, double>& edge : adjList[u]) {
                        int v = edge.first;
                        double weight = edge.second;
                        if (distances[u] + weight < distances[v]) {
                            distances[v] = distances[u] + weight;
                            predecessors[v] = u;
                        }
                    }
                }
            }

            // Detect negative cycle
            for (int u = 0; u < V; u++) {
                for (const pair<int, double>& edge : adjList[u]) {
                    int v = edge.first;
                    double weight = edge.second;
                    if (distances[u] + weight < distances[v]) {
                        throw runtime_error("Negative cycle detected"); // Throw an exception
                    }
                }
            }

            vector<int> path;
            int current = goal;
            while (current != -1) {
                path.push_back(current);
                current = predecessors[current];
            }
            reverse(path.begin(), path.end());

            return path;            
        }

        vector<int> shortestPathAStar(const int& start, const int& goal, function<double(T,T)> heuristic)
        {
            int n = size-1;
            
            vector<double> distances(n, numeric_limits<double>::max());
            distances[start] = 0.0;
            
            priority_queue<pair<double, int>> pq; // Min-heap of pairs: (-distance, vertex)
            pq.push({0, start});
            
            vector<int> parent(n, -1);
            
            while (!pq.empty()) {

                int current;
                double distance;

            #pragma omp ciritcal
                {
                    current = pq.top().second;
                    distance = -pq.top().first;
                    pq.pop();
                }

                if (distance > distances[current]) {
                    continue;
                }
                
            #pragma omp parallel for
                for (const auto& neighbor : adjList[current]) {
                    int next = neighbor.first;
                    double weight = neighbor.second;
                    double newDistance = distance + weight;

                #pragma omp critical 
                    {
                        if (newDistance < distances[next]) {
                            distances[next] = newDistance;
                            parent[next] = current;
                            pq.push({-(newDistance + heuristic(dec[current],dec[next])), next});
                        }
                    }
                }
            }
            
            vector<int> path;
            int current = goal;
            
            while (current != -1) {
                path.insert(path.begin(), current);
                current = parent[current];
            }
            
            return path;              
        }

        //-------------------------------------------------------------------------------------------------------------------------------------------------------

        //below is the codes for single source shortest paths

        map<T,vector<T>> singleSourceShortestPaths(const T& source, const string& method = "dijkstra")
        {
            if(method == "bfs")
            {
                map<T,vector<T>> ans;
                // this can be parallized!!!!
                vector<T> nodes = dfs(source);
            #pragma omp parallel for reduction(= : ans)
                for(auto it:nodes)
                {
                    ans[it] = shortestPath(source,it,"bfs");
                }
                return ans;
            }
            else if(method == "dijkstra")
            {
                map<T,vector<T>> res;
                //res[dec[0]] = vector<T>(3,'b');
                //res[dec[0]].push_back('c');
                vector<vector<int>> paths = singleSourceShortestPathsDijkstra(enc[source]);
                
            #pragma omp parallel for reduction(=:res)
                for(int i=0;i<size;i++)
                {
                    //cout<<"dest : "<< i <<" :::: ";
                    for(auto xd:paths[i])
                    {
                        //cout<<xd<<" ";
                        res[dec[i]].push_back(dec[xd]);
                    }
                    //cout<<endl;
                }

                return res;
            }
            else if(method == "bellman_ford")
            {
                map<T,vector<T>> res;
                //res[dec[0]] = vector<T>(3,'b');
                //res[dec[0]].push_back('c');
                vector<vector<int>> paths = singleSourceShortestPathsBellmanFord(enc[source]);
                
            #pragma omp parallel for reduction(=:res)
                for(int i=0;i<size;i++)
                {
                    //cout<<"dest : "<< i <<" :::: ";
                    for(auto xd:paths[i])
                    {
                        //cout<<xd<<" ";
                        res[dec[i]].push_back(dec[xd]);
                    }
                    //cout<<endl;
                }
                return res;                
            }
            else{
                throw runtime_error("wrong Method name!!");
            }
            return map<T,vector<T>>();
        } 

        vector<vector<int>> singleSourceShortestPathsDijkstra(const int& source)
        {
            int n = size; // Number of nodes in the graph
            vector<vector<int>> paths(n); // To store the paths
            
            vector<double> distance(n, INF);
            vector<int> parent(n, -1);
            vector<bool> visited(n, false);
            
            priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
            pq.push(make_pair(0.0, source));
            distance[source] = 0.0;
            
            while (!pq.empty()) {
                int u = pq.top().second;
                pq.pop();
                
                if (visited[u]) continue;
                visited[u] = true;
                
                for (const auto& neighbor : adjList[u]) {
                    int v = neighbor.first;
                    double weight = neighbor.second;
                    
                    if (distance[u] + weight < distance[v]) {
                        distance[v] = distance[u] + weight;
                        parent[v] = u;
                        pq.push(make_pair(distance[v], v));
                    }
                }
            }
        #pragma omp parallel for reduction(=:paths)
            for (int i = 0; i < n; i++) {
                if (distance[i] == INF) {
                    paths[i] = vector<int>();
                    continue;
                }
                
                int current = i;
                while (current != -1) {
                    paths[i].insert(paths[i].begin(), current);
                    current = parent[current];
                }
            }
            
            return paths;            
        }

        vector<vector<int>> singleSourceShortestPathsBellmanFord(const int& source)
        {
            int n = adjList.size(); // Number of nodes in the graph
            vector<vector<int>> paths(n); // To store the paths
            
            vector<double> distance(n, INF);
            vector<int> parent(n, -1);
            distance[source] = 0.0;
            
        #pragma omp parallel for reduction(=:distance) reduction(=:parent)
            for (int i = 0; i < n - 1; i++) {
                for (int u = 0; u < n; u++) {
                    for (const auto& neighbor : adjList[u]) {
                        int v = neighbor.first;
                        double weight = neighbor.second;
                        
                        if (distance[u] + weight < distance[v]) 
                        {
                        #pragma omp cirtical
                            {
                                distance[v] = distance[u] + weight;
                                parent[v] = u;
                            }
                        }
                    }
                }
            }
            
            // Check for negative cycles
        #pragma omp parallel
        {
            bool local_negative_cycle = false;
            #pragma omp for
            for (int u = 0; u < n; u++) {
                for (const auto& neighbor : adjList[u]) {
                    int v = neighbor.first;
                    double weight = neighbor.second;
                    
                    if (distance[u] + weight < distance[v]) {
                        local_negative_cycle = true;
                    }
                }
            }

            #pragma omp critical
            {
                if (local_negative_cycle) {
                    throw runtime_error("Negative cycle detected.");
                }
            }
        }

        //     for (int u = 0; u < n; u++) {
        //         for (const auto& neighbor : adjList[u]) {
        //             int v = neighbor.first;
        //             double weight = neighbor.second;
                    
        //             if (distance[u] + weight < distance[v]) {
        //                 throw runtime_error("Negative cycle detected.");
        //             }
        //         }
        //     }

        #pragma omp parallel for   
            for (int i = 0; i < n; i++) {
                if (distance[i] == INF) {
                    paths[i] = vector<int>();
                    continue;
                }
                
                int current = i;
                while (current != -1) {
                    paths[i].insert(paths[i].begin(), current);
                    current = parent[current];
                }
            }
            
            return paths;
        }
        // ------------------------------------------------------------------------------------------------------------------------------------------------------
        //below is the code for all pairs shortest paths

        map<T,map<T,vector<T>>> allPairsShortestPaths(const string& method = "dijkstra")
        {
            if(method == "bfs")
            {
                // this can be parallized!!!!
                map<T,map<T,vector<T>>> res;
                // auto start_time = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for reduction(=:res)
                for(int i=0;i<size;i++)
                {
                    res[dec[i]] = singleSourceShortestPaths(dec[i],"bfs");
                    //res.push_back(singleSourceShortestPaths(dec[i],"bfs"));
                }
                // auto end_time = std::chrono::high_resolution_clock::now();
                // std::chrono::duration<double> duration= end_time - start_time;
                // cout<<"werhbfjhuisdbgds    :::::::    "<<duration.count()<<endl; 
                return res;
            }
            else if(method == "dijkstra")
            {
                // this can be parallized!!!!
                map<T,map<T,vector<T>>> res;
                vector<vector<vector<int>>> ans = allPairsShortestPathsDijkstra();
            #pragma omp parallel for reduction(=:res)
                for(int i=0;i<size;i++)
                {                        
                    map<T,vector<T>> temp;
                #pragma omp parallel for reduction(=:temp)
                    for(int j=0;j<size;j++)
                    {
                        for(auto it:ans[i][j])
                        {
                            temp[dec[j]].push_back(dec[it]);
                        }
                    }
                    res[dec[i]] = temp;
                }
                return res;                
            }
            else if(method == "floyd_warshall" || method == "bellman_ford")
            {
                map<T,map<T,vector<T>>> res;
                vector<vector<vector<int>>> ans = allPairsShortestPathsFloydWarshall();
            #pragma omp parallel for reduction(=:res)
                for(int i=0;i<size;i++)
                {                        
                    map<T,vector<T>> temp;
                #pragma omp parallel for reduction(=:temp)
                    for(int j=0;j<size;j++)
                    {
                        for(auto it:ans[i][j])
                        {
                            temp[dec[j]].push_back(dec[it]);
                        }
                    }
                    res[dec[i]] = temp;
                }
                return res;
            }
            else if(method == "jhonson")
            {
                map<T,map<T,vector<T>>> res;
                vector<vector<vector<int>>> ans = allPairsShortestPathsJhonson();
            #pragma omp parallel for reduction(=:res)
                for(int i=0;i<size;i++)
                {                        
                    map<T,vector<T>> temp;
                #pragma omp parallel for reduction(=:temp)
                    for(int j=0;j<size;j++)
                    {
                        for(auto it:ans[i][j])
                        {
                            temp[dec[j]].push_back(dec[it]);
                        }
                    }
                    res[dec[i]] = temp;
                }
                return res;                
            }
            else
            {
                throw runtime_error("wrong method!!!");
            }
            return map<T,map<T,vector<T>>>();
        }

        vector<vector<vector<int>>> allPairsShortestPathsDijkstra()
        {
            int n = size;
            vector<vector<vector<int>>> ans(n);

        #pragma omp parallel for reduction(=:ans)    
            for(int i=0;i<n;i++)
            {
                ans[i] = singleSourceShortestPathsDijkstra(i);
            }

            return ans;
        }

        vector<vector<vector<int>>> allPairsShortestPathsFloydWarshall()
        {
            int n = size;
            vector<vector<vector<int>>> paths(n, vector<vector<int>>(n));
            vector<vector<double>> dist(n, vector<double>(n, INF));

        #pragma omp parallel for reduction(=:dist) reduction(=:paths)
            for (int i = 0; i < n; i++) {
                dist[i][i] = 0;
                for (const auto& edge : adjList[i]) {
                    int v = edge.first;
                    double weight = edge.second;
                    dist[i][v] = weight;
                    paths[i][v] = {i, v};  // Initialize paths
                }
            }
            
            
            for (int k = 0; k < n; k++) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            paths[i][j] = paths[i][k];  // Update path
                            paths[i][j].insert(paths[i][j].end(), paths[k][j].begin() + 1, paths[k][j].end());
                        }
                    }
                }
            }


            return paths;         
        }

        vector<vector<vector<int>>> allPairsShortestPathsJhonson()
        {
            int n = size;
            vector<double> h(n, 0); // Potential values for Bellman-Ford

            // Step 1: Bellman-Ford algorithm to re-weight edges
            vector<double> dist(n, INF);
            dist[0] = 0;
            for (int i = 0; i < n - 1; i++) {
                for (int u = 0; u < n; u++) {
                #pragma omp parallel for reduction(=:dist)
                    for (const auto& edge : adjList[u]) {
                        int v = edge.first;
                        double weight = edge.second + h[u] - h[v];
                        if (dist[u] + weight < dist[v]) {
                            dist[v] = dist[u] + weight;
                        }
                    }

                }
            }

            // Step 2: Create new graph with re-weighted edges
            vector<vector<pair<int, double>>> newGraph(n);
        #pragma omp parallel for reduction(=:newGraph)
            for (int u = 0; u < n; u++) {
                for (const auto& edge : adjList[u]) {
                    int v = edge.first;
                    double weight = edge.second + h[u] - h[v];
                    newGraph[u].emplace_back(v, weight);
                }
            }

            vector<vector<vector<int>>> allPaths(n, vector<vector<int>>(n));

            // Step 3: Run Dijkstra's algorithm for all pairs of vertices
            for (int u = 0; u < n; u++) {
                priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
                vector<double> dist(n, INF);
                vector<int> prev(n, -1);

                dist[u] = 0;
                pq.emplace(0, u);

                while (!pq.empty()) {
                    int current = pq.top().second;
                    double currentDist = pq.top().first;
                    pq.pop();

                    if (currentDist > dist[current]) {
                        continue;
                    }

                    for (const pair<int, double>& edge : newGraph[current]) {
                        int v = edge.first;
                        double weight = edge.second;

                        if (currentDist + weight < dist[v]) {
                            dist[v] = currentDist + weight;
                            prev[v] = current;
                            pq.emplace(dist[v], v);
                        }
                    }
                }

                // Step 4: Construct paths from predecessors
            #pragma omp parallel for reduction(=:allPaths)
                for (int v = 0; v < n; v++) {
                    if (prev[v] != -1) {
                        int current = v;
                        while (current != -1) {
                            allPaths[u][v].insert(allPaths[u][v].begin(), current);
                            current = prev[current];
                        }
                    }
                }
            }

            return allPaths;           
        }


        //------------------------------------------------------------------------------------------------------------------------------------------------------
        // below is the code for all Minimum Spanning Tree generation

        vector<Edge<T,W>> minimumSpanningTree(const string& method = "kruskal")
        {
            if(method == "kruskal")
            {
                vector<Edge<T,W>> ans;
                vector<pair<pair<int,int>,double>> temp = mstKruskal();
                for(auto it:temp)
                {
                    ans.push_back(Edge<T,W>(dec[it.first.first],dec[it.first.second],it.second));
                    //cout<<"src: "<<ans[ans.size()-1].getSource()<<" , dest: "<<ans[ans.size()-1].getDestination()<<" , weight: "<<ans[ans.size()-1].getWeight()<<endl;
                    //cout<<"src: "<<it.first.first<<" , dest: "<<it.first.second<<" , weight: "<<it.second<<endl;
                }
                return ans;
            }
            else if(method == "prim")
            {
                vector<Edge<T,W>> ans;
                vector<pair<pair<int,int>,double>> temp = mstPrim();
                for(auto it:temp)
                {
                    ans.push_back(Edge<T,W>(dec[it.first.first],dec[it.first.second],it.second));
                    //cout<<"src: "<<ans[ans.size()-1].getSource()<<" , dest: "<<ans[ans.size()-1].getDestination()<<" , weight: "<<ans[ans.size()-1].getWeight()<<endl;
                    //cout<<"src: "<<it.first.first<<" , dest: "<<it.first.second<<" , weight: "<<it.second<<endl;
                }
                return ans;                
            }
            else if(method == "boruvka")
            {
                vector<Edge<T,W>> ans;
                vector<pair<pair<int,int>,double>> temp = mstBoruvka();
                for(auto it:temp)
                {
                    ans.push_back(Edge<T,W>(dec[it.first.first],dec[it.first.second],it.second));
                    //cout<<"src: "<<ans[ans.size()-1].getSource()<<" , dest: "<<ans[ans.size()-1].getDestination()<<" , weight: "<<ans[ans.size()-1].getWeight()<<endl;
                    //cout<<"src: "<<it.first.first<<" , dest: "<<it.first.second<<" , weight: "<<it.second<<endl;
                }
                return ans;                   
            }
            else
            {
                throw runtime_error("wrong method!!!");
            }
            return vector<Edge<T,W>>();
        }

        vector<pair<pair<int,int>,double>> mstKruskal()
        {
            int n = size;
            vector<pair<pair<int, int>, double>> mstEdges;

            vector<pair<double, pair<int, int>>> edges;
            for (int u = 0; u < n; u++) {
                for (const auto &edge : adjList[u]) {
                    int v = edge.first;
                    double weight = edge.second;
                    edges.push_back({weight, {u, v}});
                }
            }

            sort(edges.begin(), edges.end());

            DSU dsu(n);
            for (const auto &edge : edges) {
                int u = edge.second.first;
                int v = edge.second.second;
                double weight = edge.first;

                if (dsu.leader(u) != dsu.leader(v)) {
                    mstEdges.push_back({{u, v}, weight});
                    dsu.merge(u, v);
                }
            }

            return mstEdges;
        }

        vector<pair<pair<int,int>,double>> mstPrim()
        {
            int n = size;
            vector<pair<pair<int, int>, double>> mst; // The Minimum Spanning Tree
            vector<bool> visited(n, false); // Track visited nodes
            vector<double> key(n, numeric_limits<double>::max()); // Minimum weights to each node
            vector<int> parent(n, -1); // Parent of each node in MST

            // Custom comparator for priority queue
            auto compare = [](const pair<int, double>& a, const pair<int, double>& b) {
                return a.second > b.second;
            };
            priority_queue<pair<int, double>, vector<pair<int, double>>, decltype(compare)> pq(compare);

            // Start with the first node
            key[0] = 0.0;
            pq.push(make_pair(0, 0.0));

            while (!pq.empty()) {
                int u = pq.top().first;
                pq.pop();

                if (visited[u])
                    continue;

                visited[u] = true;

                // Add the edge to the MST
                if (parent[u] != -1) {
                    mst.push_back(make_pair(make_pair(parent[u], u), key[u]));
                }

                for (const pair<int, double>& neighbor : adjList[u]) {
                    int v = neighbor.first;
                    double weight = neighbor.second;

                    if (!visited[v] && weight < key[v]) {
                        parent[v] = u;
                        key[v] = weight;
                        pq.push(make_pair(v, key[v]));
                    }
                }
            }

            return mst;            
        }

        vector<pair<pair<int,int>,double>> mstBoruvka()
        {
            int n = size;
            vector<pair<pair<int, int>, double>> mstEdges;

            DSU dsu(n);

            while (signed(mstEdges.size()) < (n - 1)) {
                vector<pair<pair<int, int>, double>> cheapestEdge(n, {{-1, -1}, INF});

                for (int u = 0; u < n; u++) {
                    for (const auto& edge : adjList[u]) {
                        int v = edge.first;
                        double weight = edge.second;
                        int rootU = dsu.leader(u);
                        int rootV = dsu.leader(v);

                        if (rootU != rootV && weight < cheapestEdge[rootU].second) {
                            cheapestEdge[rootU] = {{u, v}, weight};
                        }
                    }
                }

                for (int u = 0; u < n; u++) {
                    if (cheapestEdge[u].first.first != -1) {
                        int rootU = dsu.leader(cheapestEdge[u].first.first);
                        int rootV = dsu.leader(cheapestEdge[u].first.second);

                        if (rootU != rootV) {
                            mstEdges.push_back(cheapestEdge[u]);
                            dsu.merge(rootU, rootV);
                        }
                    }
                }
            }

            return mstEdges;
        }       

        // ------------------------------------------------------------------------------------------------------------------------------------------------------
        // below is the code for toposort of a graph , it uses khan's algorithm , and the functions requried for toposort is also defined

        vector<T> topologicalSort()
        {
            if(directed == false)
            {
                throw runtime_error("Graph is not a Directed Acyclic Graph (DAG)");
            }
            else
            {
                function<vector<int>()> topoHelper = [&]()
                {
                    int n = size;
                    vector<int> inDegree(n, 0);
                    
                    // Calculate in-degrees of all nodes
                    for (int u = 0; u < n; u++) {
                        for (const auto& edge : adjList[u]) {
                            int v = edge.first;
                            inDegree[v]++;
                        }
                    }
                    
                    queue<int> q;
                    for (int u = 0; u < n; u++) {
                        if (inDegree[u] == 0) {
                            q.push(u);
                        }
                    }
                    
                    vector<int> topoOrder;
                    
                    while (!q.empty()) {
                        int u = q.front();
                        q.pop();
                        topoOrder.push_back(u);
                        
                        for (const auto& edge : adjList[u]) {
                            int v = edge.first;
                            inDegree[v]--;
                            if (inDegree[v] == 0) {
                                q.push(v);
                            }
                        }
                    }
                    
                    // Check if graph is not a DAG (cycle exists)
                    if (signed(topoOrder.size()) != n) {
                        throw runtime_error("Graph is not a Directed Acyclic Graph (DAG)");
                    }
                    
                    return topoOrder;                    
                };

                vector<int> temp = topoHelper();
                vector<T> ans(size);
                for(int i=0;i<size;i++)
                {
                    ans[i] = dec[temp[i]];
                }
                return ans;
            }
            return vector<T>();
        }

        //------------------------------------------------------------------------------------------------------------------------------------------------------
        //below is the code for node coloring , is Bipartite, edge coloring and try coloring with n colors

            vector<int> nodeColoringHelper()
            {
                int numNodes = size;
                vector<int> colors(numNodes, -1); // Initialize all nodes with no color assigned

                unordered_map<int, set<int>> colorToNodes;

                // Iterate through each node and assign colors
                for (int node = 0; node < numNodes; node++) {
                    set<int> usedColors;

                    // Check colors of adjacent nodes and mark them as used
                    for (auto& neighbor : adjList[node]) {
                        int neighborNode = neighbor.first;
                        if (colors[neighborNode] != -1) {
                            usedColors.insert(colors[neighborNode]);
                        }
                    }

                    // Find the smallest available color
                    for (int color = 0; color < numNodes; color++) {
                        if (usedColors.find(color) == usedColors.end()) {
                            colors[node] = color;
                            colorToNodes[color].insert(node);
                            break;
                        }
                    }
                }

                // for (int color = 0; color < numNodes; color++) {
                //     cout << "Color " << color << " : ";
                //     for (auto node : colorToNodes[color]) {
                //         cout << node << " ";
                //     }
                //     cout << endl;
                // }
                return colors;                
            };

        map<T,int> nodeColoring()
        {
            map<T,int> ans;
            vector<int> temp = nodeColoringHelper();
            for(int i=0;i<size;i++)
            {
                ans[dec[i]] = temp[i];
            }
            return ans;
        }

        map<pair<int,int>,int> edgeColoring();


        bool isBipartite()
        {
            vector<int> temp = nodeColoringHelper();
            set<int> st;
            for(auto it:temp)
            {
                st.insert(it);
            }
            if(st.size() <= 2)
                return true;
            return false;
        }

        //------------------------------------------------------------------------------------------------------------------------------------------------------
        // below is the code to find articulation points of a graph (cut vertices) and is_biconnected graph

        vector<T> articulationPoints()
        {
            // dfs algo to find articulation points
            if(directed == true)
            {
                throw runtime_error("not implemented for directed");
            }
            //int n = size;
            vector<int> vis(size,0);

            function<vector<int>()> articulationPointsHelper = [&]()
            {
                int numNodes = size;
                vector<int> disc(numNodes, -1);
                vector<int> low(numNodes, -1);
                vector<bool> visited(numNodes, false);
                unordered_set<int> articulationPoints;
                int time = 0;

                function<void(int,int)> dfsArticulationPoints = [&](int node, int parent)
                {
                    visited[node] = true;
                    disc[node] = low[node] = ++time;
                    int children = 0;

                    for (const pair<int, double>& edge : adjList[node]) {
                        int neighbor = edge.first;
                        if (!visited[neighbor]) {
                            children++;
                            dfsArticulationPoints(neighbor, node);
                            low[node] = min(low[node], low[neighbor]);

                            if (low[neighbor] >= disc[node] && parent != -1) {
                                articulationPoints.insert(node);
                            }
                        } else if (neighbor != parent) {
                            low[node] = min(low[node], disc[neighbor]);
                        }
                    }

                    if (parent == -1 && children > 1) {
                        articulationPoints.insert(node);
                    }
                };

                for (int i = 0; i < numNodes; ++i) {
                    if (!visited[i]) {
                        dfsArticulationPoints(i, -1);
                    }
                }

                return vector<int>(articulationPoints.begin(), articulationPoints.end());
            };
            

            vector<T> ans;
            vector<int> temp = articulationPointsHelper();
            
            for(auto it:temp)
            {
                if(vis[it] == 0)
                {
                    vis[it] = 1;
                    ans.push_back(dec[it]);
                }
            }
            
            return ans;
        }

        bool isBiconnected()
        {
            auto temp = articulationPoints();
            if(temp.size() > 0)
                return false;
            return true;
        }

        //-------------------------------------------------------------------------------------------------------------------------------------------------------
        // below is the code to find the bridges in the graph

        vector<Edge<T,W>> bridges()
        {
            int n = adjList.size(); // Number of vertices in the graph
            vector<bool> visited(n, false); // To keep track of visited vertices
            vector<int> disc(n, 0); // Discovery time of vertices
            vector<int> low(n, 0); // Lowest discovery time reachable from the vertex
            vector<pair<int, int>> bridges; // Store the bridge edges

            int time = 0; // Initialize time

            // DFS function to find bridges
            function<void(int, int)> dfs = [&](int u, int parent) {
                visited[u] = true;
                disc[u] = low[u] = ++time;

                for (auto& neighbor : adjList[u]) {
                    int v = neighbor.first;
                    if (v == parent)
                        continue;

                    if (!visited[v]) {
                        dfs(v, u);
                        low[u] = min(low[u], low[v]);
                        
                        if (low[v] > disc[u]) {
                            bridges.push_back({u, v});
                        }
                    } else {
                        low[u] = min(low[u], disc[v]);
                    }
                }
            };

            // Call DFS for each unvisited vertex
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    dfs(i, -1);
                }
            }

            // Construct the result vector with pair<pair<int, int>, double>
            vector<Edge<T,W>> result;
            for (auto bridge : bridges) {
                int u = bridge.first;
                int v = bridge.second;
                for (auto& neighbor : adjList[u]) {
                    if (neighbor.first == v) {
                        result.push_back(Edge<T,W>(dec[u],dec[v],neighbor.second));
                        //result.push_back({{u, v}, neighbor.second});
                        break;
                    }
                }
            }

            return result;            
        }

        //------------------------------------------------------------------------------------------------------------------------------------------------------
        // below is the code for eulerian paths and circuits
        
        vector<vector<Edge<T,W>>> eulerianPathFromSource(T source)
        {
            vector<vector<Edge<T,W>>> ans;
            int srcEnc = enc[source];
            //cout<<"hi"<<endl;
            set<vector<pair<int,int>>> result;
            map<pair<int,int>,bool> visEdge;
            vector<pair<int,int>> curPath;
            vector<Edge<T,W>> temp_edge_list(edgeList.begin(),edgeList.end());
            int numEdges = temp_edge_list.size();
            if(!directed)
                numEdges/=2;
            //cout<<numEdges<<endl;
            function<void(int)> dfs = [&](int cur)
            {
                //cout<<dec[cur]<<endl;
                //cout<<curPath.size()<<endl;
                if(signed(curPath.size()) == numEdges)
                {
                    result.insert(curPath);
                }

                for(auto it:adjList[cur])
                {
                    int neighbor = it.first;
                    if(!visEdge[make_pair(cur,neighbor)])
                    {
                        visEdge[make_pair(cur,neighbor)] = true;
                        visEdge[make_pair(neighbor,cur)] = true;
                        curPath.push_back(make_pair(cur,neighbor));
                        dfs(neighbor);
                        curPath.pop_back();
                        visEdge[make_pair(cur,neighbor)] = false;
                        visEdge[make_pair(neighbor,cur)] = false;
                    }
                }

            };

            dfs(srcEnc);

            //cout<<result.size()<<endl;
            //vector<vector<pair<int,int>>> temp(result.begin(),result.end());
            for(auto it:result)
            {
                vector<Edge<T,W>> temp;
                for (auto ed : it) {
                    int u = ed.first;
                    int v = ed.second;
                    for (auto& neighbor : adjList[u]) {
                        if (neighbor.first == v) {
                            temp.push_back(Edge<T,W>(dec[u],dec[v],neighbor.second));
                            break;
                        }
                    }
                }
                ans.push_back(temp);
            }

            return ans;
        }

        map<T,vector<vector<Edge<T,W>>>> allSourceEulerianPaths()
        {
            map<T,vector<vector<Edge<T,W>>>> ans;
            for(auto it:enc)
            {
                ans[it.first] = eulerianPathFromSource(it.first);
            }
            return ans;
        }

        vector<vector<Edge<T,W>>> eulerianCircuitsFromSource(T source)
        {
            vector<vector<Edge<T,W>>> ans;
            int srcEnc = enc[source];
            //cout<<"hi"<<endl;
            set<vector<pair<int,int>>> result;
            map<pair<int,int>,bool> visEdge;
            vector<pair<int,int>> curPath;
            int numEdges = edgeList.size();
            if(!directed)
                numEdges/=2;
            //cout<<numEdges<<endl;
            function<void(int)> dfs = [&](int cur)
            {
                //cout<<dec[cur]<<"    ";
                //cout<<curPath.size()<<endl;
                //cout<<curPath.size()<<endl;
                if(signed(curPath.size()) == numEdges)
                {
                    if(curPath[numEdges-1].second == srcEnc)
                        result.insert(curPath);
                }

                for(auto it:adjList[cur])
                {
                    int neighbor = it.first;
                    if(!visEdge[make_pair(cur,neighbor)])
                    {
                        visEdge[make_pair(cur,neighbor)] = true;
                        visEdge[make_pair(neighbor,cur)] = true;
                        curPath.push_back(make_pair(cur,neighbor));
                        dfs(neighbor);
                        curPath.pop_back();
                        visEdge[make_pair(cur,neighbor)] = false;
                        visEdge[make_pair(neighbor,cur)] = false;
                    }
                }

            };

            dfs(srcEnc);

            //cout<<result.size()<<endl;
            //vector<vector<pair<int,int>>> temp(result.begin(),result.end());
            for(auto it:result)
            {
                vector<Edge<T,W>> temp;
                for (auto ed : it) {
                    int u = ed.first;
                    int v = ed.second;
                    for (auto& neighbor : adjList[u]) {
                        if (neighbor.first == v) {
                            temp.push_back(Edge<T,W>(dec[u],dec[v],neighbor.second));
                            break;
                        }
                    }
                }
                ans.push_back(temp);
            }

            return ans;            
        }

        map<T,vector<vector<Edge<T,W>>>> allSourceEulerianCircuits()
        {
            map<T,vector<vector<Edge<T,W>>>> ans;
            for(auto it:enc)
            {
                ans[it.first] = eulerianCircuitsFromSource(it.first);
            }
            return ans;
        }

        bool isEulerian()
        {
            auto ans = allSourceEulerianPaths();
            for(auto it:ans)
            {
                if(it.size()>0) 
                    return true;
            }
        }

        //-------------------------------------------------------------------------------------------------------------------------------------------------------
        // below is the code to find number of components

        vector<std::vector<T>> connectedComponents()
        {
            unordered_map<T, bool> vis;
            vector<vector<T>> res;
            auto grid = this->grp;
            for (const auto& node : grid) 
            {
                auto i = node.first;
                if (!vis[i]) 
                {
                    vector<T> temp;
                    queue<T> q;
                    q.push(i);
                    vis[i] = true;

                    while (!q.empty()) 
                    {
                        auto curr = q.front();
                        q.pop();
                        temp.push_back(curr);

                        for (const auto& adj : grid[curr]) 
                        {
                            T next = adj.first;
                            if (!vis[next]) 
                            {
                                q.push(next);
                                vis[next] = true;
                            }
                        }
                    }

                    res.push_back(temp);
                }
            }

            return res;        
        }     

        //------------------------------------------------------------------------------------------------------------------------------------------------------
        // code to find strongly connected components (SCC) 

        vector<vector<T>> stronglyConnectedComponents(const string& method = "tarjan")
        {
            if(!directed)
            {
                throw runtime_error("implemented only for directed graph");
            }

            if(method == "tarjan")
            {
                vector<vector<int>> ans = tarjanSCC();
                vector<vector<T>> res;
                for(auto it:ans)
                {
                    vector<T> temp;
                    for(auto xd:it)
                    {
                        temp.push_back(dec[xd]);
                    }
                    res.push_back(temp);
                }
                return res;
            }
            else if(method == "kosaraju")
            {
                vector<vector<int>> ans = kosarajuSCC();
                vector<vector<T>> res;
                for(auto it:ans)
                {
                    vector<T> temp;
                    for(auto xd:it)
                    {
                        temp.push_back(dec[xd]);
                    }
                    res.push_back(temp);
                }
                return res;                
            }
            else
            {
                throw runtime_error("wrong method!!!");
            }

            return vector<vector<T>>();
        }

        vector<vector<int>> tarjanSCC()
        {
            int n = size;
            
            vector<int> disc(n, -1);
            vector<int> low(n, -1);
            vector<bool> inStack(n, false);
            stack<int> nodeStack;
            vector<vector<int>> sccs;
            int time = 0;

            function<void(int)> dfs = [&](int node)
            {
                disc[node] = low[node] = ++time;
                nodeStack.push(node);
                inStack[node] = true;
                
                for (auto neigh : adjList[node]) 
                {
                    auto neighbor = neigh.first;
                    if (disc[neighbor] == -1) {
                        dfs(neighbor);
                        low[node] = min(low[node], low[neighbor]);
                    } else if (inStack[neighbor]) {
                        low[node] = min(low[node], disc[neighbor]);
                    }
                }
                
                if (disc[node] == low[node]) 
                {
                    vector<int> scc;
                    while (true) {
                        int curr = nodeStack.top();
                        nodeStack.pop();
                        inStack[curr] = false;
                        scc.push_back(curr);
                        if (curr == node) {
                            break;
                        }
                    }
                    sccs.push_back(scc);
                }
            };

            for (int i = 0; i < n; ++i) {
                if (disc[i] == -1) {
                    dfs(i);
                }
            }
            
            return sccs;            
        }

        vector<vector<int>> kosarajuSCC()
        {
            int n = size;
            
            vector<bool> visited(n, false);
            stack<int> order;
            
            function<void(int)> dfs = [&](int node) 
            {
                visited[node] = true;
                for (auto neigh : adjList[node]) 
                {
                    auto neighbor = neigh.first;
                    if (!visited[neighbor]) 
                    {
                        dfs(neighbor);
                    }
                }
                order.push(node);
            };

            // Step 1: Perform DFS on the original graph to get the finishing times
            for (int i = 0; i < n; i++) 
            {
                if (!visited[i]) {
                    dfs(i);
                }
            };
            
            // Step 2: Reverse the graph
            vector<vector<int>> reversedAdjList(n);

            function<void()> reverseGraph = [&]()
            {
                for (int i = 0; i < size; i++) 
                {
                    for (auto neigh : adjList[i]) 
                    {
                        auto neighbor = neigh.first;
                        reversedAdjList[neighbor].push_back(i);
                    }
                }
            };

            reverseGraph();
            
            // Step 3: Perform DFS on the reversed graph to find SCCs
            vector<vector<int>> stronglyConnectedComponents;
            visited.assign(n, false);        

            while (!order.empty()) 
            {
                int node = order.top();
                order.pop();
                
                if (!visited[node]) 
                {
                    vector<int> component;

                    function<void(int)> dfsSCC = [&](int node)
                    {
                        visited[node] = true;
                        component.push_back(node);
                        for (int neighbor : reversedAdjList[node]) 
                        {
                            if (!visited[neighbor]) 
                            {
                                dfsSCC(neighbor);
                            }
                        }
                    };     

                    dfsSCC(node);
                    stronglyConnectedComponents.push_back(component);
                }
            }
            
            return stronglyConnectedComponents;            
        }

        //------------------------------------------------------------------------------------------------------------------------------------------------------
        // 

        









        //-------------------------------------------------------------------------------------------------------------------------------------------------------
        // below is the code to print the graph, for debugging
        void printGraph()
        {
            //stack<vector<pair<int,double>> st;
            for(int i=0;i<size;i++)
            {
                cout<<dec[i]<<" ----> ";
                for(auto it:adjList[i])
                {
                    cout<<dec[it.first]<<"::"<<it.second<<"  ,  ";
                }
                cout<<endl;
            }
            cout<<endl;
            cout<<"size : "<<endl;
        }

};