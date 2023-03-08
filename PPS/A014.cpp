#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        int sp = -1, ep;
        vector<string> result;
        for(int i = 0; i < nums.size(); i++){
            if(sp == -1){
                sp = i;
                ep = i;
                if(i == nums.size()-1){
                    result.push_back(get_range(nums[sp], nums[ep]));
                    break;
                }
                if(nums[ep] + 1 == nums[ep+1]){
                    ep += 1;
                }
                else{
                    result.push_back(get_range(nums[sp], nums[ep]));
                    sp = -1;
                }
            }
            else{
                if(i == nums.size()-1){
                    result.push_back(get_range(nums[sp], nums[ep]));
                    break;
                }
                if(nums[ep] + 1 == nums[ep+1]){
                    ep += 1;
                }
                else{
                    result.push_back(get_range(nums[sp], nums[ep]));
                    sp = -1;
                }
            }
        }
        return result;
    }
    string get_range(int s, int e){
        string str;
        if(s == e){
            str =to_string(s);
        }
        else{
            str =to_string(s) + "->" + to_string(e);
        }
        return str;
    }
};

int main(){

    return 0;
}