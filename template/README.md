## 到时候记得打印出来加到板子里面

### 一些注意事项：
1. dijkstra记得打vis标记，否则可能会有毒瘤出题人卡
2. 杜教的利用自然溢出计算两个long long相乘`(x*y-(ll)(((long double)x*y)/mod)*mod)%mod`，防止毒瘤出题人卡int128
