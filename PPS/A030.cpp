#include<iostream>

using namespace std;

int main() {
    int n, t_mood, count = 1;
    double rt[2][2]={0,}, re_g = 0, re_b = 0;
    cin >> n >> t_mood;
    cin >> rt[0][0] >> rt[0][1];
    cin >> rt[1][0] >> rt[1][1];
    re_g = rt[t_mood][0];
    re_b = rt[t_mood][1];
    while(count != n){
        double g, b;
        g = re_g * rt[0][0] + re_b * rt[1][0];
        b = re_g * rt[0][1] + re_b * rt[1][1];
        re_g = g;
        re_b = b;
        count++;
    }
    cout << (int)(re_g * 1000) << endl;
    cout << (int)(re_b * 1000) << endl;
    return 0;
}