#include<bits/stdc++.h>
#include <cstdarg>

using namespace std;


template <typename T, typename W>
class Edge {
    private:
        T src, dest;
        W weight;
    public:
        Edge(const T& src, const T& dest, const W& weight)
        {
            this->src = src;
            this->dest = dest;
            this->weight = weight;
        }
        T getSource() const
        {
            return src;
        }
        T getDestination() const
        {
            return dest;
        }
        W getWeight() const
        {
            return weight;
        }
};

template <typename T, typename W>
class Graph {
    //vector<vector<T>> grp;
    unordered_map<T,vector<pair<T,W>>> grp;
    vector<Edge<T,W>> edge_list;
    int size;
    bool directed;
    public:
        unordered_map<T,vector<pair<T,W>>> grid = this->grp;
        void help_construct()
        {
            return;
        }
        template<typename... Types>
        void help_construct(T node , Types... var)
        {
            this->addNode(node);
            size++;
            help_construct(var...);
        }
        Graph(bool directed)
        {
            this->directed = directed;
            size = 0;
        }
        template<typename... Types>
        Graph(bool directed,Types... var)
        {
            this->directed = directed;
            size = 0;
            help_construct(var...);
        }

        void addNode(const T& data)
        {
            grp[data] = vector<pair<T,W>>();
            size++;
        }

        void addEdge(const T& src, const T& dest, const W& weight = W())
        {
            Edge<T,W> temp(src,dest,weight);
            edge_list.push_back(temp);
            if(directed)
            {
                grp[src].push_back(make_pair(dest,weight));
            }
            else
            {
                grp[src].push_back(make_pair(dest,weight));
                grp[dest].push_back(make_pair(src,weight));
            }
        }

        bool hasCycle() const
        {
            map<T,bool> vis;
            auto grid = this->grp;
            function<bool(T)> dfs = [&](T src)
            {
                vis[src] = true;
                for(auto it:grid[src])
                {
                    if(vis[it.first] == true)
                        return true;
                    dfs(it.first);
                }
                return false;
            };
            bool ans = false;
            for(auto it:grid)
            {
                if(!vis[it.first])
                {
                    ans = dfs(it.first);
                }
            }
            return ans;
            return false;
        }
        // Algorithm implementations
        std::vector<int> nodeColoring() const
        {
            // initialize the colors of all nodes to -1 (unassigned)
            unordered_map<T, int> node_colors;
            for (const auto& node_pair : grp) 
            {
                node_colors[node_pair.first] = -1;
            }

            // assign colors to nodes one by one, based on the colors of their neighbors
            for (const auto& node_pair : grp) 
            {
                const T& node = node_pair.first;
                const vector<pair<T, W>>& neighbors = node_pair.second;
                vector<bool> available_colors(size, true);  // initialize all colors as available

                // mark the colors of all neighboring nodes as unavailable
                for (const auto& neighbor_pair : neighbors) 
                {
                    const T& neighbor = neighbor_pair.first;
                    int color = node_colors[neighbor];
                    if (color != -1) {
                        available_colors[color] = false;
                    }
                }

                // find the first available color for the current node
                int color = 0;
                while (color < size && !available_colors[color]) {
                    color++;
                }

                // assign the color to the current node
                node_colors[node] = color;
            }

            // convert the unordered_map of node colors to a vector
            vector<int> result;
            for (const auto& node_pair : node_colors) 
            {
                result.push_back(node_pair.second);
            }
            return result;
        }

        std::vector<int> edgeColoring() const
        {
            //todo
            return vector<int>(size,0);
        }

        bool isBipartite()
        {
            vector<int> colors = nodeColoring();
            set<int> st;
            for(auto it:colors)
            {
                st.insert(it);
            }
            if(st.size() == 2)
                return true;
            return false;
        }

        void completeEdges();

        std::vector<std::vector<T>> connectedComponents() const
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

        std::vector<double> katzCentrality(double alpha, double beta) const
        {
            int n = size;
            vector<vector<double>> A(n, vector<double>(n, 0));
            vector<double> deg(n, 0);

            unordered_map<T, int> labelToIndex;
            int index = 0;
            for (auto node : grp) 
            {
                T label = node.first;
                labelToIndex[label] = index++;
            }

            for (auto edge : edge_list) 
            {
                T u = edge.getSource();
                T v = edge.getDestination();
                double w = edge.getWeight();
                int i = labelToIndex[u];
                int j = labelToIndex[v];
                A[i][j] = w;
                deg[i] += w;
            }

            vector<double> x(n, 1);
            vector<double> prev_x(n, 0);
            double lambda = 1 / (alpha * deg[0] + beta);
            while (true) {
                for (int i = 0; i < n; i++) 
                {
                    prev_x[i] = x[i];
                    x[i] = 0;
                    for (int j = 0; j < n; j++) {
                        x[i] += A[j][i] * prev_x[j];
                    }
                    x[i] = alpha * x[i] + beta;
                }
                double norm = 0;
                for (int i = 0; i < n; i++) 
                {
                    norm += pow(x[i], 2);
                }
                norm = sqrt(norm);
                for (int i = 0; i < n; i++) 
                {
                    x[i] /= norm;
                }
                double err = 0;
                for (int i = 0; i < n; i++) 
                {
                    err += abs(x[i] - prev_x[i]);
                }
                if (err < 1e-6) 
                {
                    break;
                }
            }
            vector<double> centrality(n, 0);
            for (auto node : grp) 
            {
                T label = node.first;
                int i = labelToIndex[label];
                centrality[i] = lambda * x[i];
            }
            return centrality;
        }        

        std::vector<Edge<T, W>> primMST() const
        {
            vector<Edge<T, W>> mst;
            priority_queue<pair<W, T>, vector<pair<W, T>>, greater<pair<W, T>>> pq;
            unordered_set<T> visited;
            // Pick arbitrary node as starting point
            T start_node = grp.begin()->first;
            pq.push(make_pair(W(), start_node));
            while (!pq.empty()) 
            {
                T node = pq.top().second;
                //W weight = pq.top().first;
                pq.pop();
                if (visited.find(node) != visited.end()) 
                {
                    continue;
                }
                visited.insert(node);
                for (const auto& it : grp.at(node)) 
                {
                    auto neighbor = it.first;
                    auto neighbor_weight = it.second;
                    if (visited.find(neighbor) == visited.end()) 
                    {
                        pq.push(make_pair(neighbor_weight, neighbor));
                    }
                }
                if (pq.empty()) 
                {
                    break;
                }
                T next_node = pq.top().second;
                W next_weight = pq.top().first;
                mst.emplace_back(node, next_node, next_weight);
            }
            return mst;
        }

        std::vector<Edge<T, W>> kruskalMST() const
        {
            vector<Edge<T, W>> result;
            // Create a priority queue to store edges sorted by weight
            priority_queue<Edge<T, W>, vector<Edge<T, W>>, function<bool(Edge<T, W>, Edge<T, W>)>> pq([](Edge<T, W> a, Edge<T, W> b) -> bool {
                return a.getWeight() > b.getWeight();
            });
            // Add all edges to the priority queue
            for (Edge<T, W> edge : edge_list)
            {
                pq.push(edge);
            }

            // Create a vector to store the parent of each node for the union-find algorithm
            //vector<T> parent(size);
            map<T,T> parent;
            auto grid = this->grp;

            for (auto i : grid)
            {
                parent[i.first] = i.first;
            }

            // Keep adding edges to the result until we have n-1 edges or the priority queue is empty
            while (!pq.empty() && int(result.size()) < size - 1)
            {
                Edge<T, W> edge = pq.top();
                pq.pop();

                T u = edge.getSource();
                T v = edge.getDestination();

                // Find the parent of u and v using union-find algorithm
                while (u != parent[u])
                {
                    u = parent[u];
                }
                while (v != parent[v])
                {
                    v = parent[v];
                }

                // If the parents are different, add the edge to the result and merge the sets
                if (u != v)
                {
                    result.push_back(edge);
                    parent[u] = v;
                }
            }

            return result;   
        }

        std::vector<T> iterativeDFS(const T& start) const
        {
            stack<T> st;
            auto grid = this->grp;
            st.push(start);
            unordered_map<T,bool> vis;
            vector<T> res;
            while(!st.empty())
            {
                auto curr = st.top();st.pop();
                res.push_back(curr);
                vis[curr] = true;
                for(auto it:grid[curr])
                {
                    auto neighbor = it.first;
                    if(!vis[neighbor])
                        st.push(neighbor);
                }
            }
            return res;
        }

        std::vector<T> uniformCostSearch(const T& start, const T& goal) const
        {
            std::unordered_map<T, T> parent;  // to store parent of each node
            std::unordered_map<T, W> dist;  // to store distance of each node from start
            std::priority_queue<std::pair<W, T>, std::vector<std::pair<W, T>>, std::greater<std::pair<W, T>>> pq;

            auto grid = this->grp;

            pq.push(std::make_pair(W(), start));
            dist[start] = W();

            while (!pq.empty()) 
            {
                T curr = pq.top().second;
                pq.pop();
                if (curr == goal)
                {
                    break;
                }
                for (auto edge : grid[curr]) {
                    T neighbor = edge.first;
                    W weight = edge.second;
                    W new_dist = dist[curr] + weight;
                    if (!dist.count(neighbor) || new_dist < dist[neighbor]) {
                        parent[neighbor] = curr;
                        dist[neighbor] = new_dist;
                        pq.push(std::make_pair(new_dist, neighbor));
                    }
                }
            }

            std::vector<T> path;
            T curr = goal;
            while (curr != start) {
                path.push_back(curr);
                curr = parent[curr];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }


        std::vector<T> aStarSearch(const T& start, const T& goal, std::function<double(T, T)> heuristic)const
        {
            unordered_map<T, W> g_score;
            unordered_map<T, double> f_score;
            unordered_map<T, T> came_from;
            priority_queue<pair<double, T>, vector<pair<double, T>>, greater<pair<double, T>>> pq;
            auto grid = this->grp;
            // Initialize g_score and f_score maps
            for (auto node : grp)
            {
                g_score[node.first] = numeric_limits<W>::max();
                f_score[node.first] = numeric_limits<double>::max();
            }

            g_score[start] = 0;
            f_score[start] = heuristic(start, goal);

            pq.push(make_pair(f_score[start], start));

            while (!pq.empty())
            {
                T current = pq.top().second;
                pq.pop();

                if (current == goal)
                {
                    // Reconstruct the path from start to goal
                    vector<T> path;
                    path.push_back(current);

                    while (current != start)
                    {
                        current = came_from[current];
                        path.push_back(current);
                    }

                    reverse(path.begin(), path.end());
                    return path;
                }

                for (auto neighbor : grid[current])
                {
                    T next = neighbor.first;
                    W cost = neighbor.second;

                    W tentative_g_score = g_score[current] + cost;
                    if (tentative_g_score < g_score[next])
                    {
                        came_from[next] = current;
                        g_score[next] = tentative_g_score;
                        f_score[next] = g_score[next] + heuristic(next, goal);
                        pq.push(make_pair(f_score[next], next));
                    }
                }
            }

            // If we reach here, there is no path from start to goal
            return vector<T>();

        }


        /* here im writing print graph function just to check the corectness*/
        void print_graph()
        {
            //auto node_colors = this->nodeColoring();
            int i = 0;
            stack<pair<T,vector<pair<T,W>>>> temp;
            for(auto it:grp)
            {
                temp.push(it);
            }
            while(!temp.empty())
            {
                auto top = temp.top();temp.pop();
                cout<<top.first<<"--->";
                for(auto xd:top.second)
                {
                    cout<<xd.first<<":w="<<xd.second<<"  ,  ";
                    i++;
                }
                cout<<endl;
            }
            cout<<endl;
            //cout<<"hi"<<endl;
            vector<int> edge_color = this->edgeColoring();
            //vector<int> edge_color = vector<int>(9999,0);
            //cout<<edge_color.size()<<endl;
            i = 0;
            for(auto edg : edge_list)
            {
                if(directed == 1)
                {cout<<"("<<edg.getSource()<<" "<<edg.getDestination()<<"):"<<edge_color[i]<<" , ";i++;}
                else
                {
                    cout<<"("<<edg.getDestination()<<" "<<edg.getSource()<<"):"<<edge_color[i]<<" , ";
                    cout<<"("<<edg.getSource()<<" "<<edg.getDestination()<<"):"<<edge_color[i]<<" , ";
                    i++;
                }
            }
            cout<<endl;

            cout<<"Node colors:-"<<endl;
            auto node_colors = this->nodeColoring();
            for(auto it:node_colors)
            {
                cout<<it<<" ";
            }
            cout<<endl<<endl;
        
            cout<<"Connected compoents"<<endl;
            auto connectedComponents = this->connectedComponents();
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
            auto kratz_centrality = this->katzCentrality(0.1,0.2);
            for(auto it:kratz_centrality)
            {
                cout<<it<<" "<<endl;
            }
            cout<<endl;

            cout<<"Prim's MST"<<endl;
            auto primMST = this->primMST();
            for(auto it:primMST)
            {
                if(it.getSource() == it.getDestination())
                    continue;
                cout<<'('<<it.getSource()<<" "<<it.getDestination()<<')'<<"  , ";
            }
            cout<<endl<<endl;

            cout<<"Krushkal MST"<<endl;
            auto kruskalMST = this->kruskalMST();
            for(auto it:kruskalMST)
            {
                if(it.getSource() == it.getDestination())
                    continue;
                cout<<'('<<it.getSource()<<" "<<it.getDestination()<<')'<<"  , ";
            }
            cout<<endl<<endl;
        
        }

};