#include<iostream>

using namespace std;

int main(){
    int i, add, mius, people_num = 0, max = 0;
    for(i = 0; i < 4; i++){
        cin >> mius >> add;
        people_num -= mius;
        people_num += add;
        if(i == 0){
            max = people_num;
        }
        else{
            if(people_num > max){
                max = people_num;
            }
        }
    }
    cout << max;
    return 0;
}