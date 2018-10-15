#方程的解个数是a中1中个数（二进制去掉所有0）的值再+1（因为有一个解为0）
t =int(input())
while t>0:
    t-=1;
    n=int(input())
    s=str(bin(n))
    cnt = 0
    for ch in s:
        if ch =='1':
            cnt+=1
    # print(s)
    ans = ''
    if cnt == 0:
        ans = '0'
    else:
       for i in range(0,cnt):
           ans += '1'
    print(int(ans,2)+1)
