/**
 * @author John Heath
 * @date 1.7.18
 * CS2 Assignment 1 Part 3
 * @brief
 */
#include "grid.hpp"
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;
/**
 * @brief Empty constructor for the Grid class. Initializes the grid 
 * with zeros.
 */
Grid::Grid()
{
    for(int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            grid[i][j] = '0'; 
        }
    }
}
/**
 * @brief Main constructor for the Grid class. Initializes the grid by 
 * calling loadboard on the specified filename. 
 * @param filename the filename of the board to be loaded onto grid. 
 */
Grid::Grid(string filename)
{
    loadBoard(filename);
}

/**
 * 
 */
void Grid::loadBoard(string filename)
{
    
}

/**
 * 
 */
bool Grid::isComplete()
{
    return false;
}

bool Grid::checkValid(int x, int y, char val)
{
    // ensure that I check to see if the spot is filled too
    return true;
}

/**
 * 
 */
void Grid::writeNum(int x, int y, char val)
{
    
}

/**
 * 
 */
void Grid::undoNum(int x, int y)
{
     
}

/**
 * 
 */
void Grid::displayGrid()
{
    
}






