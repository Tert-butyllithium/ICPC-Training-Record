//简单的贪心
#include <iostream>
#include <cstring>
 
using namespace std;
const int maxn = 100009;
long long a[maxn];
 
int main(){
    int round;
    scanf("%d",&round);
    while(round--){
        memset(a, 0, sizeof(a));
        int n;
        scanf("%d", &n);
        for(int i=1;i<=n;i++)
            scanf("%lld", &a[i]);
 
        long long maxp = 0;
        int tot = 0;
        for (int i = 1; i < n;i++){
            if(a[i+1]<a[i])
               continue;
            int j = i + 1;
            if(a[j]-a[i]>0){
                while(j<n&&a[j+1]>=a[j])  j++;//注意这个地方是>=，wa7就是wa在这
                maxp += a[j] - a[i];
                tot++;
                i = j;
            }
 
        }
        printf("%lld %d\n", maxp, tot * 2);
    }
     
}
