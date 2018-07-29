//https://blog.csdn.net/theArcticOcean/article/details/50563963
#include <bits/stdc++.h>

using namespace std;
const double eps = 1e-7, pi = acos(-1);
const int maxn = 1005;
struct point
{
    double x,y;
};
point points[maxn], convex[maxn];

double cross(point p0,point p1,point p2){
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

inline double sq(double x) { return x * x; }

double dis(point a,point b){
    return sqrt(sq(a.x - b.x) + sq(a.y - b.y));
}

bool cmp1(point p1,point p2){
    return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

bool cmp2(point p1,point p2){
    double c1 = cross(points[0], p1, p2);
    if(c1==0){
        return dis(p1, points[0]) < dis(p2, points[0]);
    }
    return c1 > 0;
}

int top;
void solve(int n){
    top = 0;
    sort(points, points + n, cmp1);
    sort(points + 1, points + n, cmp2);
    convex[top++] = points[0];
    convex[top++] = points[1];
    for (int i = 2; i < n;i++){
        if(cross(convex[top-2],convex[top-1],points[i])>0)
            convex[top++] = points[i];
        else{
            top--;
            while (top >= 2&&cross(convex[top-2],convex[top-1],points[i])<=0)
                top--;
            convex[top++] = points[i];
        }
    }
    convex[top++] = points[0];
}
