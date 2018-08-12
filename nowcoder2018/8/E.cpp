//这是个傻逼题：n*m的棋盘，相邻的格子相连，k条边相连，每条边权值1，问遍历所有点最短是多少
//1.不能一笔画：一个点通过两次，答案为n*m+1，2.能一笔画，答案为n*m；
//若n*m为偶数，必然能一笔画，若为奇数，将棋盘黑白染色（1，1是黑色），因为黑色点更多，若存在一条边链接两个黑色点，则能一笔画

#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;

bool colors[maxn][maxn];
int m, n;

void dye(){
    memset(colors, 0, sizeof(colors));
    for (int i = 1; i <= n;i++){
        for (int j = (i % 2 == 1); j <= m;j+=2)
            colors[i][j] = 1;
    }
}

int main(int argc, char const *argv[])
{
    int round;
    scanf("%d", &round);
    while(round--){
        int k;
        scanf("%d%d%d", &n, &m, &k);
        bool flag = false;
        dye();
        if(n*m%2==0)
            flag = true;
        while (k--)
        {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            if(x1==x2&&y1==y2)
                continue;
            if (colors[x1][y1] && colors[x2][y2])
                flag = true;
        }
        int ans = n * m;
        if(!flag)
            ans++;
        printf("%d\n", ans);
    }
}
