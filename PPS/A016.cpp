#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0, left = 0, right = people.size() - 1;
    sort(people.begin(), people.end());
    while(1){
        if(left > right){
            break;
        }
        if(left == right){
            answer++;
            break;
        }
        if(people[left] + people[right] <= limit){
            answer++;
            left++;
            right--;
        }
        else{
            answer++;
            right--;
        }
    }
    return answer;
}