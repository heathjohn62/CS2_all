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

class Grid
{
private:
    int grid[9][9];
public:
    Grid();
    Grid(string filename);
    void loadBoard(string filename);
    bool isComplete();
    bool checkValid(int x, int y, char val);
    void writeNum(int x, int y, char val);
    void displayGrid();
};


#endif /* grid_hpp */
