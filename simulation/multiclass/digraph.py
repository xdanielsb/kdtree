from graphviz import Digraph
import sys

__author__ = "Daniel Santos"
__repo__="github.com/xdanielsb/kdtree"
__license="GPL V3"
def create(showInfoNode=False):
    infoNodes = open(sys.argv[1], "r").read().split("\n")
    infoRelations = open(sys.argv[2], "r").read().split("\n")
    dot = Digraph(comment='The Round Table', format="eps")
    for info in infoNodes:
        if( len(info) == 0): continue
        sp = info.split()
        id = sp[0]
        pload = " ".join( sp[1:]).replace('*','\n')
        if( showInfoNode is False):
            pload = pload[:pload.find('\n')]
        dot.node( id, pload)
    for info in infoRelations:
        if( len(info) == 0): continue
        fr, to= info.split()
        dot.edge( fr, to)
    #print( dot.source )
    dot.render('test-output/tree', view=True)

if __name__ == "__main__":
    create();
