class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int idx;
        if(nums.size() == 1){
            if(nums[0] < target){
                return 1;
            }
            else{
                return 0;
            }
        }
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
        if(t > arr[s] && t < arr[e] && e - s == 1){
            return e;
        }
        int half = (s + e) / 2;
        if(t > arr[s] && t <= arr[half]){
            return bs(arr, t, s, half);
        }
        if(t >= arr[half] && t < arr[e]){
            return bs(arr, t, half, e);
        }
        else if(t > arr[e]){
            return e+1;
        }
        else if(t < arr[s]){
            return 0;
        }
    }
};