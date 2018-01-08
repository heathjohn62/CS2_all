/**
 * @author John Heath
 * @date 1.7.18
 * CS2 Assignment 1 Part 3
 */
#include "sudoku.hpp"
#include "grid.hpp"
#include "game.hpp"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    //ask for filename
    string filename = "";
    //state instructions
    Game g = Game(filename);
    g.Run();
    //say thanks, 
    g.wipe_moves();
    return 0;
}
