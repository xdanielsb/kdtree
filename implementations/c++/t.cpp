/**
 *    author:  xdanielsb
 *    created: 04.2019
 *    last modified: 06.2019
**/
#include<bits/stdc++.h>
#define rep( a,b, c) for(__typeof(b) a = b; a <(c); a++)
using namespace std;
typedef double lf;
// global,
int n, dim;
const int MAXD = 100;
struct pt{
  int x[ MAXD ];
  bool operator==( pt &c) const{
    rep(i ,0, dim) if (x[i]!=c.x[i]) return false;
    return true;
  }
};
struct node{
  int id, d;
  node *l, *r;
  pt p;
  node(){ r = l = nullptr;}
  node(int _id, int _d, pt &_p){
    d = _d, id = _id, p = _p, r = l = nullptr;
  }
};
struct cmp{
  int d;
  cmp( int _d): d(_d){};
  bool operator()( pt &a, pt &b) const {
    return a.x[d] < b.x[d];
  }
};

struct kdtree{
  vector< pt > pts;
  int n;
  kdtree(int _n ): pts( _n ), n( _n ){
    rep( i, 0, n) rep(j, 0, dim) cin >> pts[ i ].x[ j ];
  }
  lf dist( pt &a, pt &b, lf res=.0){
   rep( i, 0, dim) res += pow( a.x[i]-b.x[i], 2.0);
   return res;
  }
  node* build(int id,  int l, int r, int d){
    node *root;
    if( l >= r)
      return new node(id, d, pts[l] );
    int nd = (d+1)%dim, mid = r + (l-r)/2;
    nth_element(pts.begin()+l, pts.begin()+mid,pts.begin()+r+1, cmp(d));
    root = new node(id, d, pts[mid]);
    root->l = build(id*2,l, mid-1, nd);
    root->r = build(id*2+1, mid+1, r, nd);
    return root;
  }
  void findNearest( pt &to, node *root,  pt &res, lf &dis, int d=0){
    if( root == nullptr) return;
    lf aux = dist( to, root->p );
    if( aux > 0 && dis > aux ) {
      res = root->p;
      dis = aux;
    }
    lf delta = pow(root->p.x[d] - to.x[d], 2.0);
    int nd = (d+1)%dim;
    if(to.x[d] > root->p.x[d] ){
      findNearest( to, root->r, res, dis, nd);
      if( dis > delta) findNearest( to, root->l, res, dis, nd);
    }else{
      findNearest( to, root->l, res, dis, nd);
      if( dis > delta) findNearest( to, root->r, res, dis, nd);
    }
  }
};

int main(){

  return 0;
}
