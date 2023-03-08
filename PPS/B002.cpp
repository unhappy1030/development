#include<iostream>
#include<vector>

using namespace std;


// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};


class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        int i, sum;
        sum = recursion_get_importance(employees, id);
        return sum;
    }
private:
    int recursion_get_importance(vector<Employee*> &e, int id){
        int i, j, sum, idx;
        idx = get_id_to_idx(e, id);
        sum = e.at(idx)->importance;
        vector<int> sub = e.at(idx)->subordinates;
        if(sub.size() != 0){
            for(i = 0; i < sub.size(); i++){
                sum += recursion_get_importance(e, sub.at(i));
            }
        }
        return sum;
    }
    int get_id_to_idx(vector<Employee*> &e, int id){
        int i;
        for(i = 0; i < e.size(); i++){
            if(e.at(i)->id == id){
                return i;
            }
        }
        return 0;
    }
};

int main(){
    return 0;
}