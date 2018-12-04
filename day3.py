import re
from collections import defaultdict

data = [i for i in open('day3.txt').read().split('\n')]

coords = defaultdict(set)

class Claim():
    def __init__(self, id, start_x, start_y, width, height):
        self.id = id
        self.start_x = start_x
        self.start_y = start_y
        self.width = width
        self.height = height
        self.marked = False
    


def part_one():
    for claim in data:
        parsed = re.findall(r'-?\d+', claim)
        start_x = int(parsed[1])
        start_y = int(parsed[2])
        width = int(parsed[3])
        height = int(parsed[4])
        for i in range(start_y, start_y + height):
            for j in range(start_x, start_x + width):
                coords[(j,i)].add(claim)
    return len([x for x,y in coords.items() if len(y) > 1])
print(part_one())

def part_two():
    claims = []
    for line in data:
        parsed = re.findall(r'-?\d+', line)
        claims.append(Claim(*[int(x) for x in parsed]))
    for claim in claims:
        for i in range(claim.start_y, claim.start_y + claim.height):
            for j in range(claim.start_x, claim.start_x + claim.width):
                coords[(j,i)].add(claim)
                if len(coords[(j,i)]) > 1:
                    for c in coords[(j,i)]:
                        c.marked = True
    for x in claims:
        if x.marked == False:
            print(x.id)

print(part_two())