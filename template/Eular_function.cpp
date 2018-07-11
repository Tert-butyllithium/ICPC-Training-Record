#include<iostream>  
#include<cstdio>  
#define N 40000  
using namespace std;  
int n;  
int phi[N+10],prime[N+10],tot,ans;  
bool mark[N+10];  
void getphi()  
{  
   int i,j;  
   phi[1]=1;  
   for(i=2;i<=N;i++)//相当于分解质因式的逆过程  
   {  
       if(!mark[i])  
           {  
             prime[++tot]=i;//筛素数的时候首先会判断i是否是素数。  
             phi[i]=i-1;//当 i 是素数时 phi[i]=i-1  
             }  
       for(j=1;j<=tot;j++)  
       {  
          if(i*prime[j]>N)  break;  
          mark[i*prime[j]]=1;//确定i*prime[j]不是素数  
          if(i%prime[j]==0)//接着我们会看prime[j]是否是i的约数  
          {  
             phi[i*prime[j]]=phi[i]*prime[j];break;  
          }  
          else  phi[i*prime[j]]=phi[i]*(prime[j]-1);//其实这里prime[j]-1就是phi[prime[j]]，利用了欧拉函数的积性  
       }  
   }  
}  
int main()  
{  
    getphi();  
}