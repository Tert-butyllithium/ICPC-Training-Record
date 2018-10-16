//题目描述的很花哨，但是其实就是把相同的字符搞到一起
#include <bits/stdc++.h>
int apper[30];

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    getchar();
    while (n--)
    {
        char ch = getchar();
        apper[ch - 'a']++;
    }

    for (int i = 0; i < 30;i++){
        if(apper[i]){
            putchar(i + 'a');
            apper[i]--;
            i--;
        }
    }
    putchar('\n');
    return 0;
}
