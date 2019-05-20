/**
 *    author:  xdanielsb
 *    created: 04.2019
**/
struct pt{
  int x[ MAXD ];
  bool operator==( pt &c) const{
    rep(i ,0, dim) if (x[i]!=c.x[i]) return false;
    return true;
  }
};
