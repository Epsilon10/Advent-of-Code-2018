// 5 and 36
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <algorithm>
std::vector<std::string> read_file_lines(const std::string& filename);
std::string part_one(const std::map<char, std::vector<char> >& tasks);
int part_two(const std::map<char, std::vector<char> >& tasks);
int main() {
    const std::string filename = "day7.txt";
    const std::vector<std::string> lines = read_file_lines(filename);
    
    std::map<char, std::vector<char> > tasks;
    for (const std::string& line : lines) {
        char before = line.at(5);
        char after = line.at(36);
        if (tasks.find(before) == tasks.end()) {
            tasks.insert(std::pair<char, std::vector<char> >(before, std::vector<char>()));
        }
        if (tasks.find(after) == tasks.end()) {
            tasks.insert(std::pair<char, std::vector<char> >(after, std::vector<char>()));
        }
        tasks[after].push_back(before);
    }

    std::clock_t begin = clock();
    std::string p_1 = part_one(tasks);
    std::clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Part 1: " << p_1 << " took: " << elapsed_secs << " seconds. " << std::endl;
    begin = clock();
    int p_2 = part_two(tasks);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Part 2: " << p_2 << " took: " << elapsed_secs << " seconds. " << std::endl;
}

std::string part_one(const std::map<char, std::vector<char> >& tasks) {
    std::vector<char> done_ord;
    std::set<char> done;
    
    while (done.size() != tasks.size()) {
        for (const auto& [after, befores] : tasks) {
            if (std::find(done.begin(), done.end(), after) == done.end()) {
                bool to_add = true;
                for (const auto& t : befores) {
                    if (std::find(done.begin(), done.end(), t) == done.end()) {
                        to_add = false;
                        break;
                    }
                }
                if (to_add) {
                    done.insert(after);
                    done_ord.push_back(after);
                    break;
                }
            }
        }
    }

    std::string result(done_ord.begin(), done_ord.end());
    return result;
}

int part_two(const std::map<char, std::vector<char> >& tasks) {
    int cur_time = 0;
    std::set<char> done;
    std::map<char, int> current;

    while (done.size() != tasks.size()) {
        for (const auto& [after, befores] : tasks) {
            if (std::find(done.begin(), done.end(), after) == done.end() && current.find(after) == current.end()) {
                bool to_add = true;
                for (const auto& t : befores) {
                    if (std::find(done.begin(), done.end(), t) == done.end()) {
                        to_add = false;
                        break;
                    }
                }
                if (to_add) {
                    current[after] = 60 + int(after) - 64;
                    if (current.size() == 5)
                        break;
                }
            }
        }

        auto nxt_step_res = *std::min_element(current.begin(), current.end(),
                      [](decltype(current)::value_type& l, decltype(current)::value_type& r) -> bool { return l.second < r.second; });
        int nxt_step = nxt_step_res.second;
        cur_time += nxt_step;

        for (const auto& [task, val] : current) {
            current[task] -= nxt_step;
            if (current[task] == 0)
                done.insert(task);
        }

        for (const char& t : done) {
            if (current.find(t) != current.end()) 
                current.erase(t);
        }
    }

    return cur_time;

}

std::vector<std::string> read_file_lines(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    for( std::string line; getline( file, line ); )
        lines.push_back(line);
    
    return lines;
    
}