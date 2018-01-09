/**
 * @author John Heath
 * @date 1.7.18
 * CS2 Assignment 1 Part 3
 */
#include "game.hpp"
#include "grid.hpp"
#include <stdio.h>
#include <forward_list>
#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;


/**
 * @brief Empty constructor for the game class. Not recommended for use.
 */
Game::Game()
{
    grid = Grid();
}

/**
 * @brief Main constructor for the game class. 
 * @param filename The name of the file to be loaded onto the game board
 * 
 * This creates an object of the game class, and initializes the grid on
 * which the game will take place. 
 *
 */
Game::Game(string filename)
{
    grid = Grid(filename);
}

/**
 * @brief Makes a specified move that is assumed valid. 
 * 
 */
void Game::move(string full_move)
{
    // The move is valid!!
    grid.writeNum((int) (full_move[0] - '0'), 
                  (int) (full_move[1] - '0'),
                  (char) full_move[2]);
}


/**
 * @brief This method simply rewrites the array with a space instead of
 * the prevous value. All previous safety checks are no longer in place
 * since it is no longer at the mercy of user input.  
 *
 * @param move_str This is the move, in the form "xyval"
 */
void Game::undo(string move_str)
{
    char space = ' ';
    grid.writeNum((int) (move_str[0] - '0'),
                  (int) (move_str[1] - '0'),
                   space);
}


/**
 * @brief This function displays the grid, runs the recursive program, 
 * and checks for victory. 
 * 
 */
void Game::Run()
{
    string junk;
    getline(cin, junk); // Prevents the filename from being interpreted 
                        // as a move.
    grid.displayGrid(); 
    bool x = false;
    while (!x)
    {
        if (grid.isComplete()) // Checks if the user has won
        {
            cout << "SOLVED. You Win!!!" << endl;
            return; // The game has ended
        }
        recursive_solve(0);
    }
    // The game has ended
}

/**
 * @brief This is the coolest part of the program. This program makes a 
 * guess at a space, and then tries every possibility for the next space
 * by calling itself. If it is wrong, the move is undone and it moves to 
 * the next space. 
 */
void Game::recursive_solve(int cell_num)
{
    if (grid.isComplete())
    {
        grid.displayGrid();
        return;
    }
    int col = cell_num % 9;
    int row = cell_num / 9;
    char val;
    while (!grid.is_space(row + 1, col + 1))
    {
        cell_num++;
        col = cell_num % 9;
        row = cell_num / 9;
    }
    for (int i = 1; i <= 9; i++)
    {
        val = nums[i-1];
        if (grid.checkValid(row + 1, col + 1, val))
        {
            move({(char) (row + 1 + '0'), (char) (col + 1 + '0'), val});
            
            recursive_solve(cell_num + 1);
            if (grid.isComplete())
            {
                return;
            }
            undo ({(char) (row + 1 + '0'), (char) (col + 1 + '0')});
        }
    }
}



