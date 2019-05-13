/**
 *    author:  xdanielsb
 *    created: 04.2019
**/
#include<bits/stdc++.h>
#define PB push_back
#define F first
#define S second
#define rep( a,b, c) for(__typeof(b) a = b; a <(c); a++)
#define debug( x ) cout << #x << " = " << x <<endl;
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;
typedef pair< int, int > ii;
typedef vector< int > vi;
typedef long double lf;
const int oo = INT_MAX  ;
int n, dim;
const int MAXD = 100;
vector < ii> partitions ;
map<int, string> infoNodes;
map<int, vi> relations;

// class is the value in x[dim]
struct pt{
  int x[ MAXD ];
  void show(){
    rep( i ,0, dim){
      if( i ) cout << "\t";
      printf("x[%d]=%d",i, x[i]);
    }
    printf(", class = %d", x[dim]);
    cout <<endl;
  }
  bool operator==( pt &c) const{
    return c.x[dim] == x[dim];
  }
};
struct node{
  int id;
  int d;
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

// utilities
lf dist( pt &a, pt &b){
 lf res = .0;
 rep( i, 0, dim) res += pow( a.x[i]-b.x[i], 2.0);
 return res;
}
unsigned int getRnd( int n){
    static unsigned int seed = 5323;
    seed = 8253729 * seed + 2396403;
    return seed  % n;
}

struct kdtree{
  vector< pt > pts;
  int n;
  kdtree(int _n ): pts( _n ), n( _n ){
    rep( i, 0, n) {rep(j, 0, dim) {
      cin >> pts[ i ].x[ j ];
    }
    cin >> pts[ i ].x[dim];
    }
  }
  void show(){
    for( pt a: pts) a.show();
  }
  node* build(int id,  int l, int r, int d){

    node *root;
    if( l >= r){
      cout << l <<  "  " << r <<endl;
      return new node(id, d, pts[l] );
    }
    int nd = (d+1)%dim;
    int mid = r + (l-r)/2;
    nth_element(pts.begin()+l, pts.begin()+mid,pts.begin()+r+1, cmp(d));
    int flag = pts[l].x[dim];
    rep(i, l+1, r+1){
      if( pts[i].x[dim]!= flag) {
        flag = -1; break;
      }
    }
  /*  if( flag!=-1 ){
      cout << l <<  "  " << r <<endl;
      return  new node(id, d, pts[mid] );
    }*/
    // storage partitions
    partitions.PB( {d, pts[mid].x[d]});
    root = new node(id, d, pts[mid]);
    root->l = build(id*2,l, mid-1, d^1);
    root->r = build(id*2+1, mid+1, r, d^1);
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

bool check( vector< pt > &T, pt to, pt ans, lf dans){
  pt aux;
  lf dis = oo;
  for( pt &a: T){
    lf d = dist( to, a);
    if( d > 0 && dis > d){
      dis = d;
      aux = a;
    }
  }
  bool ok =  aux ==  ans || dis == dans;
  if(!ok){
    cout << endl;
    to.show();
    aux.show();
    ans.show();
  }
  return ok;
}

int main(){
  cin >> n >> dim;
  partitions.clear();
  kdtree T( n );

  node *root;
  root  = T.build(1, 0, n-1, 0 );

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


  // find nearest of three random points
  set< int > rnd; int tot =n/2;
  while( rnd.size() <= tot){
    rnd.insert( getRnd(n));
  }
  int count = 0;
  for( int el: rnd){
    lf dis = oo;
    pt res;
    T.findNearest(T.pts[el], root, res, dis);

    count+= check(T.pts, T.pts[el], res, dis);
  }
  cout << "The software has passed "<< count << " Cases over " << rnd.size() << " Cases "<<endl;

  return 0;
}
