//三堆相当于Nim Game，取异或即可
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10005;
const int Fibo[] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233,
              377, 610, 987, 1597, 2584, 4181, 6765, 10946};
int sg[maxn];
int s[maxn];
void get_sg()
{
    memset(sg, 0, sizeof(sg));
    for (int i = 1; i < maxn;i++){
        memset(s, 0, sizeof(s));
        for (int j = 0; Fibo[j] <= i && j <= 20;j++){
            s[sg[i - Fibo[j]]] = 1;
        }
        for (int j = 0;;j++){
            if(!s[j]){
                sg[i] = j;
                break;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    int a, b, c;
    get_sg();
    while (cin >> a >> b >> c)
    {
        if(a==0&&b==0&&c==0)
            return 0;
        if (sg[a] ^ sg[b] ^ sg[c])
        {
            cout << "Fibo" << endl;
        }
        else{
            cout << "Nacci" << endl;
        }
    }
}
