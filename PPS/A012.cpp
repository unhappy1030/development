/*에라토스테네스의 체
1. 2부터 소수를 구하고자하는 구간의 모든 수를 나열한다.
2. 2는 소수이므로 소수로 체크한다.
3. 자기자신을 제외한 2의 배수를 모두 제거한다.
4. 남은 수 중 3은 소수이므로 소수로 체크한다.
5. 자기자신을 제외한 3의 배수를 모두 제거한다.
6. 남은 수 중 5는 소수이므로 소수로 체크한다.
7. 자기자신을 제외한 5의 배수를 모두 제거한다.
8. 남은 수 중 7은 소수이므로 소수로 체크한다.
9. 자기자신을 제외한 7의 배수를 모두 제거한다.
이 작업을 반복 수행 후 남은 수를 체크한다.

-포인트 : 아래의 i * i는 ex) 5의 배수를 제거 후 7 * 7은
(새로운 소수) * (새로운 소수) 이기에 여기까지 체크한다.
*/
class Solution {
public:
    int countPrimes(int n) {
        if (n <= 1)
        {
            return 0;
        }
        bool* PrimeArray = new bool[n + 1];
        for (int i = 2; i <= n; i++)
	        PrimeArray[i] = true;
        for (int i = 2; i * i <= n; i++)
	    {
            if (PrimeArray[i])
                for (int j = i * i; j <= n; j += i)
                    PrimeArray[j] = false;
	    }
        int count = 0;
        for(int i = 2; i < n; i++)
            if(PrimeArray[i] == true) count++;
        return count;
    }
};