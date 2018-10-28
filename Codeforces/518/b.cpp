//题意：给一个数b，问从1到1e18之间所有的a,lcm(a,b)/a 有多少个不同的数
//考虑b的所有的因数，由于b只有1e10，O(sqrt(N))显然是可过的
#include <bits/stdc++.h>
using QAQ = long long;

int main(int argc, char const *argv[])
{
    QAQ b;
    scanf("%lld", &b);
    QAQ sq = sqrt(b);
    QAQ ans = 0;
    for (QAQ i = 1; i <= sq;i++){
        if(b%i==0){
            ans += 2;
        }
    }
    if(sq*sq==b){
        ans--;
    }
    printf("%lld\n", ans);
    return 0;
}
