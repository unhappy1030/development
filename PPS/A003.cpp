#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int i,check = 0;
        for(i = digits.size() - 1;i >= 0;i--){
            if(digits[i] == 9){
                digits[i] = 0;
                check = 1;
            }
            else{
                digits[i]++;
                check = 0;
                break;
            }
        }
        if(check == 1){
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
};

int main(){
    cout << "hello";
    return 0;
}