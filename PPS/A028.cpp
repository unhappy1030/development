#include<iostream>
#include<vector>
using namespace std;


class Cal_char{
public:
    int check = 0;
    char cal(char c1,char c2){
        char n = c1 + c2 - '0';
        if(check == 1){
            n++;
            check = 0;
        }
        if(n > '9'){
            n = n - '9' + '0' - 1;
            check = 1;
        }
        return n;
    }
};

int main(){
    Cal_char a;
    string s1, s2;
    cin >> s1 >> s2;
    vector<char> v1(s1.rbegin(), s1.rend()), v2(s2.rbegin(), s2.rend()), r;
    int len, len1 = v1.size(), len2 = v2.size();
    if(len1 > len2){
        len = len1;
    }
    else{
        len = len2;
    }
    for(int i = 0; i < len; i++){
        char c1, c2;
        if(len1-1 < i){
            c1 = '0';
        }
        else{
            c1 = v1[i];
        }
        if(len2-1 < i){
            c2 = '0';
        }
        else{
            c2 = v2[i];
        }
        r.push_back(a.cal(c1, c2));
    }
    if(a.check == 1){
        r.push_back('1');
    }
    string answer(r.rbegin(), r.rend());
    cout << answer;
    return 0;
}