//01分数规划（二分）
//用来解答 sum(ai)/sum(bi)最大问题
//sum(ai)/sum(bi)>L ==> F(L)=sum[(ai)-L*(bi)]>0
//那么对a[i]-L*b[i]排序，去掉最小的k个，求和就能判断这L是否符合条件
//然后就可以二分了，复杂度O(N*log(N)*log(N))
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
const double eps = 1e-8;

int n, k;
struct lec
{
    double s, c;
    bool operator <(const lec&l) const{
        return c < l.c;
    }
};
lec lecs[maxn];
double res[maxn];

bool test(double x){
    for (int i = 0; i < n;i++){
        res[i] = lecs[i].s * (lecs[i].c - x);
    }
    sort(res,res+n);
    double sum=0;
    for (int i = k; i < n;i++){
        sum += res[i];
    }
    return sum > 0;
}

int main(int argc, char const *argv[])
{
    double s_sum = 0;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n;i++){
        scanf("%lf", &lecs[i].s);
        s_sum += lecs[i].s;
    }
    for (int i = 0; i < n;i++){
        scanf("%lf", &lecs[i].c);
    }
    double l = min_element(lecs, lecs + n)->c;
    double r = max_element(lecs, lecs + n)->c;
    while(r-l>eps){
        double mid = (l + r) / 2;
        if(test(mid)){
            l = mid;
        }else{
            r = mid;
        }
    }
    printf("%lf\n", l);
    return 0;
}
