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
#define rept(i, a, b) for( __typeof(a) i =(a); i<=(b);i++)
#define all(x) x.begin(),x.end()

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef long double ld;
typedef pair<ld, ld> ii;
// with sweep line
ld closestPair( vector< ii > &A, int n){
  sort(all(A));
  ld best = 10000;
  int left = 0;
  set < ii > box;
  rep( i, 0, n){
    rep( j, i+1, n){
      if( A[i].F + best <  A[j].F){
        break;
      }
      best = min(best, hypot( A[i].F-A[j].F, A[i].S-A[j].S));
    }
  }
  return best;
}

int main(){
  ios::sync_with_stdio( false );
  cin.tie( nullptr );
#ifdef LOCAL
  freopen("in", "r" , stdin);
#endif
 
  int n;
  while( cin >> n && n ){
    vector< ii > A(n);
    rep( i,0 , n) cin >>A[i].F >> A[i].S;
    ld ans = closestPair( A, n);
    if( 10000.0-ans < 1e-9 ){
      cout << "INFINITY" <<endl;
    }else{
      cout <<setprecision(4)<< fixed;
      cout << ans <<endl;
    }
  }
  return 0;
}
