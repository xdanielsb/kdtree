#!/bin/sh
if [ -z "$1" ]; then
      echo "Please write the number of points"
      exit 0;
fi
if [ -z "$2" ]; then
      echo "Please write the number of classes"
      exit 0;
fi
python rnd.py "$1" "$2" > in
g++ -DLOCAL -std=c++11 code.cpp && ./a.out < in
python plot.py "in" "lines" &
python digraph.py "nodes" "relations"
