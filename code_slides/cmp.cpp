struct cmp{
  int d;
  cmp( int _d): d(_d){};
  bool operator()( pt &a, pt &b) const {
    return a.x[d] < b.x[d];
  }
};
