//恶心的卡常题，卡掉了递归的dfs
//题解说是要记录前65536个状态？发现有大佬这么写的：
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

unordered_map<string, int> maps[20];
int main(int argc, char const *argv[])
{
    int n;
    string str, str1, str2, str3;
    ios::sync_with_stdio(false);
    cin >> n >> str;
    maps[n][str] = 1;
    for (int i = n; i >= 1;i--){
        for (auto it = maps[i].begin(); it != maps[i].end();it++){
            str = it->first;
            int s1 = it -> second;
            str1 = str2 = str3 = "";
            for (int j = 0; j < str.size();j+=2){
                str1 += ((str[j] - '0') & (str[j + 1] - '0')) + '0';
                str2 += ((str[j] - '0') | (str[j + 1] - '0')) + '0';
                str3 += ((str[j] - '0') ^ (str[j + 1] - '0')) + '0';
            }
            maps[i - 1][str1] += s1;
            maps[i - 1][str2] += s1;
            maps[i - 1][str3] += s1;
        }
    }
    cout << maps[0]["1"] << endl;
    return 0;
}
