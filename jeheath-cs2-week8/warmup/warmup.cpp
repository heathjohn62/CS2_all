
#include <iostream>

using namespace std;

/**
 * Finds the element of the list that is only included once, and 
 * prints it to the terminal. 
 * 
 * @param A series of integers to be inputted as command line arguments
 * @returns 0 upon successful completion
 */
int main(int argc, char ** argv)
{
    if (argc <= 1)
    {
        cout << "No numbers were given as input. " << endl;
        return -1;
    }
    // Create array to be searched
    int arr[argc - 1];
    for (int i = 1; i < argc; i++)
    {
        arr[i - 1] = atoi(argv[i]);
    }
    
    int num_of_interest = 0x00000000;
    for(int i = 32; i > 0; i--)
    {
        num_of_interest = num_of_interest << 1;
        // We will start by summing the ith bit of each number in the array. 
        int bit_sum = 0;
        for (int j = 0; j < argc - 1; j++)
        {
            // Add the ith bit of the jth entry
            bit_sum += ((1 << (i - 1)) & arr[j]) >> (i - 1);
        }
        num_of_interest += bit_sum % 2;
    }
    cout << "The non-repeated number is: " << num_of_interest << endl;
    return 0;
}
