#include <iostream>
#define maxn 50005
using namespace std;

int d[maxn][20];
int e[maxn][20];
void RMQ_init(int n){
    for (int j = 1; (1 << j) <= n;j++){
        for (int i = 0; i + (1 << j) - 1 < n;i++){
            d[i][j] = std::min(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
            e[i][j] = std::max(e[i][j - 1], e[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int RMQ(int l,int r){
    int k = 0;
    while((1<<(k+1))<=r-l+1)
        k++;
    return std::max(e[l][k], e[r - (1 << k) + 1][k])-std::min(d[l][k], d[r - (1 << k) + 1][k]);
}


int main(int argc, char const *argv[])
{
    int n, q;
    while(scanf("%d%d",&n,&q)!=EOF){
        for (int i = 0; i < n;i++){
            scanf("%d", &d[i][0]);
            e[i][0] = d[i][0];
        }
        RMQ_init(n);
        while(q--){
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", RMQ(l-1, r-1));
        }
    }
    return 0;
}
