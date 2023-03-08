#include<iostream>

using namespace std;

int cal_price_Y(int sec);
int cal_price_M(int sec);

int main(){
    int i, n, sec, Min=0, Young=0;
    cin >> n;
    for(i = 0; i < n; i++){
        cin >> sec;
        Young += cal_price_Y(sec);
        Min += cal_price_M(sec);
    }
    if(Young > Min){
        cout << "M " << Min;
    }
    else if(Young == Min){
        cout << "Y " << "M " << Min;
    }
    else{
        cout << "Y " << Young;
    }
    return 0;
}

int cal_price_Y(int sec){
    int price = sec / 30;
    price++;
    return price * 10;
}
int cal_price_M(int sec){
    int price = sec / 60;
    price++;
    return price * 15;
}