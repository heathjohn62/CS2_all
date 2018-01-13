/**
 * @file fileio.cpp
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2015
 * @copyright This code is in the public domain.
 *
 * @brief A brief example of file input (implementation).
 */

#include "fileio.hpp"
#include <fstream>
using namespace std;
/**
 * @brief Reads the integers in file and fills nums with these integers.
 *
 * @param file: File containing integers, one per line.
 * @param nums: Vector to fill with the integers in file.
 *
 * Notice that the vector is passed by reference, so you should fill the vector
 * and not return anything from this function.
 */
void readFile(char const *file, vector<int> &nums)
{
    ifstream ifs; // This is an input file stream
    ifs.open(file, ifstream::in);
    int num;
    ifs >> num; // read the first number
    while(ifs.good()) // ifs.good() will be false if I have tried to 
                      // read a nonexistant number
    {
        nums.push_back(num); // adds number to vector
        ifs >> num;
    }
    ifs.close(); // Closes file
}
