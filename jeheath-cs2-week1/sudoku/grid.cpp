/**
 * @author John Heath
 * @date 1.7.18
 * CS2 Assignment 1 Part 3
 */
#include "grid.hpp"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const string __VALID__ = "123456789";
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
            grid_arr[i][j] = '0'; 
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
 * @brief This method loads the board at a given filename onto the 
 * grid_arr array. Throws an error if the file cannot be found. 
 * 
 * @param filename The name of the board file to be loaded. 
 */
void Grid::loadBoard(string filename)
{
    string line;
    ifstream file (filename);
    if (file.is_open()) 
    { // If the program enters here, it found and opened the file!
        int row = 0;
        while (getline(file, line)) // This loops while the file still
        {                           // has information, and also stores 
            if (line.length() != 9) // that info in the line string.
            {
                file.close();
                throw "ERROR. That file is incorrectly formatted.";
            }
            for(int i = 0; i < 9; i++)
            {
                grid_arr[row][i] = line[i];
            }
            row++;
        }
        if (row != 9)
        {
            file.close();
            throw "ERROR. That file is incorrectly formatted.";
        }
        file.close();
    }
    else
    {
        throw "ERROR. File could not be opened. ";
    }
}

/**
 * @brief Checks to see if each board space is filled. Returns true if
 * the user has won, and false otherwise. 
 * 
 * @return The boolean denoting whether the user has won or not. 
 */
bool Grid::isComplete()
{
     // If all the elements in grid_arr can be found in __VALID__, 
     // the user has won. 
     
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            size_t found = __VALID__.find( (char) grid_arr[i][j]);
            if (found == string::npos) // --> If invalid character
            {
                return false; // There is an element that is not valid.
            }
        }
    }
    return true;
}

/**
 * @brief Checks to see if a given move is valid; returns false if the 
 * row, column, or box has the number, or if the spot is filled. Returns
 * true otherwise. 
 * 
 * @param x The row of the sudoku space in question.
 * @param y The column of the sudoku space in question.
 * @param val The value to be placed in the space. 
 * 
 * @return The boolean indicating whether the move is valid. 
 */
bool Grid::checkValid(int x, int y, char val)
{
    // Check spot
    char space = ' ';
    if (grid_arr[x-1][y-1] != space)
    {
        return false; // That space is taken by another number!
    }
    
    // check row: 
    int row = x - 1;
    for (int i = 0; i < 9; i++)
    {
        if (grid_arr[row][i] == val)
        {
            return false; // The number suggested was found in the 
                          // same row!
        }
    }
    
    // check column:
    int col = y - 1;
    for (int i = 0; i < 9; i++)
    {
        if (grid_arr[i][col] == val)
        {
            return false; // The number suggested was found in the 
                          // same column!
        }
    }
    
    // check box:
    int row_1 = 0; // These are the starting indicies for the box to be
    int col_1 = 0; // checked. 
    if (x > 3 && x < 7)
    {
        row_1 = 3;
    }
    else if (x >= 7)
    {
        row_1= 6;
    }
    if (y > 3 && y < 7)
    {
        col_1 = 3;
    }
    else if (y >= 7)
    {
        col_1= 6;
    }
    // The indicies are now set to the top left corner of the box to check
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid_arr[row_1 + i][col_1 + j] == val)
            {
                return false; // The number suggested was found in the 
                              // same box!
            }
        }
    }
    return true;
}

/**
 * @brief Changes the board grid to reflect a new move. 
 * 
 * @param x The row of the new move
 * @param y The column of the new move
 * @param val The value to be placed on the space
 */
void Grid::writeNum(int x, int y, char val)
{
    grid_arr[x - 1][y - 1] = val;
}


/**
 * @brief Prints the board grid in a conventional sudoku format to the 
 * terminal. 
 */
void Grid::displayGrid()
{
    int row = 0;
    int col = 0;
    for (int m = 0; m < 3; m++)
    {
        cout << "-------------------------" << endl;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << "| ";
                for (int k = 0; k < 3; k++)
                {
                    cout << (char) grid_arr[row][col] << " ";
                    col++;
                }
            }
            cout << "|" << endl;
            row++;
            col = 0;
        }
    }
    cout << "-------------------------" << endl;
}




