/**
 * @author John Heath
 * @date 1.7.18
 * CS2 Assignment 1 Part 3
 */
#ifndef grid_hpp
#define grid_hpp
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

/**
 * @brief The Grid class provides the mechanics for loading, displaying, and 
 * otherwise working with the actual sudoku board. The board can be checked
 * and altered using methods of this class only. 
 * 
 * Each Grid object represents a different sudoku board. 
 */
class Grid
{
private:
    char grid_arr[9][9];
public:
    Grid();
    Grid(string filename);
    void loadBoard(string filename);
    bool isComplete();
    bool checkValid(int x, int y, char val);
    void writeNum(int x, int y, char val);
    void displayGrid();
    bool is_space(int x, int y);
};


#endif /* grid_hpp */
