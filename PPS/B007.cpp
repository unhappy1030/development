class Solution {
public:
    int search(vector<int>& nums, int target) {
        int idx;
        idx = bs(nums, target, 0, nums.size()-1);
        return idx;
    }
    int bs(vector<int> arr, int t, int s, int e){
        if(arr[s] == t){
            return s;
        }
        if(arr[e] == t){
            return e;
        }
        if(e - s <= 1 ){
            return -1;
        }
        int half = (s + e) / 2;
        if(t > arr[s] && t <= arr[half]){
            return bs(arr, t, s, half);
        }
        if(t >= arr[half] && t < arr[e]){
            return bs(arr, t, half, e);
        }
        else{
            return -1;
        }
    }
};