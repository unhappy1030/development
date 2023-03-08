#include <iostream>

using namespace std;

string filter(string n){
    int i = 0;
    while(n[i] != '\0'){
        if(n[i] == '9'){
            n[i] = '6';
        }
        i++;
    }
    return n;
}

int cal(string n){
    int i = 0, count = 0, count_6 = 0;
    int arr[9]={0,};
    while(n[i] != '\0'){
        if(n[i] != '6'){
            if(arr[n[i] - '0'] == count){
                arr[n[i] - '0']++;
                count++;
                count_6 = count * 2;
            }
            else{
                arr[n[i] - '0']++;
            }
        }
        else{
            if(arr[6] == count_6){
                arr[6]++;
                count++;
                count_6 = count * 2;
            }
            else{
                arr[6]++;
            }
        }
        i++;
    }
    return count;
}

int main() {
    string num;
    cin >> num;
    num = filter(num);
    cout << cal(num);
    return 0;
}