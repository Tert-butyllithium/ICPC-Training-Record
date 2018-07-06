//简单的模拟，注意double不能瞎几把==!
#include <iostream>
double H, U, D, F;
double reduce;
int newday(double &height,double& yesterday){
    height += yesterday;
    yesterday -= reduce;
    if(height>H)
        return 1;
    height -= D;
    if(height<0)
        return -1;
    return 0;
}

int main(int argc, char const *argv[])
{
    while(scanf("%lf%lf%lf%lf",&H,&U,&D,&F)&&H){
        reduce = F * U / 100.0 ;
        int res;
        double height = 0;
        double day = U;
        int i = 0;
        do{
            i++;
            res = newday(height, day);
        } while (res==0);
        printf("%s on day %d\n", res > 0 ? "success" : "failure", i);
    }
    return 0;
}


