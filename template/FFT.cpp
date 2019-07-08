inline void FFT(vector<CD> &a, bool inverse)
{
    int n = a.size();
    // 原地快速 bit reversal
    for (int i = 0, j = 0; i < n; i++)
    {
        if (j > i)
            swap(a[i], a[j]);
        int k = n;
        while (j & (k >>= 1))
            j &= ~k;
        j |= k;
    }
    double pi = inverse ? -PI : PI;
    for (int step = 1; step < n; step <<= 1)
    {
        // 把每相邻两个“step 点 DFT”通过一系列蝴蝶操作合并为一个“2*step 点 DFT”
        double alpha = pi / step;
        // 为求高效，我们并不是依次执行各个完整的 DFT 合并，而是枚举下标 k
        // 对于一个下标 k，执行所有 DFT 合并中该下标对应的蝴蝶操作，即通过 E[k] 和 O[k] 计算 X[k] 
        // 蝴蝶操作参考:http://en.wikipedia.org/wiki/Butterfly_diagram
        for (int k = 0; k < step; k++)
        {
            // 计算 omega^k. 这个方法效率低，但如果用每次乘 omega 的方法递推会有精度问题。
            // 有更快更精确的递推方法，为了清晰起见这里略去
            CD omegak = exp(CD(0, alpha * k));
            for (int Ek = k; Ek < n; Ek += step << 1)
            {                       //Ek 是某次 DFT 合并中 E[k] 在原始序列中的下标
                int Ok = Ek + step; // Ok 是该 DFT 合并中 O[k] 在原始序列中的下标 
                CD t = omegak * a[Ok]; // 蝴蝶操作:x1 * omega^k 
                a[Ok]=a[Ek]-t; // 蝴蝶操作:y1=x0-t
                a[Ek] += t;         // 蝴蝶操作:y0=x0+t
            }
        }
    }
    if (inverse)
        for (int i = 0; i < n; i++)
            a[i] /= n;
}
// 用 FFT 实现的快速多项式乘法
inline vector<double> operator*(const vector<double> &v1, const vector<double> &v2)
{
    int s1 = v1.size(), s2 = v2.size(), S = 2;
    while (S < s1 + s2)
        S <<= 1;
    vector<CD> a(S, 0), b(S, 0); // 把 FFT 的输入长度补成 2 的幂，不小于 v1 和 v2 的长度之和 
    for(int i = 0; i < s1; i++) a[i] = v1[i];
    FFT(a, false);
    for (int i = 0; i < s2; i++)
        b[i] = v2[i];
    FFT(b, false);
    for (int i = 0; i < S; i++)
        a[i] *= b[i];
    FFT(a, true);
    vector<double> res(s1 + s2 - 1);
    for (int i = 0; i < s1 + s2 - 1; i++)
        res[i] = a[i].real(); // 虚部均为 0
    return res;
}

