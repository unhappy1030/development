#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

vector<int> solution(vector<int> arr, int divisor) {
    vector<int> answer;
    sort(arr.begin(), arr.end());
    int check = 0;
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] % divisor == 0){
            answer.push_back(arr[i]);
            if(check == 0) check = 1;
        }
    }
    if(check == 0) answer.push_back(-1);
    return answer;
}

int main(){
    return 0;
}