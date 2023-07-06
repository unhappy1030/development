#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    vector<int> val, idx;
    int len;
    int subsetXORSum(vector<int>& nums) {
        int i, sum = 0;
        len = nums.size();
        for(i = 0; i <= int(nums.size()); i++){
            sum += comb_xor(nums, i);
        }
        return sum;
    }
    int comb_xor(vector<int>& arr, int n){
        int i;
        if(n == 0){
            return 0;
        }
        else{
            if(val.size() == 0){
                for(i = 0; i < n; i++){
                    push_both(arr[i], i);
                }
            }
            int x = cal();
            if(check_idx(n)){
                return x;
            }
            idx_cal(arr, n);
            return x + comb_xor(arr , n);
        }
    }
    void reset_vector(){
        val.clear();
        idx.clear();
    }
    void push_both(int v, int i){
        val.push_back(v);
        idx.push_back(i);
    }
    bool check_idx(int n){
        if(idx[0] == len - 1 - n){
            return true;
        }
        else{
            return false;
        }
    }
    void idx_cal(vector<int>& arr, int n){
        int i, j;
        for(i = n - 1; i >= 0; i--){
            if(i == n - 1){
                if(idx[i]+1 == len-1){
                    continue;
                }
                else{
                    idx[i]++;
                    val[i] = arr[idx[i]];
                    break;
                }
            }
            else{
                if(idx[i]+1 == idx[i+1]){
                    continue;
                }
                else{
                    idx[i]++;
                    val[i] = arr[idx[i]];
                    push_both(arr[idx[i]], idx[i]);
                    for(j = 1; j < n-i-1; j++){
                        idx[j] = idx[i] + j;
                        val[j] = arr[idx[j]];
                    }
                    break;
                }
            }
        }
    }
    int cal(){
        int i, n = 0;
        n = val[0];
        if(val.size() > 1){
            for(i = 1; i< int(val.size()); i++){
                n ^= val[i];
            }
        }
        return n;
    }

};


int main(){
    vector<int> num;
    int i, r, n;
    Solution s;
    for(i = 0; i < 3; i++){
        cin >> n; 
        num.push_back(n);
    }
    r = s.subsetXORSum(num);
    cout << r;
    return 0;
}