#include <iostream>

using namespace std;

int main(){
    int i, n, arr[43] = {0,};
    for(i = 0; i < 10; i++){
        cin >> n;
        n %= 42;
        if(arr[n] == 0) arr[n] = 1;
    }
    int count = 0;
    for(i = 0 ; i < 43; i++){
        if(arr[i] == 1){
            count++;
        }
    }
    cout << count;
    return 0;
}