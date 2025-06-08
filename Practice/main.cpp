#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin>>t;
    while(t--){
        int n, result;
        
        cin>>n;
        result = n;
        vector<int> visited(n + 1);
        vector<int> edge(n + 1);
        
        for(int i = 1; i <= n; i++)
            cin >> edge[i];
        
        for(int i = 1; i <= n; i++){
            if(!visited[i]){
                auto curr = i;
                int cycle_size = 0;
                while(!visited[curr]){
                    visited[curr] = ++cycle_size;
                    curr = edge[curr];
                }

                if(visited[curr] > 0){
                    result -= cycle_size - visited[curr] + 1;
                }

                curr = i;
                while(visited[curr] != -1){
                    visited[curr] = -1;
                    curr = edge[curr];
                }
            }   
        }

        cout << result << '\n';
    }

    return 0;
}