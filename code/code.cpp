/**
 *    author:  xdanielsb
 *    created: 04.2019       
**/
#include<bits/stdc++.h>
#define debug( x ) cout << #x << " = " << x ;
#define rep( a,b, c) for(__typeof(b) a = b; a <(c); a++)
using namespace std;
using ll = long long;

int n, dim;
const int MAXD = 100;

struct pt{
  ll x[ MAXD ];
  void show(){
    rep( i ,0, dim){
      if( i ) cout << "\t"; debug( x[i] );
    }
    cout <<endl;
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
};

int main(){
  #ifdef LOCAL
    freopen("in", "r",stdin);
  #endif
  cin >> n >> dim;
  kdtree T( n );

  T.show();

  
  return 0;
}
