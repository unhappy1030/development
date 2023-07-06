#include <iostream>

using namespace std;

int main() {
    int i, j, n;
    cin >> n;
    double num;
    string s;
    for(i = 0; i < n; i++){
        cin >> num;
        getline(cin, s);
        for(j = 0; j < s.size(); j++){
            if(s[j] == '@'){
                num *= 3;
            }
            else if(s[j] == '%'){
                num +=5;
            }
            else if(s[j] == '#'){
                num -=7;
            }
        }
        cout << fixed;
        cout.precision(2);
        cout << num << endl;
    }
    return 0;
}