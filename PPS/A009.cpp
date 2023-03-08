#include <string>
#include <vector>

using namespace std;

bool solution(string s) {
    bool answer = true;
    char c;
    int count = 0;
    if(!(s.length() == 4 || s.length() == 6)) return false;
    for(int i = 0 ; i < s.length(); i++){
        c = s[i];
        if(!(c >= '0' && c <= '9')){
            answer = false;
            break;
        }
    }
    return answer;
}