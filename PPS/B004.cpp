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
    bool isSymmetric(TreeNode* root) {
        vector<int> right, left;
        if(root->right != NULL){
            dfs_right(root->right, right);
        }
        else{
            right.push_back(-101);
        }
        if(root->left != NULL){
            dfs_left(root->left, left);
        }
        else{
            left.push_back(-101);
        }
        int i, len[2];
        len[0] = right.size();
        len[1] = left.size();
        if(len[0] != len[0]){
            return false;
        }
        else{
            for(i = 0; i < len[0]; i++){
                if(right.at(i) != left.at(i)){
                    return false;
                }
            }
            return true;
        }
    }
private:
    void dfs_right(TreeNode* root, vector<int> &sav){
        sav.push_back(root->val);
        if(root->right != NULL){
            dfs_right(root->right, sav);
        }
        else{
            sav.push_back(-101);
        }
        if(root->left != NULL){
            dfs_right(root->left, sav);
        }
        else{
            sav.push_back(-101);
        }
    }
    void dfs_left(TreeNode* root, vector<int> &sav){
        sav.push_back(root->val);
        if(root->left != NULL){
            dfs_left(root->left, sav);
        }
        else{
            sav.push_back(-101);
        }
        if(root->right != NULL){
            dfs_left(root->right, sav);
        }
        else{
            sav.push_back(-101);
        }
    }
};

int main() {
    return 0;
}