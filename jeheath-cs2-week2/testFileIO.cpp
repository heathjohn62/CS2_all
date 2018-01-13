/**
 * @file testFileIO.cpp
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2015
 * @copyright This code is in the public domain.
 *
 * @brief A brief example of file input.
 */

#include "fileio.hpp"
#include <vector>

using namespace std;
/**
 * @brief Read the file input and print out its contents
 *
 * Assumes that the file contains one integer per line.
 */
int main(int argc, char const *argv[])
{
    vector<int> v; 
    readFile(argv[1], v); // argv[1] is the filename
    print_vector(v);
    return 0;
}
