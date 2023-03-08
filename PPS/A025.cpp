#include<iostream>

using namespace std;

class Solution {
public:
    bool isPowerOfFour(int n) {
        double four = 1;
        while(n != four){
            if(n < four) return false;
            else{
                four *= 4;
            }
        }
        return true;
    }
};
int main(){
    return 0;
}