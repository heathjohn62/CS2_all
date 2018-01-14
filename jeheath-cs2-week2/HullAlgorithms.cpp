/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (implementation).
 *
 */
#include "HullAlgorithms.hpp"

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to HullAlgorithms.hpp if you write a helper function!
 *
 * Our reference implementation has four helper functions and the function(s)
 * copied over from angleSort.cpp.
 */

/**
 * This is the implementation of the gift wrap algorithm. It adds points
 * to a convex hull, given an initial set of points. 
 * 
 * @param app The complex hull application
 * @param points A vector containing pointers to tuples that represent 
 * points in R^2. 
 * @returns nothing
 * 
 * Outline:
 * Find leftmost point
 * add it to the hull
 * done = false
 * old_point = min
 * while not done:
 *      added = false
 *      for points and while not added:
 *          found problem = false
 *          update new_point 
 *          if new_point isn't old_point:
 *              if the point forms a left turn with any other point:
 *                  found problem = true
 *                  break
 *          if no problem:
 *              add point to hull
 *              added = true
 *              old point = new point
 *              if added min, done= true
 */
 
void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app)
{
    // Find the leftmost point.
    unsigned int min = leftmost(points);
    // Add the point to the hull
    app->add_to_hull(points[min]);
    bool done = false;
    Tuple * old_point = points[min];
    Tuple * new_point;
    while (!done)
    {
        bool added = false;
        for (unsigned int i = 0; (i < points.size()) && !added; i++)
        {
            bool found = false;
            new_point = points[i];
            // The point is ignored if it is the same point
            if ((new_point->x != old_point->x) || 
                (new_point->y != old_point->y))
            {
                for (unsigned int j = 0;
                    (j < points.size()) && !found; j++)
                {
                    if (left_turn(*old_point, *new_point, *points[j]) == 1)
                    {
                        found = true; // If a left turn is found, it
                                      // means that the point at index
                                      // i cannot be in the hull.
                        break;
                    }
                }
                if (!found) // indicates no left turns
                {
                    app->add_to_hull(points[i]); // add to hull
                    old_point = new_point;
                    added = true;
                    if (i == min) // true if we added the first point in 
                                  // the hull, forming a polygon.
                    {
                        done = true;
                    }
                }
            }
        }
    }
}


 /**
 * TODO: Implement this function.
 */

void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app)
{
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        app->add_to_hull(points[i]);
    }
    app->add_to_hull(points[0]);
}


/**
 * This is a helper function to determine if three points, as ordered, 
 * make a left turn when connected by lines. 
 * @param p_1 the first point in 2-D space, represented by a tuple
 * @param p_2 the second point in 2-D space, represented by a tuple
 * @param p_3 the third point in 2-D space, represented by a tuple
 * @returns 1 if left, 0 if right, -1 if linear, -2 if duplicate points. 
 */
int left_turn(Tuple p_1, Tuple p_2, Tuple p_3)
{
    // These are displacement vectors. Notice that the y-displacement 
    // is reversed to account for the negative y. 
    Tuple d_1 = Tuple(p_2.x - p_1.x, p_1.y - p_2.y);
    Tuple d_2 = Tuple(p_3.x - p_2.x, p_2.y - p_3.y);
    
    // If the cross product is positive, it was a left turn. 
    int cross_product = d_1.x * d_2.y - d_1.y * d_2.x;
    if (cross_product > 0)
    {
        return 1; // left
    }
    else if (cross_product < 0)
    {
        return 0; // right
    }
    // checks to see if there is actual displacement
    else if ((d_1.x != 0 || d_1.y != 0) && (d_2.x != 0 || d_2.y != 0))
    {
        return -1; // linear
    }
    else
    {
        return -2; // duplicate points
    }
}

/**
 * Finds and returns the index of the leftmost point in the vector of 
 * tuples it is passed. 
 * @param points A vector of tuples that represent points in R^2
 * @returns the unsigned integer that holds the index of the leftmost 
 * point within the vector points. 
 */
unsigned int leftmost(vector<Tuple*> points)
{
    unsigned int min = 0;
    for (unsigned int i = 1; i < points.size(); ++i)
    {
        if (points[i]->x < points[min]->x)
        {
            min = i;
        }
    }
    return min;
}

/**
 * This is a revised version of the swapping function, such that it swaps
 * two vectors of pointers to tuples and doubles, in place. 
 * @param i one index to be swapped
 * @param j the second index to be swapped
 * @param v the vector of doubles, passed by reference
 * @param points the vector of tuples, passed by reference
 * @returns nothing
 */
void swap_elements(int i, int j, vector<double> &v, 
                   vector<Tuple*> &points)
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

