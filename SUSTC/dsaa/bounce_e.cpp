//题意：从arr[i]中构建一个长度为n*(n-1)/2的数组，通过abs(arr[i]-arr[j]), i<j
//求这个新数组的中位数
//解法：二分答案，
#include <bits/stdc++.h>
const int maxn = 1e5 + 10;
int arr[maxn];
int n;
long long tar;

//小于等于val的值有多少个
long long test(int val){
	int i = 1, j = 2;
	long long ret = 0;
	int eq = 0;
	while (i <= n && j <= n)
	{
		if(arr[j]-arr[i]==val)
			eq++;
		while (arr[j] - arr[i] > val)
		{
			i++;
		}
		// printf("%d %d\n", i, j);
		ret += (j - i);
		// i++;
		j++;
	}
	return ret;
}

inline bool judge(int val){
	return test(val) <= tar;
}

int main(int argc, char const *argv[])
{
	int round;
	scanf("%d", &round);
	while(round--){
		scanf("%d", &n);
		tar = (1ll * n * (n - 1) / 2 + 1) / 2;
		for (int i = 1; i <= n;i++){
			scanf("%d", &arr[i]);
		}
		std::sort(arr + 1, arr + n + 1);
		// printf("%lld\n", test(8));
		int left = 0, right = arr[n] - arr[1];
		while(left<=right){
			int mid = (left + right) / 2;
			long long cmp = test(mid);
			if(cmp==tar){
				left = right = mid;
				break;
			}
			else if(cmp<tar){
				left = mid + 1;
			}
			else{
				right = mid - 1;
			}
		}
    //我也不知道为啥这里取max
		printf("%d\n", std::max(left , right));
	}
	return 0;
}
