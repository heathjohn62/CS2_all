/**
 * @author John Heath
 * @date 1.7.18
 * CS2 Assignment 1 Part 3
 */
#ifndef game_hpp
#define game_hpp
#include <stdio.h>
#include <forward_list>
#include <string>
#include <iostream>
#include "grid.hpp"

using namespace std;

/**
 * @brief The game class provides the setup through which one can play 
 * sudoku. Objects of this class own a game grid, and remember the moves
 * the user has played. 
 */
class Game
{
private:
    forward_list<string> moves;
    Grid grid;
public:
    Game();
    Game(string filename);
    ~Game();
    bool getMove();
    void Run();
    int undo(int index, string move_str, int len);
};

#endif /* game_hpp */
