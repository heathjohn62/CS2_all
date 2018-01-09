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
 * @brief The game class implements the sudoku solver, using a grid object 
 * for assistance. 
 */
class Game
{
private:
    Grid grid;
    string nums = "123456789";
public:
    Game();
    Game(string filename);
    void move(string full_move);
    void Run();
    void undo(string move_str);
    void recursive_solve(int cell_num);
};

#endif /* game_hpp */
