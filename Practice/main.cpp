#include <iostream>
#include <vector>

using namespace std;

vector<int> graph;
vector<int> vist;
vector<bool> isCycle;

void dfs(const int curr){
    const auto next = graph[curr];
    vist[curr] = 1;

    if(vist[next] == 0){
        dfs(next);
    }else if(vist[next] == 1){
        auto c = next;

        isCycle[curr] = true;
        while(c != curr){
            isCycle[c] = true;
            c = graph[c];
        }
    }
    vist[curr] = 2;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;

    cin >> t;

    while(t--){
        int n, result = 0;

        cin >> n;

        graph.resize(n + 1);
        vist.assign(n + 1, 0);
        isCycle.assign(n + 1, false);

        for(int i = 1; i <= n; i++)
            cin >> graph[i];

        for(int i = 1; i <= n; i++)
            if(vist[i] == 0) dfs(i);

        for(int i = 1; i <= n; i++)
            if(!isCycle[i])result++;

        cout << result << '\n';
    }

    return 0;
}