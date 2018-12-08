from collections import namedtuple, defaultdict
import numpy as np
from itertools import product
from utils import timed
def manhatten_dist(p1, p2):
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])

def to_array():
    data = []
    for line in open('day6.txt'):
        data.append(line.strip().split(', '))
    return np.array(data, dtype=int)
coords = to_array()

x_min = coords[:,0].min()
y_min = coords[:,1].min()
x_max = coords[:,0].max()
y_max = coords[:,1].max()

@timed
def part_one():
    counter = [0]*len(coords)
    for x in range(x_min, x_max+1):
        for y in range(y_min, y_max+1):
            dists = np.array([manhatten_dist((c[0], c[1]), (x,y)) for c in coords])
            mindist = np.sum(dists == dists.min())
            if mindist > 1:
                continue
            counter[int(np.argmin(dists))] += 1 if not( x == x_min or y == y_min or x == x_max or y == y_max) else 1e6
    counter = np.array(counter, dtype=int)
    return counter[counter<1e6].max()

@timed
def part_two():
    area = 0
    for x in range(x_min, x_max+1):
        for y in range(y_min, y_max+1):
            dists = np.array([manhatten_dist((c[0], c[1]), (x,y)) for c in coords])
            if dists.sum() < 10000:
                area += 1
    return area
print(part_one())
print(part_two())