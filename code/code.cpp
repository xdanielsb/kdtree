/**
 *    author:  xdanielsb
 *    created: 04.2019       
**/
#include<bits/stdc++.h>
#define PB push_back
#define debug1( x ) cout << #x << " = " << x  <<endl;
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
    sort( all(pts), cmp(0));
  }
  void show(){
    for( pt a: pts) a.show();
  }
  node* build(vector< pt> &A, int l, int r, int d){
    /* for( pt c: A) c.show(); cout <<endl; */
    if( l >= r) {
      return new node( d, A[0] );
    }
    int nd = (d+1)%dim;
    int mid = ( l + r )/2;
    node *root;
    if( A.size()==2){
      if( A[0].x[nd] > A[1].x[nd] ){
        root = new node(nd, A[0]);
        root->l = new node( nd, A[1]);
      }else{
        root = new node(nd, A[0]);
        root->r = new node( nd, A[1]);
      }
      return root;
    }else{
      root = new node(d, A[mid]);
    }
    vector< pt> L, R;
    cout << d << " " << A[mid].x[ d ] <<endl;
    for( int i= l; i <=mid; i++) L.PB( A[i]);
    for( int j= mid+1; j <=r; j++) R.PB( A[j]);
    sort( L.begin(), L.end(), cmp( nd ));
    sort( R.begin(), R.end(), cmp( nd ));
    root->l = build( L, 0, L.size()-1, nd); 
    root->r = build( R, 0, R.size()-1, nd);
    return root;
  }
};

void drawTree(node *root){
  queue < node* > q;
  int level = 0;
  if( root == nullptr) return;
  q.push( root);
  while(!q.empty()){
    int s = q.size();
    /* printf("level = %d, dim= %d\n", level, (level)%dim); */
    rep( i, 0, s){
      node *t = q.front(); q.pop();
      if( t->l == nullptr && t->r == nullptr){
        /* t->p.show(); */
      }else{
        int dx = t->p.x[t->d];
        cout << (level%dim) << " " << dx <<endl;
        /* cout << "\t( > "<<dx<<")"<<endl<<endl; */
        if(t->l!=nullptr) q.push( t->l);
        if(t->r!=nullptr) q.push( t->r);
      }
    }
    level++;
  }
}

int main(){
  cin >> n >> dim;
  kdtree T( n );

  node *root;
  root  = T.build( T.pts, 0, n-1, 0 );
  /* bfs( root ); */

  
  return 0;
}
