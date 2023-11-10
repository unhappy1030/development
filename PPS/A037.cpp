#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> result;
        int i, check = 0;
        for(i = left; i <= right; i++){
            check = check_divide(i);
            if(check == 1){
                result.push_back(i);
            }
        }
        return result;
    }
    int length(int num){
        if(num >= 10000){
            return 5;
        }
        else if(num >= 1000){
            return 4;
        }
        else if(num >= 100){
            return 3;
        }
        else if(num >= 10){
            return 2;
        }
        else{
            return 1;
        }
    }
    int check_divide(int num){
        vector<int> sliced_num;
        int len, i, n;
        n = num;
        len = length(num);
        for(i = len; i > 0; i--){
            int p, d;
            if(i == 1){
                d = 1;
            }
            else{
                d = 10 * (i-1);
            }
            p = n / d;
            n -= p * d;
            if(p != 0){
                if(num % p != 0){
                    return 0;
                }
            }
            else if(p == 0){
                return 0;
            }
        }
        return 1;
    }
};