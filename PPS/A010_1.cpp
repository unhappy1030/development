#include <iostream>
#include <string>
#include <vector>
/*
요점        - 1개짜리 문자열 체크
            - 같은 문자열의 갯수가 10개 넘어가면 자릿수가 1개 늘어나고 100개가 되면 2개 늘어남
*/
using namespace std;

int solution(string s) {
    int answer = 0;
    for(int i = int(s.length()) / 2; i >=1; i--){
        vector<string> part;
        string result = "";
        int count = 0, t = -1;
        if(s.length() == 1){
            return 1;
        }
        for(int j = 0; j < s.length(); j+=i){
            t++;
            if(j+i >= s.length()){
                part.push_back(s.substr(j));
            }
            else{
                part.push_back(s.substr(j,i));
            }
            if(t == 0){
                result += part[t];
                continue;
            }
            else{
                if(part[t].compare(part[t-1]) == 0){
                    count++;
                }
                else{
                    if(count != 0){
                        result += to_string(count+1);
                        count = 0;
                    }
                    result += part[t];
                }
            }
            if(j+i >= s.length()){
                if(count != 0){
                    result += to_string(count+1);
                    count = 0;
                }
            }
        }
        if(i == int(s.length()) / 2){
            answer = result.length();
        }
        else{
            if(answer > result.length()) answer = result.length();
        }
    }
    return answer;
}

int main() {
    string input;
    cin >> input;
    cout << "\n" << solution(input) << endl;
    return 0;
}