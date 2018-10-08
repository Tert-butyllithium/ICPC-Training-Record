//啊，kmp什么的，去死
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int N = 205;
int _next[N];
char a[N];
char tmp[N];
string arr[1005];

auto sub_strings(string str){
    vector<string> res;
    for (int i = 0; i < str.length(); i++)
    {
        for (int j = 1;j<str.length()-i+1 ;j++){
            res.push_back(str.substr(i, j));
            // puts(str.substr(i, j).c_str());
        }
    }
    sort(res.begin(), res.end());
    return res;
}

int main(int argc, char const *argv[])
{
    int round;
    scanf("%d", &round);
    while(round--){
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n;i++){
            scanf("%s", tmp);
            arr[i] = string(tmp);
        }
        sort(arr, arr + n);
        auto subs = sub_strings(string(arr[0]));
        string ans;
        for (auto s : subs)
        {
            if(s.length()<=ans.length()){
                continue;
            }
            bool flag = true;
            for (int i = 1; i < n; i++)
            {
                if(arr[i].find(s)==string::npos){
                    flag = false;
                    break;
                }
            }
            if(flag){
                ans = s;
            }
        }
        if(ans==""){
            puts("Hong");
        }
        else{
            puts(ans.c_str());
        }
    }
    return 0;
}
