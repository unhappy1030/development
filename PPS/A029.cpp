#include<iostream>
using namespace std;

int method_conversion(int b_m){
    if(b_m == 1){
        return 0;
    }
    else{
        return 1;
    }
}

int main(){
    int num, f_m, i, method;
    cin >> num >> f_m;
    method = method_conversion(f_m);
    if(num < 6){
        for(i = 0; i < num-1; i++){
            cout << method << endl;
            method = method_conversion(method);
        }
    }
    else{
        cout << "Love is open door";
    }
    return 0;
}