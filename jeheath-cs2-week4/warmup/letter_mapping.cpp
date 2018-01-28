/**
 * @author John Heath
 * @date January 27, 2018
 * CS2 Warmup Problem Set 4
 * 
 * This program detects whether an integer input can be translated into 
 * letters given the code: a = 1 ... z = 26. 
 * 
 * This program has linear (O(n)) time and space complexity. There will
 * be, at worst, a series of if checks and one function call per digit 
 * of the int. There is linear space complexity because the parameter is
 * stored in every recursive frame, which will at worst amount to n
 * different numbers in total, for an n digit number. 
 */
#include <iostream>
 
using namespace std;

/**
 * Determines whether the argument integer can be translated into a 
 * string, where each letter is a number, 1-26. Works recursively. 
 * @param unsigned int x The number to be translated into a string. 
 * @returns bool Whether the number can be expressed as a string
 */
bool expressable(unsigned int x)
{
    // There are special cases when the second to last digit is 0, or 
    // when x just has a single digit. We shall deal with these first. 
    
    if ((x / 10) % 10 == 0) // If the second to last digit is 0 or absent
    {
        if (x % 10 == 0) // If the last digit is 0
        {
            return false; // 0 case, or any number with "00"
        }
        else // The second to last digit is 0, but the last digit is a 
             // non-zero number. 
        {
            if (x / 10 == 0)
            {
                return true; // End case for a single digit number
            }
            return expressable(x/10); // Removes the last digit and 
                                      // calls the function again.
        }
    }
    
    // Now we shall examine the cases where the last digit equals 0. 
    if (x % 10 == 0)
    {
        if (x % 100 <= 26 && x % 100 >= 1)
        {
            if (x / 100 == 0)
            {
                return true;
            }
            else
            {
                return expressable(x / 100);
            }
        }
        else
        {
            return false; // last digit = 0, and the last two are not a 
                          // number between 1 and 26. Thus, the number 
                          // must be 30, 40, 50... etc.
        }
    }
    
    // The only remaining case is such that the last two digits of the 
    // number are both non-zero. In this case we can just cross off the
    // lat digit and try again. 
    
    if (x / 10 == 0)
    {
        return true;
    }
    else
    {
        return expressable(x / 10);
    }
}

/**
 * This starts the letter mapping program. It prompts the user for input
 * from the terminal, and outputs the result of the expressable function
 * to the terminal. 
 * No arguments
 * @returns 0 upon successful termination of program
 */
int main()
{
    cout << "Enter a number: ";
    unsigned int x;
    cin >> x;
    if (expressable(x))
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }
    return 0;
}
