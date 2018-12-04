import datetime
from collections import defaultdict, namedtuple, Counter
from re import match
gaurds = dict()

with open('day4.txt') as f:
    lines = f.read().strip().split('\n')
    records = []
    for line in lines:
        parsed = match(r'^(\[.+\]) (.+)$', line).groups()
        records.append(((datetime.datetime.strptime(parsed[0], '[%Y-%m-%d %H:%M]')), parsed[1]))
    records.sort(key=lambda x: x[0])

gaurds = defaultdict(Counter)
current_id = 0
time_slept = None

for record in records:
    time, text = record[0], record[1]
    if text == 'falls asleep':
        time_slept = time
    elif text == 'wakes up':
        while time_slept < time:
            gaurds[current_id][time_slept.minute] += 1
            time_slept += datetime.timedelta(minutes=1)
    else:
        current_id = int(match(r'^Guard #(\d+) begins shift$', text).group(1))

def part_one():
    id = max(gaurds, key=lambda x: sum(gaurds[x].values()))
    return max(gaurds[id], key=lambda x: gaurds[id][x]) * id
def part_two():
    id = max(gaurds, key=lambda x: max(gaurds[x].values()))
    return max(gaurds[id], key=lambda x: gaurds[id][x]) * id
    

print(part_one())
print(part_two())