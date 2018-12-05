import string
from collections import defaultdict

substrs = [(x + y, y + x) for x, y in zip(list(string.ascii_uppercase), list(string.ascii_lowercase))]

def part_one(target):

    index = 0
    while index < len(substrs):
        if substrs[index][0] in target or substrs[index][1] in target:
            target = target.replace(substrs[index][0], '')
            target = target.replace(substrs[index][1], '')
            index = 0
        else:
            index += 1
    return len(target)

def part_two(target):
    lengths = defaultdict(int)
    for x, y in substrs:
        lengths[x + y] = part_one(target.replace(x[0], '').replace(x[1], ''))
    return lengths[min(lengths, key=lambda x: lengths[x])]

target = open('day5.txt').read()
print(part_two(target))