typedef long double lf;
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
    if( dis > delta)
      findNearest( to, root->l, res, dis, nd);
  }else{
    findNearest( to, root->l, res, dis, nd);
    if( dis > delta)
      findNearest( to, root->r, res, dis, nd);
  }
}
