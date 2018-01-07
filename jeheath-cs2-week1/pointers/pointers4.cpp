/**
 * @file pointers4.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2015
 * @copyright This code is in the public domain.
 *
 * @brief Pointer-fu Exercise 4: Typecasting vs. address-of
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/**
 * @brief performs type castings
 */
int main(int argc, char *argv[])
{
    int a = 5, *b;
    void *c;

    // Now make `b` point to `a`.
    b = &a;
    // I changed this from (int *), a cast, to the address operator (&).
    // If the intention is to make b point to a, the address operator 
    // should be used. Casting will have a different effect. 
    /***** CHANGE NOTHING BELOW THIS LINE *****/
    cout << "The value pointed by `b` is " << *b;
    /***** CHANGE NOTHING ABOVE THIS LINE *****/

    // Allocate an array of 10 ints.
    c = malloc(10 * sizeof(int));

    // Get the address of the array.
    b = (int *) c;
    /**
     * I deleted the & symbol before c. This is because c was already a 
     * pointer, and thus was already the address of the array--it is 
     * different to get the address of the pointer. It is valid to cast
     * the void pointer as a pointer to an int. 
     */
    /***** CHANGE NOTHING BELOW THIS LINE *****/
    b[2] = 5;
    /***** CHANGE NOTHING ABOVE THIS LINE *****/

    return 0;
}
