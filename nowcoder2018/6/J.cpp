//取前300个就好了
#include <bits/stdc++.h>
using namespace std;
 
unsigned A, B, C, t;
unsigned x, y, z;

struct smg{
    priority_queue<unsigned,vector<unsigned> ,greater<unsigned> > vals;
    int v;
    void clear(){
        while(!vals.empty())
            vals.pop(); 
    }
 
    void push(unsigned val)
    {
        if(vals.size()<500)
          vals.push(val);
        else if(val>vals.top()){
            vals.pop();
            vals.push(val);
        }
    }
 
    vector<unsigned long long> getarr(){
        vector<unsigned long long> vec;
        while(!vals.empty()){
            vec.push_back(vals.top());
            vals.pop();
        }
        vec.erase(unique(vec.begin(), vec.end()),vec.end());
        return vec;
    }

    void debug(){
        while(!vals.empty()) vals.pop();
        vals.push(1);
        vals.push(2);
        vals.push(4);
        vals.push(3);
        while(!vals.empty()){
            auto a = vals.top();
            cout << a << " ";
            vals.pop();
        }
        cout << endl;
    }
};
 
unsigned tang(){
    x ^= x << 16;
    x^=x>>5;
    x^=x<<1;
    t=x;
    x=y;
    y=z;
    z = t ^ x ^ y;
    return z;
}
  
unsigned long long gcd(unsigned long long a,unsigned long long b){
    return b?gcd(b,a%b):a;
}
unsigned long long lcm(unsigned long long x,unsigned long long y){return (unsigned long long)x*y/gcd(x,y);}
  
int main(){
    ios::sync_with_stdio(false);
    int round;
    cin >> round;
    smg s;
    // s.debug();
    for (int r = 1; r <= round; r++)
    {
        s.clear();
        int n;
        cin >> n >> A >> B >> C;
        x = A;
        y = B;
        z = C;
        for (int i = 0; i < n; i++)
        {
            s.push(tang());
        }
        auto arr = s.getarr();
        unsigned long long ans = 0;
        for (int i = 0; i<arr.size(); i++)
        {
            for (int j = i + 1; j<arr.size(); j++){
                ans = max(ans, lcm(arr[i], arr[j]));
            }
        }
        cout << "Case #" << r << ": " << ans << endl;
    }
}
