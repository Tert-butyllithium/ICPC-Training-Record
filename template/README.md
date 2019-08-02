## 到时候记得打印出来加到板子里面

### 一些注意事项：
1. dijkstra记得打vis标记，否则可能会有毒瘤出题人卡
2. 杜教的利用自然溢出计算两个long long相乘`(x*y-(ll)(((long double)x*y)/mod)*mod)%mod`，防止毒瘤出题人卡int128
3. dinic 的dist是最后一次增广到S的距离。如果某个点的距离到S存在（即在bfs过程中被访问过）那么这个点在割集的S集中，否则在T集中.
   输出最大独立集：
   ```c++
   for(int i=0;i<n;i++){
        if(DC.d[i]){
            if(source[a[i]]){
                cout<<a[i]<<" ";
            }
        }
        else{
            if(!source[a[i]]){
                cout<<a[i]<<" ";
            }
        }
    }
   ```
