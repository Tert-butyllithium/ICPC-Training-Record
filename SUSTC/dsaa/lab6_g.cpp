/* 在树（无环图）上定义一个集合，要求集合的元素全部连通，并且：
 * 将这个集合上节点的权值排序后，任意两个权值相邻点的路径上（并且属于这个集合）的点的权值都小于这两个点
 * 然后求这个最大的集合大小
 * 问题等价于：这个集合存在一个中心元素最小，然后往外依次增大，求最多能扩增多少个节点
 * 算法：dfs+记忆化搜索，枚举所有n个点作为中心元素，最后取最大值即可
 * 考虑到每个点的可能贡献只和他的子节点有关，所以可以用cnt数组存每个点的贡献
 * 简化：建图时可只考虑从权值小的往权值大的边建图（而非双向），因为所有从大的往小的都不满足要求
 * see also: https://blog.csdn.net/sotifish/article/details/47121509
 */
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 200007;

int val[maxn];
int cnt[maxn];
vector<int> vec[maxn];
int n;

void clear(){
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < maxn;i++){
        vec[i].clear();
    }
}

int dfs(int from){
    if(cnt[from])
        return cnt[from];
    cnt[from] = 1;
    for (auto c : vec[from])
    {
        cnt[from] += dfs(c);
    }
    return cnt[from];
}

int main(int argc, char const *argv[])
{
    int round;
    scanf("%d", &round);
    while(round--){
        clear();
        scanf("%d",&n);
        for (int i = 1; i <= n;i++){
            scanf("%d", &val[i]);
        }
        for (int i = 0; i < n - 1;i++){
            int x, y;
            scanf("%d%d", &x, &y);
            if(val[x]<val[y]){
                vec[x].push_back(y);
            }
            else{
                vec[y].push_back(x);
            }
        }
        for (int i = 1; i <= n;i++){
            dfs(i);
        }
        printf("%d\n", *max_element(cnt+1,cnt+1+n));
    }
    return 0;
}
