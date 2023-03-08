#include <iostream>
#include <string>
#include <vector>

using namespace std;

int check_pos(string sk, string tr){
    vector<int> arr;
    for(int i = 0; i < sk.length(); i++){
        arr.push_back(-1);
        for(int j = 0; j < tr.length(); j++){
            if(sk[i] == tr[j]) arr[i] = j;
        }
        if(i == 0 || (arr[i-1] != -1 && arr[i] == -1)){
            continue;
        }
        else if(arr[i-1] == -1 && arr[i] != -1){
            return 0;
        }
        else if(arr[i-1] > arr[i]){
            return 0;
        }
    }
    return 1;
}
int check_all(string sk,vector<string> sk_tr){
    int count = 0;
    for(int i = 0; i < sk_tr.size(); i++){
        if(check_pos(sk, sk_tr[i])== 1){
            count++;
        }
    }
    return count;
}

int solution(string skill, vector<string> skill_trees) {
    int answer = check_all(skill, skill_trees);
    return answer;
}