#include<iostream>

using namespace std;

int main(){
    int i = 42;
    string s = to_string(i);
    s += to_string(i);
    cout << s << endl;
    return 0;
}