//利用费马小定理，要求MOD为质数
inline int pow(const int n, const int k) {
    long long ans = 1;
    for (long long num = n, t = k; t; num = num * num % MOD, t >>= 1) if (t & 1) ans = ans * num % MOD;
    return ans;
}

inline int inv(const int num) {
    return pow(num, MOD - 2);
}

//扩展欧几里得
void exgcd(const int a, const int b, int &g, int &x, int &y) {
    if (!b) g = a, x = 1, y = 0;
    else exgcd(b, a % b, g, y, x), y -= x * (a / b);
}

inline int inv(const int num) {
    int g, x, y;
    exgcd(num, MOD, g, x, y);
    return ((x % MOD) + MOD) % MOD;
}
