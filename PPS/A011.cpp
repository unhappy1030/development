#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    vector<double> fail_per;
    double max;
    int idx;
    int stay_p[501]={0,}, arrive_p[501]={0,};
    for(int i = 0; i < stages.size(); i++){
        stay_p[stages[i]]++;
        for(int j = 1; j <= N; j++){
            if(stages[i] >= j){
                arrive_p[j]++;
            }
            else{
                break;
            }
        }
    }
    for(int i = 1; i <= N; i++){
        if(arrive_p[i] == 0){
            fail_per.push_back(0);
        }
        else{
            fail_per.push_back((double(stay_p[i]) / arrive_p[i]) * 100);
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(j == 0){
                max = fail_per[j];
                idx = j;
            }
            else if(max < fail_per[j]){
                max = fail_per[j];
                idx = j;
            }
        }
        if(max == -1){
            break;
        }
        else{
            answer.push_back(idx+1);
            fail_per[idx] = -1;
        }
    }
    return answer;
}

