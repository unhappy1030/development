#include<iostream>
#include<vector>

using namespace std;


class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        int i;
        vector<int> re;
        for(i = left; i <= right; i++){
            if(divid_check(i)){
                re.push_back(i);
            }
        }
        return re;
    }
    bool divid_check(const int n){
        int d = n;
        while(d != 0){
            if(d % 10 != 0){
                int dvd_n = d % 10;
                if(d <= 10){
                    d = 0;
                    break;
                }
                else{
                    d /= 10;
                }
                if(n % dvd_n != 0){
                    return false;
                }
            }
        }
        return true;
    }
};