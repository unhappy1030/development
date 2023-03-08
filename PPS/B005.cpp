#include<iostream>
#include<vector>


using namespace std;

/*
Definition for a binary tree node.
*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
public:
    bool check = false;
    bool findTarget(TreeNode* root, int k) {
        int sum;
        back_tracking(root, k);
        return check;
    }
    int back_tracking(TreeNode* root, int k){
        int sum[3], left = 0, right = 0;
        bool l_n = false, r_n = false;
        if(root->left != NULL){
            left = back_tracking(root->left, k);
            l_n = true;
        }
        if(root->right != NULL){
            right = back_tracking(root->right, k);
            r_n = true;
        }
        if(l_n) sum[0] = root->val + left;
        if(r_n)sum[1] = root->val + right;
        if(l_n && r_n)sum[2] = left + right;
        if(sum[0] == k || sum[1] == k || sum[2] == k){
            check = true;
        }
        return  root->val;
    }
};