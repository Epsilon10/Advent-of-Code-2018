#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <map>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

const std::string dir_chars = "^v><";

using Point = std::pair<int,int>;

struct Cart {
    uint32_t x;
    uint32_t y;
    Direction dir;
    uint32_t intersection_count = 0;

    void advance(const char next_token) {
        if (next_token == '\\') {
            if (dir == RIGHT || dir == LEFT)
                turn_right();
            else 
                turn_left();
        }
        else if (next_token == '/') 
            if (dir == RIGHT || dir == LEFT)
                turn_left();
            else 
                turn_right();
        else if (next_token == '+') {
            if (intersection_count == 0) {
                intersection_count++;
                turn_left();
            } else if (intersection_count == 1) {
                intersection_count++;
                move();
            } else {
                intersection_count = 0;
                turn_right();
            } 
        }

        else if (next_token == '-' || next_token == '|') 
            move();
        
    }

    void move() {
        if (dir == LEFT)
            x -= 1;
        else if (dir == RIGHT) 
            x += 1;
        else if (dir == DOWN) 
            y += 1;
        else if (dir == UP)
            y-=1;
    }

    void turn_left() {
        move();
        if (dir == LEFT)
            dir = DOWN;
        else if (dir == RIGHT) 
            dir = UP;
        else if (dir == DOWN) 
            dir = RIGHT;
        else if (dir == UP)
            dir = LEFT;
    }

    void turn_right() {
        move();
        if (dir == LEFT)
            dir = UP;
        else if (dir == RIGHT) 
            dir = DOWN;
        else if (dir == DOWN) 
            dir = LEFT;
        else if (dir == UP)
            dir = RIGHT;
    }
    


};

Point part_one(std::vector<std::vector<char> >& path);
Point part_two(std::vector<std::vector<char> >& path); 
std::vector<std::vector<char> > read_file_char(const std::string&& filename);
int main() {
    auto path = read_file_char("day13.txt");
    Point crash = part_one(path);
    Point last_cart = part_two(path);
    std::cout << "Part 1 Crash - " << crash.first << ", " << crash.second << std::endl;
    std::cout << "Part 2 Last cart - " << last_cart.first << ", " << last_cart.second << std::endl;
}

Point part_one(std::vector<std::vector<char> >& path) {
    std::vector<Cart> carts;
    for (uint32_t y = 0; y < path.size(); y++) {
        for (uint32_t x = 0; x < path[y].size(); x++) {
            char token = path[y][x];
            Direction dir;
            if (token == '^') {
                dir = UP;
                path[y][x] = '|';
            }
            else if (token == 'v') {
                dir = DOWN;
                path[y][x] = '|';
            }
            else if (token == '>') {
                dir = RIGHT;
                path[y][x] = '-';
            }
            else if (token == '<') {
                dir = LEFT;
                path[y][x] = '-';
            }
            if (dir_chars.find_first_of(token) != std::string::npos) {
                struct Cart cart = {.x = x, .y = y, .dir = dir};
                carts.push_back(cart);
            }

        }
    }

    std::vector<Point> cart_points(carts.size());

    Point crash_point;
    bool to_break = false;
    while (true) {
        for (Cart& cart : carts) {
            std::string ddir;
            if (cart.dir == LEFT)
                ddir = "left";
            if (cart.dir == RIGHT)
                ddir = "right";
            if (cart.dir == UP)
                ddir = "up";
            if (cart.dir == DOWN)
                ddir = "down";

            
            //std::cout << "Cart X Pos: " << cart.x << " Cart Y Pos: " << cart.y << " " << ddir << std::endl;
            char next_token;
            uint32_t new_x = cart.x;
            uint32_t new_y = cart.y;
            if (cart.dir == UP) 
                new_y--;
            else if (cart.dir == DOWN)
                new_y++;
            else if (cart.dir == RIGHT)
                new_x++;
            else
                new_x--;
            next_token = path[new_y][new_x];
            //std::cout << "Cart X Pos: " << cart.x << " Cart Y Pos: " << cart.y << " " << ddir << " next token: " << next_token << std::endl;
            cart.advance(next_token);
            Point point = Point(cart.x, cart.y);

            if (std::find(cart_points.begin(), cart_points.end(), point) != cart_points.end()) {
                to_break = true;
                crash_point = point;
                break;
            }
                
            cart_points.push_back(point);
        }

        if (to_break) break;
        cart_points.clear();
        // check for any common points in the vecto
    }

    return crash_point;

}

Point part_two(std::vector<std::vector<char> >& path) {
    std::vector<Cart> carts;
    for (uint32_t y = 0; y < path.size(); y++) {
        for (uint32_t x = 0; x < path[y].size(); x++) {
            char token = path[y][x];
            Direction dir;
            if (token == '^') {
                dir = UP;
                path[y][x] = '|';
            }
            else if (token == 'v') {
                dir = DOWN;
                path[y][x] = '|';
            }
            else if (token == '>') {
                dir = RIGHT;
                path[y][x] = '-';
            }
            else if (token == '<') {
                dir = LEFT;
                path[y][x] = '-';
            }
            if (dir_chars.find_first_of(token) != std::string::npos) {
                struct Cart cart = {.x = x, .y = y, .dir = dir};
                carts.push_back(cart);
            }

        }
    }

    std::vector<Point> cart_points(carts.size());
    
    Point last_cart;
    bool to_break = false;
    while (true) {
        for (Cart& cart : carts) {
            std::string ddir;
            if (cart.dir == LEFT)
                ddir = "left";
            if (cart.dir == RIGHT)
                ddir = "right";
            if (cart.dir == UP)
                ddir = "up";
            if (cart.dir == DOWN)
                ddir = "down";
            
            //std::cout << "Cart X Pos: " << cart.x << " Cart Y Pos: " << cart.y << " " << ddir << std::endl;
            char next_token;
            uint32_t new_x = cart.x;
            uint32_t new_y = cart.y;
            if (cart.dir == UP) 
                new_y--;
            else if (cart.dir == DOWN)
                new_y++;
            else if (cart.dir == RIGHT)
                new_x++;
            else
                new_x--;
            next_token = path[new_y][new_x];
            //std::cout << "Cart X Pos: " << cart.x << " Cart Y Pos: " << cart.y << " " << ddir << " next token: " << next_token << std::endl;
            cart.advance(next_token);
            Point point = Point(cart.x, cart.y);
            auto it = std::find(cart_points.begin(), cart_points.end(), point);
            if (it != cart_points.end()) {
                std::cout << "ff" << std::endl;
                cart_points.erase(it);
            }
            if (cart_points.size() == 1) {
                last_cart = cart_points[0];
                to_break = true;
                break;
            }    
            cart_points.push_back(point);
        }

        if (to_break) break;
        cart_points.clear();
        // check for any common points in the vecto
    }

    return last_cart;

}




std::vector<std::vector<char> > read_file_char(const std::string&& filename) {
    std::ifstream input(filename);
    std::vector<std::vector<char> > lines;
    for( std::string line; getline( input, line ); )
        lines.push_back(std::vector<char>(line.begin(), line.end()));
    return lines;
}