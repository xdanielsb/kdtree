/*
 * author: xdanielsb
 */
#include <bits/stdc++.h>
#define endl '\n'
#define debug1( x ) cout << #x << " = " <<  x << endl;
#define debug2( x, y) cout <<#x << " = " << x << " , " <<#y << " = " << y <<endl;
#define F first
#define S second
#define PB push_back
#define size( x )   int( ( x ).size( ) )
#define endl '\n'
#define rep(i, a, b) for( __typeof(a) i =(a); i<(b);i++)

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
const int MAXN = 1e5 + 17;
struct pt{
  int x[2];
};

pt point[MAXN], cop[MAXN];
const ll inf = LONG_MAX;

struct node{
   int d, val;
   pt p;
   node *l, *r;
   node(){}
   node(int _d){
    d = _d;
   }
};

bool cmp1( const pt &a , const pt &b){
  return a.x[0] < b.x[0];
}
bool cmp2( const pt &a, const pt &b){
  return a.x[1] < b.x[1];
}
ll dist( const pt &a, const pt &b){
  auto pow2= [](int x1) {return x1*1ll*x1;};
  ll ans=.0;
  rep( i,0, 2) ans += pow2( a.x[i]-b.x[i]);
  return ans;
}

node* build(int l, int r, int d){
  if( l > r) return nullptr;
  node *n =  new node(d);
  if( l == r ){
    n->p = point[l];
    n->l = nullptr;
    n->r = nullptr;
    return n;
  }
  int mid = ( l + r  ) / 2;
  nth_element( point +l, point+mid,  point+r+1, d ? cmp2: cmp1);
  n->p = point[mid];
  n->val = point[mid].x[d];
  n->l = build( l, mid-1, d^1);
  n->r = build( mid+1, r, d^1);
  return n;
}
void findNearest(  node *root, pt &to, ll &ans){
  if( root == nullptr) return;
  ll dis = dist( root->p, to);
  if( dis >0 && dis<ans){
    ans = dis;
  }
  ll delta = (to.x[root->d]-root->val);
  delta = delta*1ll*delta;
  if( to.x[root->d] > root->val){
    findNearest( root->r, to, ans);
    if(  ans >= delta ) findNearest( root->l, to, ans);
  }else{
    findNearest( root->l, to, ans);
    if(  ans >= delta) findNearest( root->r, to , ans);
  }
}

int main(){
  ios::sync_with_stdio( false );
  cin.tie( nullptr );
#ifdef LOCAL
  freopen("in", "r" , stdin);
#endif
  int t,n; cin >>t;
  while( t--){
    cin >>n;
    rep(i, 0, n) {
      cin >> point[i].x[0] >>point[i].x[1];
      cop[i] = point[i];
    }
    node *root = build( 0, n-1, 0);
    rep( i, 0, n){
      ll ans= inf;
      findNearest(root, cop[i], ans);
      cout<< ans <<endl;
    }
  }
  return 0;
}
