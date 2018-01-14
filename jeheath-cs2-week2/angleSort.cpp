/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief An example of sorting (x, y) pairs by angle.
 *
 */
#include "structs.hpp"
#include <vector>
using namespace std;

/**
 * This is a revised version of the swapping function, such that it swaps
 * two vectors of pointers to tuples and doubles, in place. 
 * @param i one index to be swapped
 * @param j the second index to be swapped
 * @param v the vector of doubles, passed by reference
 * @param points the vector of tuples, passed by reference
 * @returns nothing
 */
void swap_elements(int i, int j, vector<double> &v, vector<Tuple*> &points)
{
    double temp = v[i];
    v[i] = v[j];
    v[j] = temp;
    Tuple * point = points[i];
    points[i] = points[j];
    points[j] = point;
}

/**
 * This is a revised in-place quicksort algorithm that sorts the pair of 
 * vectors of angles and tuples based on angle. 
 * @param points A vector holding pointers to points (in a tuple),
 * to be sorted
 * @param angles A vector holding angles as doubles, to be sorted
 * @param left 
 * @returns nothing
 */
void sort(vector<Tuple*> &points, vector<double> &angles,
          int left, int right)
{
    if (right <= left)
    {
        return;
    }
    else
    {
        // choose pivot to be left element
        int pivot = left;
        for (int i = left + 1; i <= right; i++)
        {
            if ((angles[i]) < (angles[pivot]))
            {
                swap_elements(pivot, pivot + 1, angles, points);
                pivot++;
                if (pivot != i)
                {
                    swap_elements(pivot - 1, i, angles, points);
                }
            }
        }
        sort(points, angles, left, pivot - 1);  // Recursively sort 
        sort(points, angles, pivot + 1, right); // about the pivot.
    }
}

int main(int argc, char const *argv[])
{
    vector<double> angles {4.2, 2.8, 1.4, 5.0, 3.3};
    vector<Tuple*> points;
    // Print the initial points and angles
    for (unsigned int i = 0; i < angles.size(); ++i)
    {
        points.push_back(new Tuple(i, i));
    }
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        cout << *i << endl;
    }

    // Now sort them with respect to angle (points[i] corresponds to angle[i])

    /** THIS IS THE ONLY LINE OF THE MAIN LOOP YOU NEED TO MODIFY. */
    sort(points, angles, 0, angles.size() - 1);
    /** REPLACE THE LINE ABOVE WITH A CALL TO YOUR SORTING FUNCTION. */

    // and print out the new points and angles
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        cout << *i << endl;
    }

    // Don't want to leak memory...
    // Either of the below implementations works
    // for (std::vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    // {
    //     delete (*i);
    // }
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        delete points[i];
    }
    return 0;
}
