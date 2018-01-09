/**
 * @author John Heath
 * @date 1.7.18
 * CS2 Assignment 1 Part 3
 * 
 * 
 * I use a recursive algorithm to solve each sudoku puzzle. Essentially,
 * the program will make a valid guess on each square, and try to figure out
 * the remainder of the puzzle assuming it is right, and it will change 
 * it's guess if none of the combinations work. 
 * 
 * This uses exponential time, but since there are a limited number of 
 * valid guesses that can be made on a sudoku board, the program runs 
 * fairly fast. A 100x100 sudoku board would take a very, very long time. 
 */
#include "grid.hpp"
#include "game.hpp"
#include <string>
#include <iostream>

using namespace std;


/**
 * @brief Main method of the sudoku program. Prompts for a board to 
 * load, and starts the game with that board. Will print an error and
 * prompt again if a faulty file is given. 
 * 
 * @return Returns 0 given succesful completion. 
 */
int main()
{
    cout << "What is the name of the file you would like to solve? " 
         << "('q' to quit)" << endl;
    string filename;
    cin >> filename;
    try
    {
        Game g = Game(filename);
        g.Run();
        return 0;
    }
    catch (const char* msg)
    {
        if (filename.length() == 1 && filename[0] == 'q') 
        {
            cout << "You have decided to quit. " << endl;
            return 0;
        }
        else
        {
            cout << msg << endl;
            main();
            return 0;
        }
    }
    return 0;
}
