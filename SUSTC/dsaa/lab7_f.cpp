#pragma GCC optimize(2)
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace __gnu_pbds;

struct pt{
    int val;
    int id;
    pt(int val,int id):val(val),id(id){}

    const bool operator < (const pt& p) const{
      if (val == p.val) {
          return id<p.id;
      }
      else{
          return val<p.val;
      }
    }
};

typedef tree<pt,null_type,less< pt >,rb_tree_tag,tree_order_statistics_node_update> rbtree;

rbtree rbt;
int n,m,delta;

int del(int tar) {
  int cnt = 0;
  while (true) {
    auto c = rbt.find_by_order(0);
    if (c->val >= tar) {
      return cnt;
    }
    cnt++;
    rbt.erase(c);
  }
}

int main(int argc, char const *argv[])
{
    int round;
    scanf("%d",&round);
    while (round--) {
        scanf("%d%d",&n,&m);
        delta=0;
        int cnt=0;
        rbt.clear();
        for(int i=0;i<n;i++){
            char op[10];
            int val;
            scanf("%s %d",op,&val);
            switch(op[0]){
                case 'I':
                    if(val>=m) rbt.insert(pt(val-delta,i));
                    break;
                case 'A':
                    delta+=val;
                    break;
                case 'S':
                    delta-=val;
                    cnt+=del(m-delta);
                    break;
                default:
                    if(rbt.size()<val){
                        puts("-1");
                    }
                    else
                        printf("%d\n",rbt.find_by_order(rbt.size()-val)->val+delta);

            }
        }
        printf("%d\n",cnt);
    }

    return 0;
}
