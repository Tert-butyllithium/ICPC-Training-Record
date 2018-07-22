//找规律题，奇数要特判
#include <iostream>
#include <cstring>
const int maxn = 1e6 + 10;

int x_broken[maxn], y_broken[maxn];
int main(int argc, char const *argv[])
{
    int n, m;
    memset(x_broken, 0, sizeof(x_broken));
    memset(y_broken, 0, sizeof(y_broken));
    scanf("%d%d", &n, &m);
    int ans = (n << 1);
    while(m--){
        int x, y;
        scanf("%d%d",&x,&y);
        if(!x_broken[x])
            x_broken[x]++, ans--;
        if(!y_broken[y])
            y_broken[y]++, ans--;
    }
    if(n&1&&!x_broken[(n+1)>>1]&&!y_broken[(n+1)>>1])
        ans--;
    printf("%d\n", ans);

    return 0;
}
