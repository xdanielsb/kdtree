/**
 *    author:  xdanielsb
 *    created: 04.2019       
**/
#include<bits/stdc++.h>
#define debug( x ) cout << #x << " = " << x ;
#define debug2( x, y) cout <<#x << " = " << x << " , " <<#y << " = " << y <<endl;
#define rep( a,b, c) for(__typeof(b) a = b; a <(c); a++)

#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;

int n, dim;
const int MAXD = 100;

struct pt{
  int x[ MAXD ];
  void show(){
    rep( i ,0, dim){
      if( i ) cout << "\t";
      printf("x[%d]=%d",i, x[i]);
    }
    cout <<endl;
  }
};
struct node{
  int d;
  node *l, *r;
  pt p;
  node(){
    r = l = nullptr;
  }
  node( int _d, pt &_p){
    d = _d; 
    p = _p;
    r = l = nullptr;
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
  void show(){
    for( pt a: pts) a.show();
  }
  node* build(int l, int r, int d){
    if( l >= r) {
      return new node( d, pts[l] );
    }
    sort( pts.begin()+l, pts.begin()+r, cmp( d ));
    int mid = ( l + r )/2;
    node *root = new node(d, pts[mid]);
    int nd = (d+1)%dim;
    root->l = build( l, mid, nd);
    root->r = build( mid+1, r, nd);
    return root;
  }
};

void bfs(node *root){
  queue < node* > q;
  int level = 0;
  if( root == nullptr) return;
  q.push( root);
  while(!q.empty()){
    int s = q.size();
    printf("level = %d, dim= %d\n", level, (level)%dim);
    rep( i, 0, s){
      node *t = q.front(); q.pop();
      if( t->l == nullptr && t->r == nullptr){
        t->p.show();
      }else{
        int dx = t->p.x[t->d];
        cout << "\t( > "<<dx<<")"<<endl<<endl;
        if(t->l!=nullptr) q.push( t->l);
        if(t->r!=nullptr) q.push( t->r);
      }
    }
    level++;
  }
}

int main(){
  #ifdef LOCAL
    freopen("in", "r",stdin);
  #endif
  cin >> n >> dim;
  kdtree T( n );
  sort( all( T.pts), cmp(0));
  T.show();

  node *root;
  root  = T.build( 0, n-1, 0 );
  bfs( root );

  
  return 0;
}
