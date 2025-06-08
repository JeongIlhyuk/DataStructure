#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

const int MAX_EDGE = 500 * 499 / 2;
const int MAX_WEIGHT = MAX_EDGE * 1000;

auto djikstra(const int adj[][500], int path[][MAX_EDGE + 2], const int n, const int start){
    vector<int> dist(500, MAX_WEIGHT);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while(!pq.empty()){
        const auto weight = pq.top().first;
        const auto node = pq.top().second;

        pq.pop();

        if(weight > dist[node]) continue;

        for(int next = 1; next <= n; next++){
            const auto w = adj[node][next];
            if(w != -1 && dist[node] + w < dist[next]) {
                int i = 0;
                while(path[node][i] != -1){
                    path[next][i] = path[node][i];
                    i++;
                }
                path[next][i] = next;

                dist[next] = dist[node] + w;
                pq.push({dist[next], next});
            }
        }
    }

    return dist;
}

auto almost_djik(const int adj[][500], int path[][MAX_EDGE + 2], const int n, const int start){
    vector<int> dist(500, MAX_WEIGHT);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while(!pq.empty()){
        const auto weight = pq.top().first;
        const auto node = pq.top().second;

        pq.pop();

        if(weight > dist[node]) continue;

        for(int next = 1; next <= n; next++){
            const auto w = adj[node][next];
            if(w != -1 && dist[node] + w < dist[next]) {
                int i = 0;
                while(path[node][i] != -1){
                    path[next][i] = path[node][i];
                    i++;
                }
                path[next][i] = next;

                dist[next] = dist[node] + w;
                pq.push({dist[next], next});
            }
        }
    }

    return dist;
}



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, m;
    while(cin >> n >> m && (n != 0 || m != 0)){
        int adj[500][500];
        int path[500][MAX_EDGE + 2];
        int excluded[500] = {};
        int s, d;

        cin >> s >> d;
        
        for(int i = 0; i < 500; i++)
            fill(adj[i], adj[i] + 500, -1);
        for(int i = 0; i < 500; i++){
            path[i][0] = s;
            fill(path[i] + 1, path[i] + MAX_EDGE + 2, -1);
        }
        
        while(m--){
            int curr, next, weight;
            
            cin >> curr >> next >> weight;
            adj[curr][next] = weight;
        }
        
        djikstra(adj, path, n, s);


        int i = 0;
        while(path[d][i] != -1){
            excluded[path[d][i]] = 1;
        }
    }

    return 0;
}