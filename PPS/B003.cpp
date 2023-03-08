#include<iostream>

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
    int sumOfLeftLeaves(TreeNode* root) {
        int sum = 0;
        if(root->left != NULL){
            sum += get_val(root->left, 1);
        }
        if(root->right != NULL){
            sum += get_val(root->right, 0);
        }
        return sum;
    }
    int get_val(TreeNode* root, int check){
        int sum = 0;
        if(root->left == NULL && root->right == NULL){
            if(check == 1){
                sum += root->val;
            }
        }
        else{
            if(root->left != NULL){
                sum += get_val(root->left, 1);
            }
            if(root->right != NULL){
                sum += get_val(root->right, 0);
            }
        }
        return sum;
    }
};