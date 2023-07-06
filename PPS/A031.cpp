#include<iostream>

using namespace std;

int main() {
    int n , m, count = 0;
    cin >> n >> m;
    count = (n-1) + (n * (m-1));
    cout << count;
    return 0;
}