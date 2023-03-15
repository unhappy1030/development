#include <string>
#include <vector>

using namespace std;

string solution(string number, int k) {
    vector<char> table(number.begin(), number.end());
    for(int i = 0; i < k; i++){
        for(int j = 0; j < table.size() - 1; j++){
            if(table[j] < table[j+1]){
                table.erase(table.begin() + j);
                break;
            }
            else if(j == table.size() - 2){
                table.erase(table.begin() + j + 1);
            }
        }
    }
    string answer(table.begin(), table.end());
    return answer;
}