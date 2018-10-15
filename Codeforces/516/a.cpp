#include <bits/stdc++.h>

int tri[3];
int main(int argc, char const *argv[])
{
    scanf("%d%d%d", tri, tri + 1, tri + 2);
    std::sort(tri,tri+3);
    int cas1 = 0;
    if(tri[0]+tri[1]<=tri[2]){
        cas1 = tri[2] - tri[0] - tri[1] + 1;
    }
    /* int cas2 = 0;
    if(tri[2]-tri[0]>=) */
    printf("%d\n", cas1);
    return 0;
}
