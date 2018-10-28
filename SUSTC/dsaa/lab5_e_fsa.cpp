// see https://wycers.github.io/posts/dsaa-lab5-G.html
#include <bits/stdc++.h>
using QAQ = long long;
const int maxn = 1e5 + 10;
const int inf = 0x3f3f3f3f;

struct fsa
{
    int next[maxn][26], from[maxn], now, len, last, top;
    void build(char* str){
        last = 0;
        from[0] = 0;
        memset(next, 0, sizeof next);
        len = strlen(str);
        now = 0;
        for (int i = 0; i < len;i++){
            int ch = str[i] - 'a';
            for (int c = 0; c < 26;c++){
                if(c==ch){
                    next[i][c] = i + 1;
                }
                else{
                    next[i][c] = next[last][c];
                }
            }
            if (i)
            {
                last = next[last][ch];
            }
        }

        for (int c = 0; c < 26;c++){
            next[len][c] = next[last][c];
        }
    }

    void go(int ch){
        from[++top] = now;
        now = next[now][ch];
    }

    int getans(){
        return len - now;
    }

    void goback(){
        if(top){
            now = from[top--];
        }
        else
            now = 0;
    }
};

fsa fff[4];
int n,ans[maxn];
char str[maxn];

int getans(){
    int res = inf;
    for (int i = 0; i < n;i++){
        res = std::min(res, fff[i].getans());
    }
    return res;
}

void go(int ch){
    for (int i = 0; i < n;i++){
        fff[i].go(ch);
    }
}

void goback(){
    for (int i = 0; i < n;i++){
        fff[i].goback();
    }
}

int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for (int i = 0; i < n;i++){
        scanf("%s", str);
        fff[i].build(str);
    }
    printf("%d\n", getans());
    scanf("%s", str);
    int l = strlen(str);
    for (int i = 0; i < l;i++){
        if(str[i]=='-'){
            goback();
        }
        else{
            go(str[i] - 'a');
        }
        printf("%d\n", getans());
    }

    return 0;
}
