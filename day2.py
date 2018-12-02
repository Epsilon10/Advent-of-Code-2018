ids = [line.rstrip('\n') for line in open('day2.txt')]

def first_part():
    times = []
    for id in ids:
        counts = dict((id.count(letter),letter) for letter in set(id))
        times.append((1 if counts.get(2) else 0, 1 if counts.get(3) else 0))
    return sum([x[0] for x in times]) * sum(x[1] for x in times)


def second_part():
    for x in ids:
        for y in ids:
            amt_diff = 0
            index_remove = 0
            for i,j in enumerate(x):
                if y[i] != j:
                    amt_diff += 1
                    index_remove = i
            if amt_diff == 1:
                return y[:index_remove] + y[index_remove + 1:]

print(first_part())
print(second_part())


