//ez题，但是wa了两发。。
#include <bits/stdc++.h>
using QAQ = long long;
int a,b;
bool vis[(int)1e5 + 10];

QAQ cal(){
    QAQ x = a + b;
    return (sqrt(1 + 8 * x) - 1)/ 2;
}

int main(int argc, char const *argv[])
{
    scanf("%d%d", &a, &b);
    int n=cal();
    // printf("%lld\n", n);
    int c = 0;
    //思考的时候考虑了重复的情况，但是敲的时候没有考虑两次i会相等
    //另外就是i要>0，（莫名其妙搞成a>0了
    for (int i = std::min(n, a); i>0;)
    {
        if (!vis[i])
        {
            c++;
            vis[i] = 1;
            a -= i, i = std::min(n, a);
        }
        else{
            i--;
        }
    }
    printf("%d\n", c);
    for (int i = 1; i <= n;i++){
        if(vis[i]){
            printf("%d ", i);
        }
    }
    puts("");
    printf("%d\n", n - c);
    for (int i = 1; i <= n;i++){
        if (!vis[i]){
            printf("%d ", i);
        }
    }
    puts("");
    return 0;
}
 
