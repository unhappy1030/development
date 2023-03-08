#include<iostream>

using namespace std;

int main(){
    int i, n, c, count = 1;
    cin >> n;
    for(i = 0; i < n; i++){
        cin >> c;
        count+=c-1;
    }
    cout << count;
    return 0;
}