python rnd.py "$1" > in
g++ -DLOCAL -std=c++11 code.cpp && ./a.out < in  > lines
python plot.py "in" "lines"
