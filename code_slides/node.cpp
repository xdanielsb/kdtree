struct node{
  int id;
  int d;
  node *l, *r;
  pt p;
  node(){r = l = nullptr;}
  node(int _id, int _d, pt &_p){
    d = _d;
    id = _id;
    p = _p;
    r = l = nullptr;
  }
};
