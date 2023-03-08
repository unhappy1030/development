#include<iostream>
#include<string>
using namespace std;

class Solution {
public:
    int addDigits(int num) {
        if(num < 10) return num;
        int i, sum = 0;
        string s = to_string(num);
        for(i = 0; i < s.size(); i++){
            sum += s[i] - '0';
        }
        return addDigits(sum);
    }
};

int main(){
    int n;
    Solution s;
    cin >> n;
    cout << s.addDigits(n);
    return 0;
}