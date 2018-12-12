#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <climits>
#include <sstream>

std::vector<std::string> read_file_lines(const std::string&& filename);
int part_one(std::vector<std::pair<int, int> >& points, const std::vector<std::pair<int, int> >& velocities);
int main() {
    const std::vector<std::string> lines = read_file_lines("day10.txt");
    std::vector<std::pair<int, int> > points(lines.size());
    std::vector<std::pair<int, int> > velocities(lines.size());

    for (const std::string& line : lines) {
        auto remaining = line;
        remaining = remaining.substr(10);
        size_t taken = 0;
        auto x = std::stoi(remaining, &taken);
        remaining = remaining.substr(taken + 1);
        auto y = std::stoi(remaining, &taken);
        remaining = remaining.substr(taken + 12);
        auto vx = std::stoi(remaining, &taken);
        remaining = remaining.substr(taken + 1);
        auto vy = std::stoi(remaining, &taken);

        points.push_back(std::pair<int, int>(x, y));
        velocities.push_back(std::pair<int, int>(vx, vy));
    }
    part_one(points, velocities);

}
std::vector<std::vector<char> > create_2d_array(const int width, const int height);
int part_one(std::vector<std::pair<int, int> >& points, const std::vector<std::pair<int, int> >& velocities) {
    int y_offset = INT_MAX;
    std::vector<std::pair<int, int> > last_points = points;    
    int second = 0;
    while (true) {
        second++;
        for (int i = 0; i < points.size(); i++) {
            points[i].first += velocities[i].first;
            points[i].second += velocities[i].second;
        }
        
        const auto&& [miny, maxy] = std::minmax_element(points.begin(), points.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });
        
        int curr_offset = maxy->second - miny->second;
        if (y_offset < curr_offset) {
            std::cout << "seconds taken: " << second - 1 << std::endl;
            break;
        }
        last_points = points;
        y_offset = curr_offset;
    }

    const auto&& [minx, maxx] = std::minmax_element(last_points.begin(), last_points.end());
    const int min_x = minx->first;
    const int max_x = maxx->first;
    const auto&& [miny, maxy] = std::minmax_element(last_points.begin(), last_points.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });

    const int min_y = miny->second;
    const int max_y = maxy->second;

    const int w = max_x - min_x + 1;
	const int h = max_y - min_y + 1;

    std::vector<std::vector<char> > c;
	{
		std::vector<char> lineTemplate(w, '.');
		c.resize(h, lineTemplate);
	}
	for(auto p : last_points)
	{
		c[p.second - min_y][p.first - min_x] = '#';
	}
	for(int y = 0; y < h; y++)
	{
		for(int x = 0; x < w; x++)
		{
			std::cout << c[y][x];
		}
		std::cout << '\n';
	}
	std::cout << std::flush;
    
    return 0;
}

std::vector<std::string> read_file_lines(const std::string&& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    for( std::string line; getline( file, line ); )
        lines.push_back(line);

    return lines;
    
}

std::vector<std::vector<char> > create_2d_array(const int width, const int height) {
    return std::vector<std::vector<char> >(width, std::vector<char>(height, '.'));
}