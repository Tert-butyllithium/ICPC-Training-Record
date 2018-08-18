#include <iostream>
#include <vector>
#define maxn 100005
using namespace std;

int n;
int a[maxn];
vector <int> v;
int getid(int x){
    return lower_bound(v.begin(), v.end(), x)-v.begin()+1;
}

void ini(){
    for(int i=1;i<=n;i++){
        v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()),v.end());
    
}
