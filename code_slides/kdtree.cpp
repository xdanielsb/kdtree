struct kdtree{
  vector< pt > pts;
  int n;
  kdtree(int _n ): pts( _n ), n( _n ){
    rep( i, 0, n)
      rep(j, 0, dim)
         // read  pts[ i ].x[ j ];
  }
  node* build(int id,  int l, int r, int d){
  }
  void findNearest( pt &to, node *root,
                    pt &res, lf &dis, int d=0){
  }
};
