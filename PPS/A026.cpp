#include <string>
#include <vector>

using namespace std;

bool solution(int x) {
    bool answer = false;
    string x_s = to_string(x);
    int x_sum = 0;
    for(int i = 0; i < x_s.length(); i++){
        x_sum += x_s[i] - '0';
    }
    if(x % x_sum == 0) answer = true;
    return answer;
}