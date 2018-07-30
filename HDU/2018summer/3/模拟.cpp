#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    int round;
    cin >> round;
    while (round--)
    {
        int x, y, z;
        cin >> x >> y >> z;
        int j = 2 * y;
        for (int i = j; i; i--)
        {
            for (int k = i; k; k--)
                printf(".");
            if (i % 2 == 0)
            {
                for (int k = 0; k < x; k++)
                {
                    printf("+-");
                }
                printf("+");
                for (int v = 0; v < z&&i<=j-2*z ;v++){
                    printf(".+");
                }
                if(i>j-2*z){
                    for (int p = 0; p < (j-i) / 2;p++)
                        printf(".+");
                }
            }
            else
            {
                for (int k = 0; k < x; k++)
                {
                    printf("/.");
                }
                printf("/");
                for (int v = 0; v < z&&i<=j-2*z; v++)
                {
                    printf("|/");
                }
                if(i>j-2*z){
                    for (int p = 0; p < (j-i) / 2;p++)
                        printf("|/");
                    printf("|");
                }
            }

            for (int k = 0;k<j-i-2*z;k++){
                printf(".");
            }
            printf("\n");
        }

        for (int i = 2 * z; i >= 0; i--)
        {
            if (i % 2 == 0)
            {
                for (int k = 0; k < x; k++)
                    printf("+-");
                if (i > j)
                {
                    for (int v = 0; v < y; v++)
                    {
                        printf("+.");
                    }
                    printf("+\n");
                }
                else
                {
                    for (int v = 0; v < i / 2; v++)
                    {
                        printf("+.");
                    }
                    printf("+");
                    for (int v = i / 2; v < y; v++)
                    {
                        printf("..");
                    }
                    printf("\n");
                }
            }
            else
            {
                for (int k = 0; k < x; k++)
                    printf("|.");
                if (i > j)
                {
                    for (int v = 0; v < y; v++)
                    {
                        printf("|/");
                    }
                    printf("|\n");
                }
                else
                {
                    for (int v = -1; v < i / 2; v++)
                    {
                        printf("|/");
                    }
                    printf(".");
                    for (int v = i / 2; v < y - 1; v++)
                    {
                        printf("..");
                    }
                    printf("\n");
                }
            }
        }
    }
}
