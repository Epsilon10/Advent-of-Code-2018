# PART 1 
print(sum(int(x) for x in [line.rstrip('\n') for line in open('advent1.txt')]))

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
        

lines = [line for line in open('advent1.txt')]
cyc_lines = CyclicQueue(lines)
count = 0
sums_found = set()
found = False
while True:
    count += int(cyc_lines.get())
    if count in sums_found:
        print(count)
        break
    sums_found.add(count)
    
    

    

