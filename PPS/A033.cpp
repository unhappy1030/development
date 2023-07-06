#include <iostream>

using namespace std;

int main(){
    int i, j, max[2]={0,},arr[5] = {0,};
    for(i =0; i < 5; i++){
        for(j = 0; j < 4; j++){
            int n;
            cin >> n;
            arr[i] += n;
            if(arr[i] > max[1]){
                max[1] = arr[i];
                max[0] = i+1;
            }
        }
    }
    cout << max[0] << " " << max[1];
    return 0;
}