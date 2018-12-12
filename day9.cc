#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
int part_one(const int num_players, const int num_marbles);
int part_two(const int num_players, const int num_marbles);

int main() {
    const int players = 462;
    const int last_marble = 71938;
    std::cout << "Part 1: " << part_one(players, last_marble) << std::endl;
    std::cout << "Part 2: " << part_two(players, last_marble) << std::endl;

}
int mod(const int i, const int j) {
    int res = i % j;
    while (res < 0) 
        res += j;
    return res;
} 
int part_one(const int num_players, const int num_marbles) {
    std::vector<int> player_scores(num_players);
    std::vector<int> marbles;
    int index = 0;
    int player = 0;
    marbles.push_back(0);

    for (int i = 1; i <= num_marbles; i++) {
        player = (player + 1) % num_players;
        if (i % 23 == 0) {
            index = mod(index - 7, marbles.size());
            int val = marbles[index];
            marbles.erase(marbles.begin() + index);
            player_scores[player] += val + i;
        } else {
            index = mod(index + 2, marbles.size()) ;
            marbles.insert(marbles.begin() + index, i);
        }
    }
    
    return *std::max_element(player_scores.begin(), player_scores.end());

}

int part_two(const int num_players, const int num_marbles) {
    std::vector<int> player_scores(num_players);
    std::list<int> marbles;
    marbles.push_back(0);
    auto it = marbles.begin();
    int player = 0;
    for (int i = 1; i <= num_marbles; i++) {
        player = (player + 1) % num_players;
        if (i % 23 == 0) {
            // index 
            for (int j = 0; j < 7; j++) {
                if (it == marbles.begin()) 
                    it = marbles.end();
                 else 
                    it--;
            
            }            
            player_scores[player] += *it + i;
            //std::cout << "iter: " << *it << std::endl;
            //std::cout << "i " << i << std::endl;
            it = marbles.erase(it);
        } else {
            //index = mod(index + 2, marbles.size());
            //std::advance(it, index - std::distance(marbles.begin(), it));
            for (int j = 0; j < 2; j++) {
                if (it == marbles.end()) 
                    it = marbles.begin();
                else 
                    it++;
                //std::cout << *it << std::endl;
            }
            marbles.insert(it, i);
        }
        

    }
    
    std::list<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    auto ai = a.begin();
    for (int i = 0; i < 6; i++) {
        if (ai == a.end()) {
            ai = a.begin();
        } else {
            ai++;
        }
        std::cout << *ai << std::endl;
    }
    //std::cout << "res: " << *ai << std::endl;
    
    return *std::max_element(player_scores.begin(), player_scores.end());
}