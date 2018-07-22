//构建
while(q--){
    scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&val);
    cnt[x1][y1]+=val;
    cnt[x1][y2+1]-=val;
    cnt[x2+1][y1]-=val;
    cnt[x2+1][y2+1]+=val;
}

//恢复
for(int i=1;i<=n;i++)
   for(int j=1;j<=m;j++)
        cnt[i][j]+=cnt[i-1][j]+cnt[i][j-1]-cnt[i-1][j-1];
