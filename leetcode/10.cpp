//参照题解：考虑递归
bool isMatch(string s, string p) {
    if(p.empty())
        return s.empty();
    bool fir_match = (!s.empty() && (s[0] == p[0] || p[0] == '.'));
    if(p.length()>1&&p[1]=='*'){
        return isMatch(s, p.substr(2)) || (fir_match && isMatch(s.substr(1), p));
    }
    else{
        return fir_match && isMatch(s.substr(1), p.substr(1));
    }
}
