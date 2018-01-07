/**
 * @file arrays1.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2014-2015
 * @copyright This code is in the public domain.
 *
 * @brief An array example.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

#define TEST_SIZE 100000
/**
 * 100k actually runs in a reasonable time, and it seems that I can go 
 * up to 10 million without running out of memory (but bubble sort takes
 * forever). 100 million causes the program to crash. 
 */

using namespace std;

/**
 * @brief Computes and returns the maximum value in an array
 * 
 * @param arr The given array to be analyzed
 * @param n An int indicating the size of the array
 * @return Returns the maximum of the array
 */
int arr_max(int * arr, int n)
{
    int max = *arr;
    for (int i = 1; i < n; i ++)
    {
        if (max < *(arr + i))
        {
            max = *(arr + i);
        }
    }
    return max;
}
/**
 * @brief Calculates and returns the arithmetic mean of all values in 
 * the argument array.
 * @param arr The array to be analyzed
 * @param n The size of the given array
 * @return Returns the arithemtic mean of the array as a double.
 */
double arithmetic_mean(int * arr, int n)
{
    long double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += *(arr + i);
    }
    return sum / (double) n;
}

/**
 * @brief Accepts an array of integers, and orders the numbers from 
 * smallest to largest. No return value. Prints the array to terminal.
 * 
 * If I remember correctly, I believe this algorithm is an implementation
 * of bubble sort. An imbedded loop is used, but every repetition calls 
 * a smaller loop, because the last n numbers are garanteed to be ordered
 * after n repititions. 
 * 
 * @param arr The array to be ordered
 * @param n The size of the array to be ordered
 */
 void order_array(int * arr, int n)
 {
     for (int i = n - 1; i >= 0; i--) 
     {
         for (int j = 0; j < i; j++)// Imbedded loop
         {
             if (*(arr + j) > *(arr + j + 1)) 
             {
                 int temp = *(arr + j);  // Switches the values of arr[j] 
                 *(arr + j) = *(arr + j + 1);// and arr[j + 1]. 
                 *(arr + j + 1) = temp;
             }
         }
     }
 }
 /**
  * @brief Accepts an array and its length and prints the contents to 
  * the terminal.
  * @param arr The array to be printed.
  * @param n The length of the array to be printed. 
  */
 void print_arr(int * arr, int n)
 {
     cout << "[";
     for (int i = 0; i < n; i++)
     {
        cout << *(arr + i);
        if (i != n - 1)
        {
            cout << ", ";
        }
     }
     cout << "]" << endl;
 }
 
/**
 * @brief Sets up and runs an array example.
 */
int main(int argc, char ** argv)
{

    /*-------- CHANGE NOTHING BELOW THIS LINE FOR PART 1 --------*/
    int * test_values = new int[TEST_SIZE]; // dynamically allocates 
                                            // memory for array in heap
    int real_size;

    // seed the PRNG
    srand(time(nullptr));

    // initialize the test array to garbage
    for (int i = 0; i < TEST_SIZE; i++)
    {
        test_values[i] = rand();
    }

    // determine a real size
    real_size = TEST_SIZE - (rand() % 20);

    // initialize the meaningful part of the test array to random numbers
    // all of which are less than one million
    for (int i = 0; i < real_size; i++)
    {
        test_values[i] = rand() % 1000000;
    }
    /*-------- CHANGE NOTHING ABOVE THIS LINE FOR PART 1 --------*/

    // The following just prints out the array in a readable format
    print_arr(test_values, real_size);
    // Here there is a test call to each function
    cout << "The max is: " << arr_max(test_values, real_size) << endl;
    cout << "The mean is: " << arithmetic_mean(test_values, real_size)
         << endl;
    cout << "The ordered array is: " << endl;
    order_array(test_values, real_size); // This function edits the 
    // dynamically allocated array, so it doesn't need a "cout"
    print_arr(test_values, real_size);
    delete[] test_values; // deallocates the memory for the array
    return 0;
    
}
