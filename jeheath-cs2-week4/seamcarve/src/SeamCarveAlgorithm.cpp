/*
 * SeamCarveAlgorithm.cpp
 * Defines the seam carving algorithm.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 */
#include <iostream>
#include "SeamCarveApp.hpp"

#define min(x, y)           ((x) < (y) ? (x) : (y))


/**
 * @brief Peforms the seam carving algorithm.
 *
 * @param smap 2-d saliency map with width `w` and height `h`; can be
 * indexed by `smap[i][j]`
 * NEXT YEAR, PLEASE BE MORE EXPLICIT ABOUT WHICH DIMENSION IS WHAT
 * 
 *
 * @param w Width of the saliency map
 *
 * @param h Height of the saliency map
 *
 * @return An array of the x-coordinates of the seam, starting from the top of
 * the image.
 */
unsigned int *DoSeamCarve(unsigned int **smap, 
                          int w, int h)
{
    // I'm a little wary of destroying the saliency map, so I'm going to
    // copy it to a new array instead of changing it directly.
    unsigned int **path = new unsigned int*[h];
    for (int i = 0; i < h; i++)
    {
        path[i] = new unsigned int[w];
    }
    for (int row = 0; row < h; row++)
    {
        for (int col = 0; col < w; col++)
        {
            // OK THIS TOOK ME FOREVER TO FIGURE OUT
            // Why would you format 2D arrays in column, row format???
            // Anyways, If I switched the row and column into path, 
            // everything works. 
            path[row][col] = smap[col][row]; 
        }
    }
    
    // Change the path array to have values reflect the total saliency
    // accumulated by the lowest saliency path to that pixel. 
    for (int row = 1; row < h; row++)
    {
        // left edge case
        path[row][0] += min(path[row - 1][0], path[row - 1][1]); 
        // main body
        for (int col = 1; col < w - 1; col++)
        {
            path[row][col] += min(min(path[row - 1][col - 1], 
                                      path[row - 1][col]), 
                                      path[row - 1][col + 1]);
        }
        // right edge case
        path[row][w - 1] += min(path[row - 1][w - 1], path[row - 1][w - 2]);
    }
    
    unsigned int *seam = new unsigned int[h];

    unsigned int minimum = path[h - 1][0];
    seam[h - 1] = 0;
    for (int col = 1; col < w; col++)
    {
        if (minimum > path[h - 1][col])
        {
            minimum = path[h - 1][col];
            seam[h - 1] = col;
        }
    }
    
    // Starting at the min on the bottom, we will work our way up.
    
    for (int i = h - 2; i >= 0; i--)
    {
        if (seam[i + 1] == 0) // last pixel was on the left edge
        {
            // pixel directly above is the min
            if (path[i][seam[i + 1]] < path[i][seam[i + 1] + 1])
            {
                seam[i] = seam[i + 1];
            }
            //pixel above and to the right is the min
            else
            {
                seam[i] = seam[i + 1] + 1;
            }
        }
        else if (seam[i + 1] == (unsigned int)w - 1) // last pixel on right edge
        {
            // pixel directly above is the min
            if (path[i][seam[i + 1]] < path[i][seam[i + 1] - 1])
            {
                seam[i] = seam[i + 1];
            }
            //pixel above and to the left is the min
            else
            {
                seam[i] = seam[i + 1] - 1;
            }
        }
        else // last pixel in middle
        {
            // pixel directly above the last is the min
            if (path[i][seam[i + 1]] < path[i][seam[i + 1] + 1] &&
                path[i][seam[i + 1]] < path[i][seam[i + 1] - 1])
            {
                seam[i] = seam[i + 1];
            }
            // pixel above and to the right is the min
            else if (path[i][seam[i + 1] + 1] < path[i][seam[i + 1] - 1])
            {
                seam[i] = seam[i + 1] + 1;
            }
            // pixel above and to the left is the min
            else if (path[i][seam[i + 1] + 1] >= path[i][seam[i + 1] - 1])
            {
                seam[i] = seam[i + 1] - 1;
            }
        }
    }
    // Wipe path array, and free memory
    for (int i = 0; i < h; i++)
    {
        delete[] path[i];
    }
    delete[] path;
    return seam;
}

