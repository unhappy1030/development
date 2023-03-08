#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        int i, j;
        vector<vector<int>> result;
        vector<int> fact;
        for(i = 0; i < numRows; i++){
            fact.clear();
            if(i == 0) fact.push_back(1);
            else if(i == 1){
                fact.push_back(1);
                fact.push_back(1);
            }
            else{
                for(j = 0; j <= i; j++){
                    if(j == 0 || j == i) fact.push_back(1);
                    else{
                        fact.push_back(result[i-1][j-1] + result[i-1][j]);
                    }
                }
            }
            result.push_back(fact);
        }
        return result;
    }
};
//below main fuction is test setting.
int main(){
    int n = 4;
    Solution test;
    vector<vector<int>> p = test.generate(n);
    int i, j;
    for(i = 0; i < n; i++){
        cout << '[';
        for(j = 0; j < p[i].size(); j++){
            cout << p[i][j];
            if(j != p[i].size() - 1) cout << ", ";
        }
        cout << ']';
        cout << endl;
    }
    return 0;
}