//仅仅展示代码片段，目的求多项式的平方

void FFT(complex<double> x[], int n, int p) {
    for (int i=0,t=0;i<n;i++)
    {
        if (i>t) swap(x[i],x[t]);
        for (int j=n>>1;(t^=j)<j;j>>=1);
    }
    for (int m=2;m<=n;m<<=1)  //枚举每一层
    {
        complex<double>       wn(cos(p*2*pi/m),sin(p*2*pi/m));
        for (int i=0;i<n;i+=m)
        {
            complex<double> w(1,0),u;
            int k=m>>1;
            for (int j=0;j<k;j++,w*=wn)
            {
                //蝴蝶操作
                u=x[i+j+k]*w;
                x[i+j+k]=x[i+j]-u;
                x[i+j]=x[i+j]+u;
            }
        }
    }
}

//扩展成最近的2^n
int NTT_init(int n_) {
    int n = 1;
    for (; n < n_; n <<= 1);
    return n;
}

// main 里面的代码片段
    FFT(ra, len, 1);
    for (int i = 0; i < len; i++) {
        ra[i] = ra[i] * ra[i];
    }
    FFT(ra, len, -1);
