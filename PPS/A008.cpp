#include<iostream>
#include<vector>
using namespace std;

int main(){
    int num;
    cin >> num;
    for(int i = 0; i < num; i++){
        int c_num, input ,sum = 0, count = 0;
        vector<int> arr;
        cin >> c_num;
        for(int j = 0; j < c_num; j++){
            cin >> input;
            arr.push_back(input);
            sum += input;
        }
        double avg = double(sum) / c_num;
        for(int j = 0; j < c_num; j++){
            if(arr[j] > avg) count++;
        }
        cout << fixed;
        cout.precision(3);
        cout << double(count) / c_num * 100<< "\%\n";
    }
    return 0;
}