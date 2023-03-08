#include <iostream>

using namespace std;

int main() {
    int input[8], a = 0 , d = 0;
    for(int i = 0; i < 8; i++){
        cin >> input[i];
        if(i == 0) continue;
        else{
            if(input[i-1] < input[i]){
                a++;
            }
            if(input[i-1] > input[i]){
                d++;
            }
        }
    }
    if(a == 7)cout << "ascending";
    else if(d == 7)cout << "descending";
    else cout << "mixed";
    return 0;
}