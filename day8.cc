#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
int part_one(std::stringstream& to_parse);
int part_two(std::stringstream& to_parse);

std::stringstream read_file_string(const std::string& filename);

int main() {
    std::string filename = "day8.txt";
    std::stringstream str1 = read_file_string(filename);
    std::clock_t begin = clock();
    int p_1 = part_one(str1);
    std::clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Part 1: " << p_1 << " took: " << elapsed_secs << " seconds. " << std::endl;

    // jank to read it twice but im lazy
    std::stringstream str2 = read_file_string(filename);
    begin = clock();
    int p_2 = part_two(str2);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Part 2: " << p_2 << " took: " << elapsed_secs << " seconds. " << std::endl;
}

int part_one(std::stringstream& to_parse) {
    int x; // number of nodes
    int y; // amount of metadata
    int sum = 0;
    to_parse >> x;
    to_parse >> y;

    for (int i = 0; i < x; i++) {
        sum += part_one(to_parse);
    }

    for (int i = 0; i < y; i++) {
        int nxt;
        if (to_parse >> nxt) 
            sum += nxt;
    }
 
    return sum;
}

int part_two(std::stringstream& to_parse) {
    int x; // number of nodes
    int y; // amount of metadata
    to_parse >> x;
    to_parse >> y;
    if (x == 0) {
        int total = 0;
        for (int i = 0; i < y; i++) {
            int nxt;
            to_parse >> nxt;
            total += nxt;
        }
        return total;
    } 
    std::vector<int> node_values(x);
    for (int i = 0; i < x; i++) 
        node_values[i] = part_two(to_parse); // recurse until we have a node with no more child nodes
    int total = 0;
    for (int i = 0; i < y; i++) {
        int index;
        to_parse >> index;
        if (index > 0 && index <= x) 
            total += node_values[index - 1];
    }
    return total;

}


std::stringstream read_file_string(const std::string& filename) {
    std::ifstream input("day8.txt");
    std::stringstream buffer;
    buffer << input.rdbuf();
    return buffer;
}