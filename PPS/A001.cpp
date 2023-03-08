#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int count = 0, i, j;
        sort(s.begin(), s.end());
        for(i = 0; i < s.size(); i++){
            for(j = 0; j < g.size(); j++){
                if(g[j] == 0) continue;
                else{
                    if(s[i] >= g[j]){
                        g[j] = 0;
                        s[i] = 0;
                        count++;
                        break;
                    }
                }
            }
        }
        return count;
    }
};