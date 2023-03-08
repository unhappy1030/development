#include<iostream>

using namespace std;
void quick_sort(int** arr, int start, int end);

int main() {
    int i, com_num, case_num, count = 0;
    int com_arr[101] = {0, 1, 0,};
    cin >> com_num;
    cin >> case_num;
    int **link = nullptr;
    link = new int* [case_num];
    for(i = 0; i < case_num; i++){
        int a, b ,t;
        cin >> a;
        cin >> b;
        if(a > b){
            t = a;
            a = b;
            b = t;
        }
        link[i] = new int[2]{a, b};
    }
    quick_sort(link, 0, case_num-1);
    for(i = 0; i < case_num; i++){
        if(com_arr[link[i][0]] != 0 && com_arr[link[i][1]] == 0){
           com_arr[link[i][1]] = 1;
        }
    }
    for(i = 1; i <= com_num; i++){
        if(com_arr[i] != 0) count++;
    }
    cout << count-1;
    for(i = 0; i < case_num; i++){
        delete[] link[i];
    }
    delete[] link;
    return 0;
}

void quick_sort(int** arr, int start, int end){
    if(start >= end){
        return ;
    }
    int pivot = start;
    int i = pivot + 1;
    int j = end;
    int temp[2];
    while(i <= j){
        while(i <= end && arr[i][0] <= arr[pivot][0]){
            i++;
        }
        while(j > start && arr[j][0] >= arr[pivot][0]){
            j--;
        }
        if(i > j){
            temp[0] = arr[j][0];
            temp[1] = arr[j][1];
            arr[j][0] = arr[pivot][0];
            arr[j][1] = arr[pivot][1];
            arr[pivot][0] = temp[0];
            arr[pivot][1] = temp[1];
        }
        else{
            temp[0] = arr[i][0];
            temp[1] = arr[i][1];
            arr[i][0] = arr[j][0];
            arr[i][1] = arr[j][1];
            arr[j][0] = temp[0];
            arr[j][1] = temp[1];
        }
    }
    quick_sort(arr, start, j-1);
    quick_sort(arr, j + 1, end);
}