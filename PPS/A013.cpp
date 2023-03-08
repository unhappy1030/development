#include<iostream>
#include<vector>

using namespace std;

/*
-포인트 : 중간 노드 삭제시 head, tail 체크 및 변경
*/
class node{
public:
    int num;
    node *link;
    void set_node(int n);
};

void node::set_node(int n){
    num = n;
}

class check_list{
    node *head, *tail;
public:
    check_list();
    void add_t(node t);
    void del_h();
    bool del(int n);
    node last();
};

check_list::check_list(){
    head = NULL;
    tail = NULL;
}
void check_list::add_t(node t){
    node *p;
    p = new node;
    (*p) = t;
    p->link = NULL;
    if(tail != NULL){
        tail->link = p;
    }
    else{
        head = p;
    }
    tail = p;
}
void check_list::del_h(){
        node temp;
        node *t;
        t = head;
        temp = *head;
        head = head->link;
        delete t;
        if(head == NULL){
            tail = NULL;
        }
}
bool check_list::del(int n){
    node *t, *prev;
    int check = 0;
    for(t = head; t!=NULL; t=t->link){
        if(n == t->num){
            check = 1;
            break;
        }
        prev = t;
    }
    if(check == 0) return true;
    else{
        if(t == head){
            del_h();
        }
        else{
            prev->link = t->link;
            delete t;
            if(prev->link == NULL){
                tail = prev;
            }
        }
        return false;
    }
}
node check_list::last(){
    return *tail;
}

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        check_list arr;
        for(int i = 0; i < nums.size(); i++){
            if(arr.del(nums[i])){
                node t;
                t.set_node(nums[i]);
                arr.add_t(t);
            }
        }
        return arr.last().num;
    }
};

int main(){
    Solution x;
    vector<int> a;
    int t;
    while(t != 0){
        cin >> t;
        a.push_back(t);
    }
    cout << x.singleNumber(a);
    return 0;
}