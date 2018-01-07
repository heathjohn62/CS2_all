/**
 * @file debugging1.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2014-2015
 * @copyright This code is in the public domain.
 *
 * @brief An example of the utility of print statements in debugging.
 */


/**
 * There is a loop that will go until b = 0
 * If b is odd, a is added to x. 
 * At the end of every repetition, regardless of whether a was added or 
 * not, the value of a is multiplied by two (by adding a 0 to the end of 
 * its binary representation). If b is odd, b is subtracted by one. 
 * Then b is divided by 2. The division is valid because if b was odd, 
 * it is no longer odd after the subtraction. This last operation is 
 * done by removing the last digit of the binary representation of b. 
 * 
 * I explained the operators again in the code. If this code calculates 
 * something unique, rather than the arbitrary number x = 14790, I'm
 * not sure what it is. 
 */
#include <iostream>

using namespace std;

/**
 * @brief Does a thing.
 *
 * Does a thing, I dunno, you tell me.
 */
int main(int argc, char ** argv)
{
    // Much of the following is intentionally undocumented.
    // Part of the assignment is to figure out what is going on.
    // You may need to look up some operators!
    unsigned int a = 174, b = 85, x = 0;

    // This construct is known as a 'while loop'.
    // The interior of the loop is run if, and while,
    // the given condition is true.
    // The program proceeds past the loop if, and when,
    // the given condition is found to be false just before any iteration
    // of the interior of the loop.
    while (b != 0)
    {
        // This construct is known as a conditional statement
        // ('if' statement).
        // The interior of the statement is run exactly once in its entirety
        // if the given condition is found to be true.
        // Note that 'true' is defined as nonzero,
        // and 'false' is defined as zero.
        if ((b & 1) != 0) // This is the bitwise AND. 
        /**
         * This will compare each bit in the unsigned int, which is 
         * 4 bytes long, with the int 1, represented by ...00001
         * Essentially, if the last bit is 1 (the number is odd), then
         * the contents of the if will execute. 
         */
        {
            x += a;
            cout << "X is " << x << endl;
        }
        a <<= 1; // Adds a 0 to the end of the binary representation.
                 // In effect mutiplies a by 2.
        cout << "A is " << a << endl;
        b >>= 1; // Removes the last digit in the binary representation
                 // of b. 
        cout << "B is " << b << endl;
    }

    // Question for you now: so what is x anyway?
    // X is 14790
    //cout << sizeof(unsigned int) << endl; // unsigned int contains 4 bytes
    return 0;
}
