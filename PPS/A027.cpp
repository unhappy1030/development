#include <string>
#include <vector>

using namespace std;

string solution(string number, int k) {
    string answer = "";
    int* idx = new int[number.length()];
    int i, n = 0;
    for(i = 1; i < number.length(); i++){
        if(number[i-1] < number[i]){
            idx[n] = i-1;
            n++;
        }
    }
    n = 0;
    for(i = 0; i < number.length(); i++){
        if(i == idx[n] && n < k){
            n++;
            continue;
        }
        answer+=number[i];
    }
    return answer;
}