class BebertSubmission():

    def run(self, s):
        dependencies = [line.split(" ") for line in s.splitlines()]
        dependencies = [(d[1], d[7]) for d in dependencies]
        print(dependencies)
        tasks = {}
        for before, after in dependencies:
            if before not in tasks:
                tasks[before] = []
                print('h')
            if after not in tasks:
                tasks[after] = []
                print('h')
            tasks[after].append(before)
        print(tasks['A'])
        tasks = sorted(tasks.items(), key=lambda t: t[0])
        print(tasks)
        done_ord = []
        done = set()
        while len(done) != len(tasks):
            for after, befores in tasks:
                if after not in done and all(t in done for t in befores):
                    done.add(after)
                    done_ord.append(after)
                    break

        return "".join(done_ord)

x = BebertSubmission()
print(x.run(open('day7.txt').read()))