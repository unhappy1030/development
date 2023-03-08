#include <iostream>
#include <algorithm>
using namespace std;



int main() {
    int i, n, a[50] = {0,}, b[50] = {0,} , r = 0;
    cin >> n;
    for(i = 0; i < n; i++) cin >> a[i];
    for(i = 0; i < n; i++) cin >> b[i];
    sort(a, a+n);
    sort(b, b+n);
    for(i = 0; i < n; i++){
        r += a[i] * b[n-i-1];
    }
    cout << r;
    return 0;
}