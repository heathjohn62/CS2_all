/**
 * @author John Heath
 * @date 1.7.18
 * CS2 Assignment 1 Part 3
 * @brief
 */
#include "game.hpp"
#include <stdio.h>
#include <forward_list>
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Empty constructor for the game class
 */
Game::Game()
{
    // The instance variable (the move list) initializes as empty, 
    // which is desired. 
    grid = Grid();
}

/**
 * @brief Main constructor for the game class. 
 * @param filename The name of the file to be loaded onto the game board
 * 
 * This creates an object of the game class, and initializes the grid on
 * which the game will take place. 
 */
Game::Game(string filename)
{
    grid = Grid(filename);
}

/**
 * @brief Obtains the next move from the user, and demands that the move 
 * is formatted correctly. 
 * 
 * 
 */
bool Game::getMove()
{
    cout << "Enter your first move: ";
    string move_str; // This will be the full user inputted string
    getline(cin, move_str);
    size_t len = move_str.length() // len is the length of the input
    if (len == 0)
    {
        throw "There was no input!";
    }
    
    string valid = "123456789"; // A string containing every valid input
    
    int index = 0;
    while(move_str[index] == " " && index < len - 1) 
    {
        index++; // clears whitespace, avoids bound errors
    }
    if (move_str[index] == 'q')
    {
        cout << "You have decided to quit" << endl;
        return 1; // This denotes game-over to the rest of the program
    }
    else if (index == len - 1)
    {
        throw "There was insufficient input!";
        // This error will result from the user only inputting a single
        // letter (other than q), or just whitespace
    }
    else if (move_str[index] == 'd')
    {
        char full_move[3] = {'0', '0', '0'};
        for (int i = 0; i < 3; i++)
        {
            index++;
            while(move_str[index] == " " && index < len - 1)
            {
                index++; //clears whitespace while avoiding bound errors
            }
            
            // I will use the string method "find" to see if the 
            // following 3 characters the user entered were valid 
            // characters. 
            size_t found = valid.find(move_str[index]);
            if (found != string::npos)
            {
                
            }
            else
            {
                
            }
        }
        // initiate move
        char * move = new char[2];
        // return 0;
    }
    else if (move_str[index] == 'u')
    {
        //initiate undo
    }
    else
    {
        throw "Your command did not begin with a valid character.";
    }
    return 0;
}

/**
 * 
 */
bool Game::Run()
{
    grid.displayGrid(); 
    int x = 0;
    while (x == 0)
    {
        try
        {
            x = getMove();
            grid.displayGrid();
        }
        catch (const char* msg)
        {
            cout << msg << endl;
        }
    }
    return 1; // 1 denotes a game-over situation
}

void Game:wipe_moves()
{
    //traverse through moves and delete each move
}
