//to get 2^(n-1) with n=1e(1e6);
#include <cstdio>
const int maxn = 1e6 + 10;
const int MOD = 1e9 + 7;
char str[maxn];

long long divMod(char* ch,int num)
{
	long long s = 0;
	for(int i=0;ch[i]!='\0';i++)
		s = (s*10+ch[i]-'0')%num;
	return s;
}


inline long long pow(const int n, const int k) {
    long long ans = 1;
    for (long long num = n, t = k; t; num = num * num % MOD, t >>= 1) if (t & 1) ans = ans * num % MOD;
    return ans;
}


int main(int argc, char const *argv[])
{
    int round;
    scanf("%d", &round);
    while(round--){
        scanf("%s", str);
        long long c = divMod(str, MOD - 1);
        c--;
        if(c<0)
            c += (MOD - 1);
        printf("%lld\n", pow(2, c));
    }
}
