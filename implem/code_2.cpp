/**
 *    author:  xdanielsb
 *    created: 04.2019
 *    desc: use when there are multiple classes
**/
#include<bits/stdc++.h>
#define PB push_back
#define F first
#define S second
#define rep( a,b, c) for(__typeof(b) a = b; a <(c); a++)
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;
typedef pair< int, int > ii;
typedef vector< int > vi;
int n, dim;
const int MAXD = 100;
vector < ii> partitions ;
map<int, string> infoNodes;
map<int, vi> relations;

struct pt{
  int x[ MAXD ];
  int cl; // class
  void show(){
    rep( i ,0, dim){
      if( i ) cout << "\t";
      printf("x[%d]=%d",i, x[i]);
    }
    cout <<endl;
  }
};
struct node{
  int id;
  int d;
  int cl;
  node *l, *r;
  pt p;
  node(){
    r = l = nullptr;
  }
  node(int _id, int _d, pt &_p){
    d = _d;
    id = _id;
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
string toString( int d){
  stringstream ss;
  ss << d;
  return ss.str();
}
void getInfo( node *root, node *father=nullptr ){
  if( root == nullptr) return;
  string info = "";
  if(root->l != nullptr || root->r!=nullptr){
    info = "> "+toString( root->p.x[root->d])+"  * ";
  }
  info.PB('[');
  rep( i, 0, dim){
    if( i > 0 )info.PB(',');
    info.append(toString(root->p.x[i]));
  }
  info.PB(']');
  infoNodes[root->id] = info;
  if( father!= nullptr){
    relations[father->id].PB( root->id );
  }
  getInfo( root->l, root);
  getInfo( root->r, root);
}

/*
 *  Complexity
 */
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
  node* build(int id, vector< pt> &A, int l, int r, int d){
    set< int > si;
    for( pt &c: A) si.insert( c.cl );
    node *root;
    if( si.size()== 1) {
      root = new node();
      root->cl = A[0].cl;
      return root;
    }

    int nd = (d+1)%dim;
    int mid = ( l + r ) >> 1;

    // storage partitions
    partitions.PB( {d, A[mid].x[d]});

    root = new node(id, d, A[mid]);
    vector< pt> L, R; // TODO:  not optimal, maybe nth-element?, why? creating copies
    rep(i, l, mid) L.PB( A[i] ) ;
    rep(i, mid+1, r+1) R.PB( A[i] );
    sort( all(L), cmp( nd ));
    sort( all(R), cmp( nd ));
    root->l = build(id*2, L, 0, L.size()-1, nd);
    root->r = build(id*2+1, R, 0, R.size()-1, nd);
    return root;
  }
};


int main(){
  cin >> n >> dim;
  partitions.clear();
  kdtree T( n );

  node *root;
  root  = T.build(1, T.pts, 0, n-1, 0 );

  /* Print partitions */
  ofstream lines ("lines");
  for( ii x: partitions){
    lines << x.F << " " << x.S <<endl;
  }
  lines.close();

  /* Get info graph */
  getInfo( root );
  ofstream nodes ("nodes");
  for( pair< int, string> c: infoNodes){
    nodes << c.F << " " << c.S <<endl;
  }
  nodes.close();
  ofstream rel("relations");
  for( pair< int, vi > r: relations){
    for( int x: r.S) rel << r.F << " " << x <<endl;
  }
  rel.close();

  return 0;
}
