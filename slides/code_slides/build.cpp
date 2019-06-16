node* build(int id,  int l, int r, int d){
  node *root;
  if( l == r) return new node(id, d, pts[l]);
  int nd = (d+1)%dim;
  int mid = r + ( l - r )/2;
  sort(pts.begin()+l,pts.begin()+r+1, cmp(d));
  root = new node(id, d, pts[mid]);
  root->l = build(id*2,l, mid-1, nd);
  root->r = build(id*2+1, mid+1, r, nd);
  return root;
}
