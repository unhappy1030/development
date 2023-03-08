#include<iostream>

using namespace std;


void cal(string n){
    int i = 0, arr[10] = {0,};
    while(n[i] != '\0'){
        arr[n[i]-'0']++;
        i++;
    }
    for(i = 0;i < 10; i++){
        cout << arr[i] << endl;
    }
}

int main() {
    int i, n, num = 1;
    for(i = 0; i < 3; i++){
        cin >> n;
        num *= n;
    }
    cal(to_string(num));
    return 0;
}