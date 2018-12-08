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

int main() {
    std::string filename = "day7.txt";
    std::vector<std::string> lines = read_file_lines(filename);
    
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

    
    for (const auto& e : done_ord) {
        std::cout << e;
    }
    std::cout << "\n";
    
}

std::vector<std::string> read_file_lines(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    for( std::string line; getline( file, line ); )
    {
        lines.push_back(line);
    }
    
    return lines;
    
}