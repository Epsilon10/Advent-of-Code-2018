from utils import timed
# PART 1
@timed 
def first_part():
    return sum(int(x) for x in [line.rstrip('\n') for line in open('day1.txt')])

# PART 2
class CyclicQueue():
    def __init__(self, items):
        self.items = items
        self.index = 0
    def next(self):
        if self.index < len(self.items) - 1:
            self.index+=1
        else:
            self.index = 0
    def get(self):
        to_ret = self.items[self.index]
        self.next()
        return to_ret
        
@timed
def second_part():
    lines = [line for line in open('day1.txt')]
    cyc_lines = CyclicQueue(lines)
    count = 0
    sums_found = set()
    while True:
        count += int(cyc_lines.get())
        if count in sums_found:
            return count
        sums_found.add(count)

print(second_part())
    

    

