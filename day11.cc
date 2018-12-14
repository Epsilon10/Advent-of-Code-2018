#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include <tuple>
#include <climits>
#include <algorithm>
using Point = std::pair<uint32_t, uint32_t>;


Point part_one(const uint32_t serial); 
uint32_t part_two(const uint32_t serial);

int main() {
    const uint32_t serial = 18; // test case
    auto ans = part_one(serial);
    std::cout << "x: " << ans.first + 1 << " y: " << ans.second + 1 << std::endl; // we need to add one because we returned the corresponding indexes which start at 0 not 1
    auto ans2 = part_two(serial);
    std::cout << ans2;
}

uint32_t calc_power(Point& point, const uint32_t serial);
Point part_one(const uint32_t serial) {
    int grid[300][300] = {0};   

    for (int y = 0; y < 300; y++) {
        for (int x = 0; x<300; x++) {
            Point point = Point(x, y);
            grid[y][x] = calc_power(point, serial);
        }
    }

    std::map<Point, int> powers;

    for (int y = 0; y < 298; y++) {
        for (int x = 0; x < 298; x++) {
            const uint32_t matrix_power = grid[y][x] + grid[y][x + 1] + grid[y][x + 2] + grid[y + 1][x] + grid[y + 1][x + 1]
                + grid[y + 1][x + 2] + grid[y + 2][x] + grid[y + 2][x + 1] + grid[y + 2][x + 2];
            powers.insert(std::pair<Point, int> (Point(x, y), matrix_power));
        }
    }

    auto res = *std::max_element(powers.begin(), powers.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });
    return res.first;

}

uint32_t part_two(const uint32_t serial) {
    int max_power = -1 * 99999999;
    int max_x, max_y = 0;

    int grid[300][300] = { 0 };
    for (int y = 0; y < 300; y++) {
        for (int x = 0; x<300; x++) {
            Point point = Point(x, y);
            grid[y][x] = calc_power(point, serial);
        }
    }
    for (int y = 0; y < 298; y++) {
        for (int x = 0; x < 298; x++) {
            uint32_t matrix_power = 0;
            for (int i = x; i < 300; i++) {
                
            }
        }
    }

    return max_x;
}


uint32_t calc_power(Point& point, const uint32_t serial) {
    point.first += 1; point.second += 1;
    const uint32_t rack_id = point.first + 10;
    uint32_t power = rack_id * point.second;
    power += serial;
    power *= rack_id;
    power = int(power / 100 % 10);
    return power - 5;
}