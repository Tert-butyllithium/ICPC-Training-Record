//题意：给出一个序列，然后找出其中的一个子序列bi，要求bi%i==0
//思路：考虑dp，对于序列每一个元素在bi中index（如果可以成为）将会是之前所有的index-1个数只和
//即：dp[j]+=dp[j-1], with arr[i]%j=0;
#include <bits/stdc++.h>
// #define debug
using std::vector;
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
int div_by_i[maxn];
int arr[maxn];
vector<int> vec[(int)(1e5 + 1)];

void cal_divs(int index){
    for (int i = 1; i * i <= arr[index];i++){
        if(arr[index]%i==0){
            vec[index].push_back(i);
            if(i*i!=arr[index])
                vec[index].push_back(arr[index] / i);
        }
    }
    std::sort(vec[index].begin(), vec[index].end());
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n;i++){
        scanf("%d", &arr[i]);
    }
    div_by_i[0] = 1;
    long long ans = 0;
    for (int index = 1; index <= n; index++)
    {
        cal_divs(index);
    }
    #ifdef debug
    for (int i = 1; i <= n;i++){
        printf("%d: ", arr[i]);
        for (auto c : vec[i])
        {
            printf("%d ", c);
        }
        puts("");
    }
#endif
    for (int i = 1; i <= n;i++){
        for (auto it = vec[i].rbegin(); it != vec[i].rend();it++){
            if((*it)>i)
                continue;
            div_by_i[*it] += div_by_i[(*it) - 1];
            div_by_i[*it] %= mod;
            // ans += div_by_i[(*it) - 1];
        }
    }
    for (int i = 1; i < maxn;i++){
        ans = (ans + div_by_i[i])%mod;
    }
    printf("%lld\n", ans % mod);

    return 0;
}
