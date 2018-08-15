void Matrix(int (&a)[2][2],int b[2][2]){   //矩阵乘法
    int tmp[2][2] = {0};
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 2; ++j)
            for(int k = 0; k < 2; ++k)
                tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j]) % N;  //矩阵相乘，注意mod
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 2; ++j)  
            a[i][j] = tmp[i][j]; //赋值返回数据
}

作者：徐森威
链接：https://www.jianshu.com/p/1c3f88f63dec
來源：简书
简书著作权归作者所有，任何形式的转载都请联系作者获得授权并注明出处。
