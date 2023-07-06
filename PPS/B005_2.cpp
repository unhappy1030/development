#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool check = false;
    vector<int> q;
    bool findTarget(TreeNode* root, int k) {
        int i, j;
        search(root, k);
        for(i = 0; i < q.size();i++){
            for(j = 0; j < q.size();j++){
                if(i <= j ){
                    continue;
                }
                else{
                    if(compare(q[i], q[j], k)){
                        return true;
                    }
                }
            }
        }
        return false;
    }
    void search(TreeNode* node, int k){
        if(node->left != nullptr){
            search(node->left, k);
        }
        if(node->right != nullptr){
            search(node->right, k);
        }
        q.push_back(node->val);
    }
    bool compare(int a, int b, int k){
        if(a + b == k) return true;
        else return false;
    }
};