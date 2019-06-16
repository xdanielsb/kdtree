import java.lang.Math;
import java.util.Vector;
import java.util.Comparator;
import java.util.Collections;

import java.util.*;

public class TestKDTree {
  private class Node{
    Integer id, d;
    Node l, r;
    Vector<Integer> p;
    public Node(Integer _id, Integer _d, Vector<Integer> _p){
      d = _d; id=_id; p =_p;
    }
  }
  public static class Cmp implements Comparator {
    Integer d;
    public Cmp(int _d){
        d = _d;
    }
    public int compare(Object o1, Object o2){
      Node x = (Node)o1, y = (Node)o2;
        return x.p.get(this.d)-y.p.get(this.d);
    }
  }
  private class KDTree{
    Vector< Vector<Integer> > pts;
    Integer n, dim;
    public KDTree( Integer n, Vector< Vector<Integer> > pts){
      this.n = n;
      this.pts = pts;
      this.dim = pts.size();
    }
    double dist( Vector<Integer> a , Vector<Integer>  b){
      double res =0.0;
      for( Integer i = 0; i < this.n; ++i){
        res +=Math.pow(a.get(i)-b.get(i),2);
      }
      return res;
    }
    Node build( Integer id, Integer l, Integer r, Integer d){
      Node root;
      if( l == r) return new Node( id, d, this.pts.get(l));
      Integer nd = (d+1)%dim, mid = r +(l-r)/2;
      Collections.sort(pts.subList(l, mid),new Cmp(d));
      root = new Node( id, d , this.pts.get(mid));
      root.l = build(id*2, l, mid-1, nd);
      root.r = build(id*2+1, r, mid+1, nd);
      return root;
    }
    void findNearest( Vector<Integer> to, Node root, Vector<Integer> res, double dis, Integer d  ){
        if( root == null ) return;
        double aux = dist( to, root.p);
        if( aux > 0 && dis > aux){
          res = root.p;
          dis = aux;
        }
        double delta = Math.pow( root.p.get(d) - to.get(d), 2.0);
        Integer nd = (d+1)%dim;
        if( to.get(d) > root.p.get(d)){
          findNearest( to, root.r, res, dis, nd);
          if( dis > delta)
            findNearest(to,root.l, res, dis, nd);
        }else{
          findNearest( to, root.l, res, dis, nd);
          if( dis > delta)
            findNearest(to,root.r, res, dis, nd);
        }
    }
  }
	public static void main(String[] args) {

	}
}
