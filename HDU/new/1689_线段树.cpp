#include <iostream>
#include <cstring>
#define ls l,m,rt<<1  
#define rs m+1,r,rt<<1|1  
#define maxn 100007
int Sum[maxn<<2],Add[maxn<<2];//Sum求和，Add为懒惰标记   

//PushUp函数更新节点信息 ，这里是求和  
void PushUp(int rt){Sum[rt]=Sum[rt<<1]+Sum[rt<<1|1];}  
//Build函数建树   
void Build(int l,int r,int rt){ //l,r表示当前节点区间，rt表示当前节点编号  
    if(l==r) {//若到达叶节点   
        Sum[rt]=1;//储存数组值   
        return;  
    }  
    int m=(l+r)>>1;  
    //左右递归   
    Build(l,m,rt<<1);  
    Build(m+1,r,rt<<1|1);  
    //更新信息   
    PushUp(rt);  
}  

void PushDown(int rt,int ln,int rn){  
    //ln,rn为左子树，右子树的数字数量。   
    if(Add[rt]){  
        //下推标记   
        Add[rt<<1]=Add[rt];  
        Add[rt<<1|1]=Add[rt];  
        //修改子节点的Sum使之与对应的Add相对应   
        Sum[rt<<1]=Add[rt]*ln;  
        Sum[rt<<1|1]=Add[rt]*rn;  
        //清除本节点标记   
        Add[rt]=0;  
    }  
}  

void Update(int L,int R,int C,int l,int r,int rt){//L,R表示操作区间，l,r表示当前节点区间，rt表示当前节点编号   
    if(L <= l && r <= R){//如果本区间完全在操作区间[L,R]以内   
        Sum[rt]=C*(r-l+1);//更新数字和，向上保持正确  
        Add[rt]=C;//增加Add标记，表示本区间的Sum正确，子区间的Sum仍需要根据Add的值来调整  
        return ;   
    }  
    int m=(l+r)>>1;  
    PushDown(rt,m-l+1,r-m);//下推标记  
    //这里判断左右子树跟[L,R]有无交集，有交集才递归   
    if(L <= m) Update(L,R,C,l,m,rt<<1);  
    if(R >  m) Update(L,R,C,m+1,r,rt<<1|1);   
    PushUp(rt);//更新本节点信息   
}


int main(int argc, char const *argv[])
{
    int round;
    int t = 1;
    scanf("%d", &round);
    while (round--)
    {
        int n, o;
        memset(Sum, 0, sizeof(Sum));
        memset(Add, 0, sizeof(Add));
        scanf("%d%d", &n, &o);
        Build(1, n, 1);
        while (o--)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            Update(a, b, c, 1, n, 1);
        }
        printf("Case %d: The total value of the hook is %d.\n",t++,Sum[1]);
    }
    return 0;
}


