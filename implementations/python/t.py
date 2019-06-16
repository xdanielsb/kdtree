__author__="xdanielsb"
__date__="06.2019"


import math

class node:
    def __init__(self, id, d):
        self.id = id
        self.d = d
        self.l = None
        self.r = None
        self.p = []

class kdtree:
    def __init__(self, pts):
        self.pts = pts
        self.n = len(pts)
        self.dim = len(pts[0])
    def dist(self, nodea, nodeb):
        res = 0.0
        for i in range(0, self.dim):
            res += (nodea.p[i] - nodeb.p[i]) ** 2
        return res
    def build(id, l, r, d):
        if( l == r ): return node(id, d, self.pts[l])
        nd = (d+1)%self.dim
        mid = r +(l-r)/2
        sorted(pts[l:mid+1], key = lambda x: x[d])
        root = node(id, d,pts[mid])
        root.l = build( id*2, l, mid-1, nd)
        root.r = build( id*2+1, mid+1, r, nd)
        return root
    def findNearest( to, root, res, dis, d=0 ):
        if( root == None): return
        aux = self.dist(to, root.p)
        if( aux > 0 and dis > aux):
            res = root.p
            dis = aux
        delta = ( root.p[d] - to.p[d] ) ** 2
        nd = ( d+1 ) % self.dim
        if( to.p[d] > root.p[d]):
            findNearest(to, root.r, res, dis, nd)
            if( dis > delta):
                findNearest( to, root.l, res, nd)
        else:
            findNearest(to, root.l, res, dis, nd)
            if( dis > delta):
                findNearest( to, root.r, res, nd)
