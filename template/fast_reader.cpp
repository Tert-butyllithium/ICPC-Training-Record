// 适用于cin的快读
struct ioos
{
    inline char gc()
    {
        static const int IN_LEN = 1 << 18 | 1;
        static char buf[IN_LEN], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)), s == t ? -1 : *s++;
    }

    template <typename _Tp>
    inline ioos &operator>>(_Tp &x)
    {
        static char ch, sgn;
        ch = gc(), sgn = 0;
        for (; !isdigit(ch); ch = gc())
        {
            if (ch == -1)
                return *this;
            sgn |= ch == '-';
        }
        for (x = 0; isdigit(ch); ch = gc())
            x = x * 10 + (ch ^ '0');
        sgn && (x = -x);
        return *this;
    }
} io;
