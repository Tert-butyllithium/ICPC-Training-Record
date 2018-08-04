std::ostream& operator<<(std::ostream& os, __int128 t) {
    if (t==0) return os << "0";
    if (t<0) {
        os<<"-";
        t=-t;
    }
    int a[50],ai=0;
    memset(a,0,sizeof a);
    while (t!=0){
        a[ai++]=t%10;
        t/=10;
    }
    for (int i=1;i<=ai;i++) os<<abs(a[ai-i]);
    return os<<"";
}
 
std::ostream& operator<<(std::ostream& os, __int128 T) {//极简版王铭轩专用
    if (T<0) os<<"-";if (T>=10 ) os<<T/10;if (T<=-10) os<<-（T/10）;
    return os<<( (int) (T%10) >0 ? (int) (T%10) : -(int) (T%10) ) ;
}
