+//主要是离线做

#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<map>
#include<unordered_map>
#include<string>
#define type unordered_map<string,int>::value_type
using namespace std;
unordered_map<string,int> mp1,mp2;
const int maxn = 1e5 +10;
int solved[1010];
bool tp[1010];
char cas1[maxn][22],cas2[maxn][82];

int main()
{
    char temp[200];
    temp[0] = 0;
    int cnt = 0,i,j;
    fgets(temp,105,stdin);
    while(temp[0] != '@')
    {
        for(i=1;temp[i]!=']';i++)
            cas1[cnt][i-1] = temp[i];
        ++i;
        for(++i,j=0;temp[i] && temp[i]!='\n';i++,j++)
            cas2[cnt][j] = temp[i];
        ++cnt;
        fgets(temp,105,stdin);
    }
    int n;
    scanf("%d\n",&n);
    string tmp;
    for(i=1;i<=n;i++)
    {
        solved[i] = -1;
        fgets(temp,105,stdin);
        if(temp[0] == '[')
        {
            temp[strlen(temp) - 1] = 0;
            temp[strlen(temp) - 1] = 0;
            mp1.insert(type(temp + 1,i));
            tp[i] = 1;
        }
        else
        {
            temp[strlen(temp) - 1] = 0;
            //std::cout<<tmp<<std::endl;
            mp2.insert(type(temp ,i));
        }
    }
    for(i=0;i<cnt;i++)
    {
        tmp = cas1[i];
        //std::cout<<tmp<<std::endl;
        unordered_map<string,int>::iterator itr = mp1.find(tmp);
        if(itr != mp1.end())
        {
            solved[itr ->second] = i;
        }
        tmp =  cas2[i];
        //std::cout<<tmp<<std::endl;
        itr = mp2.find(tmp);
        if(itr != mp2.end())
            solved[itr -> second] = i;
    }
    for(i = 1;i<=n;i++)
    {
        if(solved[i] != -1)
        {
            if(tp[i])
                printf("%s\n",cas2[solved[i]]);
            else
                printf("%s\n",cas1[solved[i]]);
        }
        else
            printf("what?\n");
    }
    return 0;
}
