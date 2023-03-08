#include<iostream>
#include<vector>

using namespace std;
bool visit[101]={0,};
vector<int> graph[101];

void dfs(int x);

int main(){
    int i, com_num, case_num, count = 0;
    cin >> com_num;
    cin >> case_num;
    for(i = 0; i < case_num; i++){
        int a, b ,t;
        cin >> a;
        cin >> b;
        if(a > b){
            t = a;
            a = b;
            b = t;
        }
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dfs(1);
    for(i = 2; i <= com_num; i++){
        if(visit[i]){
            count++;
        }
    }
    cout << count;
    return 0;
}

void dfs(int x){
    visit[x] = true;
    for(int i = 0; i < int(graph[x].size()); i++){
        int y = graph[x][i];
        if(!visit[y]){
            dfs(y);
        }
    }
}