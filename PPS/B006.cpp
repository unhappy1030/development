#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>

using namespace std;

vector<int> graph[1001];
bool v[1001];
queue<int> q;


int node_num, branch_num, start_node;
void reset(){
    int i;
    for(i = 0; i <= node_num; i++){
        v[i] = false;
    }
}
void dfs(int s){
    int i;
    cout << s << " ";
    v[s] = true;
    if(!graph[s].empty()){
        for(i = 0; i < int(graph[s].size()); i++){
            if(!v[graph[s][i]]){
                dfs(graph[s][i]);
            }
        }
    }
    
}
void bfs(int s){
    int i;
    cout << s << " ";
    v[s] = true;
    q.push(s);
    while(!q.empty()){
        int x = q.front();
        q.pop();
        for(i = 0; i < int(graph[x].size()); i++){
            if(!v[graph[x][i]]){
                cout << graph[x][i] << " ";
                v[graph[x][i]]=true;
                q.push(graph[x][i]);
            }
        }
    }
}
int main() {
    int i;
    int start , end;
    cin >> node_num >> branch_num >> start_node;
    for(i = 0; i < branch_num; i++){
        cin >> start >> end;
        graph[start].push_back(end);
        graph[end].push_back(start);
    }
    for(i = 0; i <=node_num; i++){
        if(!graph[i].empty()){
            sort(graph[i].begin(), graph[i].end());
        }
    }
    reset();
    dfs(start_node);
    reset();
    cout << "\n";
    bfs(start_node);
    return 0;
}