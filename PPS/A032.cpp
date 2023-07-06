#include<iostream>

using namespace std;

int cal(int n, int k);

int main(){
    
    return 0;
}

int cal(int n, int k){
    int i, j, t;
    int arr[2][14] = {0,};
    for(i = 0; i < n; i++){
        for(j = 0; j < k; j++){
            if(i == 0){
                arr[0][j] = j + 1;
            }
            else{
                for(t = 0; t < j; j++){
                    arr[1][j] += arr[0][t];
                }
            }
        }
        for(j = 0; j < k; j++){
            arr[0][j] = arr[1][j];
        }
    }
    return arr[n-1][k-1];
}