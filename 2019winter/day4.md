# day4

## A - [HDU 1166](http://acm.hdu.edu.cn/showproblem.php?pid=1166)

题意：树状数组裸题，单点+/-，区间求和

```c++
#include <bits/stdc++.h>

const int maxn = 100005;
inline int lowbit(int x) { return x & (-x); }
int bit[maxn];

void update(int x,int v){
    for (int i = x; i < maxn;i+=lowbit(i)){
        bit[i] += v;
    }
}

int query(int x){
    int res = 0;
    for (int i = x; i; i -= lowbit(i))
    {
        res += bit[i];
    }
    return res;
}
char str[10];
int main(int argc, char const *argv[])
{
    int round;
    scanf("%d", &round);
    for (int ca = 1; ca <= round;ca++){
        memset(bit, 0, sizeof(bit));
        printf("Case %d:\n", ca);
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n;i++){
            int x;
            scanf("%d", &x);
            update(i, x);
        }
        while(scanf("%s",str)&&str[0]!='E'){
            int x, y;
            scanf("%d%d", &x, &y);
            if (str[0] == 'Q')
            {
                printf("%d\n", query(y) - query(x - 1));
            }
            else if(str[0]=='A'){
                update(x, y);
            }
            else{
                update(x, -y);
            }
        }
    }
    return 0;
}
```

## B - [HDU 1540](http://acm.hdu.edu.cn/showproblem.php?pid=1540)

题意：有n个村庄，最开始相邻的村庄都相连，对应q个操作，摧毁，重建和查询。摧毁之后村庄与相邻的村庄都不再相连。每个查询问这个村庄和多少个村庄相连。

题解：把村庄存在与否看作0和1，摧毁和重建就转化为赋值为0和赋值为1，查询就是问这个点的连续区间。于是就是一个线段树区间覆盖问题，最麻烦的步骤就是线段树的query

错误分析：我最开始时试图用一个bool变量来表示“我当前查询的区间是在区间中点”的左边还是右边，这样就非常难以维护和debug，实际上只需顺便传入查询的当前值p，每次查询与当前区间做比较即可。

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;

#define ls l, m, rt << 1
#define rs m + 1, r, rt << 1 | 1

//leftv: 当前区间从左开始的连续“1”的个数（前缀）
//rightv:当前区间从右开始的连续“1”的个数（后缀）
//Sum: max(leftv,rightv)
int Sum[maxn << 2];
int leftv[maxn << 2], rightv[maxn << 2];
void PushUp(int l, int r, int rt)
{
    int m = (l + r) >> 1;
    int lc = rt << 1;
    int rc = rt << 1 | 1;
    leftv[rt] = leftv[lc];
    rightv[rt] = rightv[rc];
    Sum[rt] = max(max(leftv[lc], rightv[rc]), rightv[lc] + leftv[rc]);
    if (rightv[lc] == m - l + 1)
    {
        leftv[rt] += leftv[rc];
    }
    if (leftv[rc] == r - m)
    {
        rightv[rt] += rightv[lc];
    }
}

void Build(int l, int r, int rt)
{ 
    //初始化时，由于全是1，所以维护的三个量都等于当前区间长度
    leftv[rt] = rightv[rt] = Sum[rt] = r-l+1;
    if (l == r)
        return;
    int m = (l + r) >> 1;
    Build(l, m, rt << 1);
    Build(m + 1, r, rt << 1 | 1);
    PushUp(l, r, rt);
}

void Update(int L, int C, int l, int r, int rt)
{ 
    if (l == r)
    { 
        Sum[rt] = C;
        leftv[rt] = C;
        rightv[rt] = C;
        return;
    }
    int m = (l + r) >> 1;
    if (L <= m)
        Update(L, C, l, m, rt << 1);
    else
        Update(L, C, m + 1, r, rt << 1 | 1);
    PushUp(l, r, rt);
}

int query(int p, int l, int r, int rt)
{
    if (Sum[rt] == r - l + 1 || Sum[rt] == 0 || l == r)
    {
        return Sum[rt];
    }
    int m = (l + r) >> 1;
    int lc = rt << 1;
    int rc = lc | 1;
    if (p <= m)//如果需要查询元素在区间中点左边，那就是需要继续查询左区间
    {
        if (m - p + 1 <= rightv[lc])//如果元素到中点都是“1”，那还可以加上右儿子的前缀
        {
            return query(p, l, m, lc) + leftv[rc];
        }
        else
        {
            return query(p, l, m, lc);
        }
    }
    else//否则，查询右区间
    {
        if (p - m <= leftv[rc])//如果元素到终点都是“1”，那还可以加上左儿子的后缀
        {
            return query(p, m + 1, r, rc) + rightv[lc];
        }
        else
        {
            return query(p, m + 1, r, rc);
        }
    }
}

char str[10];
stack<int> last;
int main(int argc, char const *argv[])
{
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF)
    {
        Build(1, n, 1);
        while (m--)
        {
            scanf("%s", str);
            int x;
            if (str[0] == 'R')
            {
				int r = last.top();
				last.pop();
				Update(r, 1, 1, n, 1);
				continue;
            }
            scanf("%d", &x);
            if (str[0] == 'D')
            {
                Update(x, 0, 1, n, 1);
				last.push(x);
			}
			else
            {
                printf("%d\n", query(x, 1, n, 1));
            }
        }
    }
    return 0;
}
```

## C - [Codeforces #426 Div.1 B](https://codeforces.com/problemset/problem/833/B)

题意：将n长序列划分 k 块的最大价值和。每块的价值定义为该段区间内的**不同数**的个数。其中 N 长序列的每个数为 a1,a2,⋯,an， (1 ≤ n≤ 35000, 1 ≤ k ≤ min(n, 50)) 

题解：枚举k，状态转移方程为`dp[i][k] = max(dp[i][k], dp[j][k-1] + distinct(j+1, i))`，难点在如何计算`distinct(j+1,i)`，考虑如果第i个数字对第k块有贡献，那么必然是这第k块的第一个“i”，预处理数组pre[i]，表示与第i个数字相同的数字前一个的位置，用（区间最大）线段树维护，对于每个数字所处的位置i，`update(pre[i],i-1,+1)` 并查找`[1,i-1]`的区间最大值就代表最大的`distinct(j+1,i)`。初始化线段树时，用前一次迭代的结果给叶子节点赋值，于是迭代n次后就是答案。

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 35010;
const int maxk = 55;
const int INF = 0x3f3f3f3f;
using LL = int;
int dp[maxn][maxk];
int pre[maxn];
int a[maxn];
int pos[maxn];
int n, k;

int maxv[maxn<<2],add[maxn<<2];
// #define mid ((l + r)/2)
#define lson l, mid, rt << 1
#define rson mid+1, r, (rt<<1|1)
void pushdown(int rt){
	if(add[rt]){
		add[rt << 1] += add[rt];
		add[rt << 1 | 1] += add[rt];
		maxv[rt << 1] += add[rt];
		maxv[rt << 1 | 1] += add[rt];
		add[rt] = 0;
	}
}

inline void pushup(int rt){
	maxv[rt] = max(maxv[rt << 1], maxv[rt << 1 | 1]);
}

void build(int l,int r,int rt,int j){
	add[rt] = 0;
	if(l==r){
		maxv[rt] = dp[l][j];
		return;
	}
	int mid = (l + r) / 2;
	build(lson, j);
	build(rson, j);
	pushup(rt);
}

void update(int ql,int qr,int l,int r,int rt){
	if(ql>qr)
		return;
	if (ql <= l&&r <= qr)
	{
		add[rt]++;
		maxv[rt]++;
		return;
	}
	pushdown(rt);
	int mid = (l + r) / 2;
	if (ql <= mid)
		update(ql, qr, lson);
	if(qr>mid)
		update(ql, qr, rson);
	pushup(rt);
}

int qmax(int ql,int qr,int l,int r,int rt){
	if (ql<= l &&qr>=r)
		return maxv[rt];
	pushdown(rt);
	int ret = -INF;
	int mid = (l + r) / 2;
	if (ql <= mid)
		ret = max(ret, qmax(ql, qr, lson));
	if(qr>mid)
		ret = max(ret, qmax(ql, qr, rson));
	return ret;
}


int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n;i++){
		scanf("%d", &a[i]);
		if(pos[a[i]])
			dp[i][1] = dp[i - 1][1];
		else
			dp[i][1] = dp[i - 1][1] + 1;
		pre[i] = max(pos[a[i]], 1);
		pos[a[i]] = i;
	}

	for (int j = 2; j <= k; j++)
	{
		build(1, n, 1, j - 1);
		dp[1][j] = 1;
		for (int i = 2; i <= n; i++)
		{
			update(pre[i], i - 1, 1, n,1);
			dp[i][j] = qmax(1, i - 1, 1,n,1);
		}
	}
	printf("%d\n", dp[n][k]);
	return 0;
}
```

## D - [POJ 3281](http://poj.org/problem?id=3281)

题意：有N头牛，F种食物，D种饮料。给定每只牛喜好的食物与饮料（可能不只一种）每种食物，每种饮料都只能分配给一头牛。请问，在最优的分配下，最多有多少只牛能吃到它喜好的食物，并喝到喜好的饮料。

题解：最大流，需要注意的是牛需要拆开成两个点，两点流量为1，确保一头牛只被选一次。

```c++
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
struct E
{
	int to, cp;
};

struct Dinic {//Dinic 是板子的内容，故只保留接口
    void init(int n, int s, int t);
    void addedge(int u, int v, int cap);
    bool BFS();
    int DFS(int u, int cp);

    int go() {
        int flow = 0;
        while (BFS()) {
            memset(cur, 0, sizeof cur);
            flow += DFS(s, INF);
        }
        return flow;
    }
} DC;

int n, f, d;
int main(int argc, char const *argv[])
{
	scanf("%d%d%d", &n, &f, &d);
	//s: 0, t: 1+2n+f+d
	//f: 1..f
	//n: f+1..f+n and f+n+1..f+2n
	//d: 2n+f+1..2n+f+1+d
	int s = 0, t = 1 + 2*n + f + d;
	DC.init(t - s + 1, s, t);

	for (int i = 1; i <= n;i++){
		int fi, di;
		scanf("%d%d", &fi, &di);
		while(fi--){
			int fx;
			scanf("%d", &fx);
			DC.addedge(fx, f + i, 1);
		}
		DC.addedge(f + i, f + n + i,1);
		while(di--){
			int dx;
			scanf("%d", &dx);
			DC.addedge(f + n + i, dx + 2 * n + f, 1);
		}
	}
	for (int i = 1; i <= f;i++){
		DC.addedge(s, i, 1);
	}
	for (int i = 1; i <= d;i++){
		DC.addedge(2 * n + f + i, t, 1);
	}

	printf("%d\n", DC.go());

	return 0;
}
```

## E -  [Educational Codeforces Round 42 D](https://codeforces.com/problemset/problem/962/D)

题意：给一个数组，可以进行如下操作：选取最小出现两次的数字，左边的去掉，右边的变成两倍。一直进行这个操作，问最后剩下什么东西

题解：用heap维护一个node序列，node表示每个值和对应位置，以值以第一序，位置为第二序。每次pop一个node，如果这个与堆顶的node的值相等就push一个新的，表示进行过一次这样的操作，否则直接加入答案。

```kotlin
import java.lang.Integer.compare
import java.util.*
import java.util.Collections.sort
import kotlin.collections.ArrayList

class Node(val id:Int,var v:Long=0) :Comparable<Node>{
    override fun compareTo(other: Node): Int {
        return when {
            v==other.v -> id-other.id
            v<other.v -> -1
            else -> 1
        }
    }
}

fun main(args: Array<String>) {
    val ans:ArrayList<Node> = ArrayList()
    val heap:PriorityQueue<Node> = PriorityQueue()

    val scanner:Scanner= Scanner(System.`in`)
    val n=scanner.nextInt()

    for(i in 1..n){
        val x=scanner.nextInt()
        heap.add(Node(i,x.toLong()))
    }

    while (!heap.isEmpty()){
        val first=heap.poll()
        if((!heap.isEmpty())&&first.v==heap.peek().v){
            val second=heap.poll()
            heap.add(Node(second.id,second.v*2))
        }
        else{
            ans.add(first)
        }
    }
    sort(ans) { a, b-> compare(a.id,b.id)}
    println(ans.size)
    for(c in ans)
        print("${c.v} ")

}
```

## F - [Educational Codeforces Round 40](https://codeforces.com/problemset/problem/954/G)

题意：城墙上有n个连成一排的区域，每个区域中有一些弓箭手。弓箭手们都有r的防御半径，也就是说，弓箭手能够防守到向左或向右r个区域加上自己所处区域的范围。每个区域的防御等级为能够防守到该区域的弓箭手数量的总和，而城墙的防御等级为各区域防御等级的最小值。现在我们共有k名备用弓箭手可以增援这n个区域。问增援后城墙的防御等级的最大值能达到多少

题解：考虑二分，注意到防御等级最小值为x时需要额外的弓箭手数量与k之间的关系，显然x与k单调。检验时维护一个长度为r+1的滑动窗口[i,i+r+1]，表示第i个的值，每次增加弓箭手加到滑动窗口最右边最优。这里不能使用线段树/树状数组，不只是可能TLE(Kotlin 1.3 TLE on test 18)，还（疑似）存在爆long long的风险（WA on test 19）（注意：CF测评🐔由于Windows环境采用32位的GNU C++，不支持`__int128`）

```c++
#include <bits/stdc++.h>
using ll = long long;
const int maxn = 500005;
ll arr[maxn];
ll a[maxn];
int n, r;
ll k;

bool judge(ll val){
    memcpy(a, arr, sizeof(arr));
    ll cnt = 0;
    ll sum = 0;
    for (int i = 1; i <= r+1;i++){
        sum += arr[i];
    }
    int left = 1;
    int right = r + 1;
    for (int i = 1; i <= n; i++)
    {
        if (sum < val)
        {
            cnt += val - sum;
            a[right] += val - sum;
            if (cnt > k)
                return false;
            sum = val;
        }
        if(right<n){
            right++;
            sum += a[right];
        }
        if(i>r){
            sum -= a[left];
            left++;
        }
    }
    return cnt<=k;
}

int main(int argc, char const *argv[])
{
    scanf("%d%d%lld", &n, &r, &k);
    for (int i = 1; i <= n;i++){
        scanf("%lld", &arr[i]);
    }
    ll left = *std::min_element(arr+1,arr+n+1);
    ll right = LLONG_MAX;
    while (left < right)
    {
        ll mid = left + (right - left) / 2ll;
        if(judge(mid)){
            if(!judge(mid+1)){
                left = right = mid;
                break;
            }
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    printf("%lld", right);

    return 0;
}
```

