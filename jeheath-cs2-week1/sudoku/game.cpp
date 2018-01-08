/**
 * @author John Heath
 * @date 1.7.18
 * CS2 Assignment 1 Part 3
 * @brief
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
 *
 */
Game::Game(string filename)
{
    grid = Grid(filename);
}

/**
 * @brief Obtains the next move from the user, and demands that the move 
 * is formatted correctly. Calls functions on grid that execute the move.
 * 
 * @return Returns 0 in the event of a successful move or undo. Returns
 * 1 if the user quits. 
 * 
 * Note: This uses heap memory when filling the moves forward_list. This 
 * memory is reallocated at the end by the wipe moves method or undoing 
 * the move. 
 * 
 * Given errors in user input, this function will throw errors to be 
 * printed and caught by the Run function. 
 */
bool Game::getMove()
{
    cout << "Enter your move: ";
    string move_str; // This will be the full user inputted string
    getline(cin, move_str);
    int len = (int) move_str.length(); // len is the length of the input
    if (len == 0)
    {
        throw "ERROR. There was no input!";
    }
    
    string valid ("123456789"); // A string containing every valid input
    
    int index = 0;
    while(isspace(move_str[index]) && index < (len - 1)) 
    {
        index++; // clears whitespace, avoids bound errors
    }
    if (move_str[index] == 'q')
    {
        cout << "You have decided to quit" << endl;
        return true; // This denotes game-over to the rest of the program
    }
    else if (index == len - 1)
    {
        throw "ERROR. There was insufficient input!";
        // This error will result from the user only inputting a single
        // letter (other than q), or just whitespace
    }
    else if (move_str[index] == 'd') // There is a move!
    {
        char full_move[3] = {'0', '0', '0'};
        
        for (int i = 0; i < 3; i++) // three values must be extracted 
                                    // from the string
        {
            index++; // shift to the next character
            while(isspace(move_str[index]) && index < (len - 1)) 
            {
                index++; //clears whitespace while avoiding bound errors
            }
            // I will use the string method "find" to see if the 
            // following 3 characters the user entered were valid 
            // characters. 
            size_t found = valid.find(move_str[index]);
            if (found != string::npos) // --> If valid
            {
                full_move[i] = move_str[index]; // stores correctly 
                                                // formatted moves
            }
            else
            {
                throw "ERROR. That move has insufficient or invalid characters.";
            }
        }
        // I now have to check that there is no more user input. 
        // For example, an undo with three values is not acceptable. 
        if (index < (len - 1))
        {
            index++;
            while(isspace(move_str[index]) && index < (len - 1)) 
            {
                index++; //clears whitespace while avoiding bound errors
            }
            if (!isspace(move_str[index]))
            {
                throw "ERROR. You entered too many values";
            }
        }
        
        // Now to check if the move even works on the board!
        
        if (grid.checkValid((int) (full_move[0] - '0'), 
                            (int) (full_move[1] - '0'),
                            full_move[2]))
        {
            // The move is valid!!
            grid.writeNum((int) (full_move[0] - '0'), 
                          (int) (full_move[1] - '0'),
                          (char) full_move[2]);
            
                        
            char * move = new char[2]; // Each successful move will be
                                       // stored permanently, and deleted
                                       // upon game-over
            move[0] = full_move[0];
            move[1] = full_move[1];
            moves.push_front(move); // adds move to the list of moves
            return false; // indicates successful move
        }
        else
        {
            throw "ERROR. That move is not valid due to the rules of sudoku.";
        }
    }
    else if (move_str[index] == 'u') // The user wants to undo a move!
    {
        return undo(index, move_str, len);
    }
    else 
    {
        throw "ERROR. Your command did not begin with a valid character.";
    }
    return false;
}


/**
 * @brief This method is called whenever the user inputs a 'u' character 
 * first. It scans the rest of their input for validity, and then undoes
 * the specified move if valid. 
 * 
 * @return Returns 0 upon successful execution
 * 
 * @param index This is the index of the first meaningful character found
 * in the user input string
 * @param move_str This is the user input string
 * @param len This is the length of the user input string
 */
int Game::undo(int index, string move_str, int len)
{
    string valid ("123456789"); // A string containing every valid input
    char undo_move[2] = {'0', '0'};
    for (int i = 0; i < 2; i++) // two values must be extracted 
    {
        index++;
        while(isspace(move_str[index]) && index < (len - 1)) 
        {
            index++; //clears whitespace while avoiding bound errors
        }
        // Mirrors the process for validating earlier input. 
        size_t found = valid.find(move_str[index]);
        if (found != string::npos) // --> If valid
        {
            undo_move[i] = move_str[index];
        }
        else
        {
            throw "ERROR. That move has insufficient or invalid characters.";
        }
    }
    // I now have to check that there is no more user input. 
    // For example, an undo with three values is not acceptable. 
    if (index < (len - 1))
    {
        index++;
        while(isspace(move_str[index]) && index < (len - 1)) 
        {
            index++; //clears whitespace while avoiding bound errors
        }
        if (!isspace(move_str[index]))
        {
            throw "ERROR. You entered too many values";
        }
    }
    // Now I will check if undo_move is within moves.
    bool true_undo = false;
    for (char * m : moves)
    {
        if (*m == undo_move[0] && *(m + 1) == undo_move[1])
        {
            true_undo = true;
            moves.remove(m);
            delete[] m;
        }
    }
    if (true_undo)
    {
        char space = ' ';
        grid.writeNum((int) (undo_move[0] - '0'),
                      (int) (undo_move[1] - '0'),
                      space);
                      
        cout<< "Successful undo" << endl;
        return 0;
    }
    else
    {
        throw "ERROR. The space you entered cannot be removed";
    }
}


/**
 * @brief This function creates a grid object, and repeatedly prompts 
 * the user for their turn until they quit or win. Errors from other 
 * methods are caught here and printed. 
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
        try
        {
            x = getMove();
            if (!x)
            {
                grid.displayGrid();
            }
        }
        catch (const char* msg) // Error handling done here
        {
            cout << msg << endl;
        }
    }
    // The game has ended
}


/**
 * @brief This function is called at game over, and deletes the individual
 * moves that were stored in the heap. 
 */
void Game::wipe_moves()
{
    char * m;
    while (!moves.empty())
    {
        m = moves.front();
        moves.pop_front();
        delete[] m;
    }
}


