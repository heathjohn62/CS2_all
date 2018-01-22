#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;
/**
 * This is a minesweeper game. It will load a file that you input, given
 * that the file is a set of characters, E and M, and that it is square.
 */


class Minesweeper
{
public:
unsigned int size;// This is the length of each side of the square array
char** arr; // This is the actual game board

/**
 * @brief This constructor gathers input from the user and constructs the game 
 * board from a filename. It throws an exception if the file cannot be 
 * found. 
 */
Minesweeper()
{
    cout << "What is the name of the file you want to input? " 
         << endl << "The name of the demo file is demo.txt    ";
    string filename;
    cin >> filename;
    ifstream file;
    file.open(filename, ifstream::in);
    
    if (file.is_open()) 
    { // If the program enters here, it found and opened the file!
        int row = 0;
        string line;
        getline(file, line);
        int s = line.length(); 
        size = s; // size is initialized
        arr = new char*[size];
        do
        {    
            arr[row] = new char[size];
            for(unsigned int i = 0; i < size; i++)
            {
                arr[row][i] = line[i];
            }
            row++;
        } while (getline(file, line));
        file.close();
    }
    else
    {
        throw "ERROR. File could not be opened. ";
    }
}

/**
 * @brief This function, recursive_reveal, is a helper function to 
 * assist with the clearing of blank cells that are not adjacent to a mine. 
 * @param x The row of the cell to be investigated
 * @param y The column of the cell to be investigated
 * @returns nothing
 */
void r_reveal(unsigned int x, unsigned int y)
{
    int bombs = 0;
    arr[x][y] = '0'; // Temporary change to prevent the program from
                     // entering an infinite recursive loop
                     
    // Imbedded for loop checks all squares within a unit of the current.
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            // This is a bounds check
            if((x + i < size) && (y + j < size) 
              && (x + i >= 0) && (y + j >= 0))
            {
                if(arr[x + i][y + j] == 'M' || arr[x + i][y + j] == 'X')
                {
                    bombs++; // bomb detected
                }
            }
        }
    }
    // It is irritating to have to do an imbedded for-loop twice over the
    // same elements, but it is important to know whether there are any 
    // bombs adjacent to the cell before recursively calling the function.
    if (bombs == 0)
    {
        arr[x][y] = 'B'; // no bombs -> cell = 'B'
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if((x + i < size) && (y + j < size) 
              && (x + i >= 0) && (y + j >= 0))
                {
                    if (arr[x + i][y + j] == 'E')
                    {
                        r_reveal(x + i, y + j); // recusion! 
                        // Any 'E' next to this point will be given the same
                        // analysis
                    }
                }
            }
        }
    }
    else
    {
        // This makes the cell display the number of adjacent bombs.
        arr[x][y] = (char)(bombs + '0');
    }
}

/**
 * @brief This is a helper function that carries out a user move. 
 * If a bomb is chosen, the cell is changed, and if an empty cell is 
 * chosen, r_reveal is called.
 * @param x The row of the cell to be investigated
 * @param y The column of the cell to be investigated
 * @returns nothing
 */
void reveal(unsigned int x, unsigned int y)
{
    // Settles case of clicking on a bomb
    if (arr[x][y] == 'M') 
    {
        arr[x][y] = 'X';
    }
    else if (arr[x][y] == 'E')
    {
        r_reveal(x, y); // recursive helper function
    }
}

/**
 * @brief This is a helper function which prints the current state of 
 * the game. No parameters, no return value.
 */
void print_arr()
{
    for (unsigned int i = 0; i < size; i++)
    {
        for (unsigned int j = 0; j < size; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * @brief This is essentially an explicit deconstructor for the 
 * minesweeper class. The dynamically allocated game board is deleted 
 * row by row. No parameters, no return value. 
 */
void kill_game()
{
    for (unsigned int i = 0; i < size; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}
}; // End of class description


/**
 * @brief Main function for the minesweeper game. Creates a minesweeper
 * object, initializes it, loops the game until the user quits, 
 * and call the clean up function afterwards. Errors are caught, and the 
 * messages are printed out. 
 * @returns 0
 */
int main()
{
    try
    {
        Minesweeper * m = new Minesweeper();
        
        m->print_arr();
        cout << "Enter a move in the form \"row column\" where the first"
             << "row/column is 0. " << endl 
             << "Enter 2 negative numbers to quit." << endl;
        bool done = false;
        while (!done)
        {
            cout << "Enter: ";
            int x = 0, y = 0;
            cin >> x >> y;
            if (x < 0 || y < 0)
            {
                cout << "You have quit" << endl;
                done = true;
            }
            else
            {
                m->reveal((unsigned int)x, (unsigned int)y);
                m->print_arr();
            }
        }
        m->kill_game();
        delete m;
    }
    catch(const char* msg)
    {
        cout << msg << endl;
        cout << "You will have to run the program again" << endl;
    }
    return 0;
}
