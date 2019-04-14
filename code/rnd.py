import random as rnd
import sys

num = int( sys.argv[1])
print("{} {}".format(num, 2))
for i in range( num):
  print("{} {}".format( rnd.randint(-100, 100), rnd.randint(-100,100))) 
