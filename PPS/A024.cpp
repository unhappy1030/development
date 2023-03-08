#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int d[3] = {0,};
        for(int i = 0; i < bills.size(); i++){
            if(!each_check(bills[i], d)){
                return false;
            }
        }
        return true;
    }
    bool each_check(int pay,int (&d)[3]){
        if(pay == 5){
            d[0]++;
            return true;
        }
        if(pay == 10)d[1]++;
        pay -= 5;
        if(pay == 15){
            if(d[1]>=1){
                d[1]--;
                pay-=10;
            }
            else{
                if(d[0] >= 3){
                    d[0]-=3;
                    return true;
                }
                else{
                    return false;
                }
            }
        }
        if(pay == 5){
            if(d[0] >= 1){
                    d[0]-=1;
                    return true;
                }
                else{
                    return false;
                }
        }
        if(pay == 0) return true;
        else return false;
    }
};

int main(){
    return 0;
}