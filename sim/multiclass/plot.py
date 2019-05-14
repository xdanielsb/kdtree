#!/usr/bin/python

import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
__author__ = "xdanielsb"
__date__="April,2019"
x = np.arange(10)
ys = [i+x+(i*x)**2 for i in range(10)]
colors = cm.rainbow(np.linspace(0, 1, len(ys)))
def init():
    print( sys.argv )
    fp = open(sys.argv[1], "r").read().split("\n")
    fl = open(sys.argv[2], "r").read().split("\n")
    points = [[],[]]
    lines = [[],[]]
    colors_points =[]
    minx, maxx = float('inf'), -float('inf')
    miny, maxy = float('inf'), -float('inf')
    for l in fp[1:]:
        if( len(l) == 0):continue;
        x, y, cl = [ float(a) for a in l.split()]
        colors_points.append(colors[int(cl)-1])
        minx = min( x, minx)
        miny = min( y, miny)
        maxx = max( x, maxx)
        maxy = max( y, maxy)
        points[0].append( x);
        points[1].append(y);

    minx -= 1
    miny -= 1
    maxx += 1
    maxy += 1
    for l in fl:
        if( len(l) == 0):continue;
        x, y = [ int(a) for a in l.split()]
        lines[0].append( x);
        lines[1].append(y)

    plt.scatter(points[0], points[1], c=colors_points)
    for i in range(len( lines[0])):
        color= lines[0][i]
        pos = lines[1][i]
        if( color == 0 ):
            plt.plot([pos, pos], [miny, maxy], 'b-')
        else:
            plt.plot([minx, maxx], [pos, pos], 'r-')
        plt.pause(0.5)
    plt.show()



if __name__ =="__main__":
    init();
