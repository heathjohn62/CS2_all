/**
 * @file DepthFirstSolver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for maze solver that implements depth-first search.
 *
 * @section License
 * Copyright (c) 2014-2015 California Institute of Technology.
 * All rights reserved.
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
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the California Institute of Technology.
 *
 */

#include "DepthFirstSolver.hpp"

/**
 * @brief Initializes the solver.
 *
 * @param[in] app Pointer to the main MazeSolverApp class.
 */
DepthFirstSolver::DepthFirstSolver(class MazeSolverApp *app)
{
    stack = new CoordinateStack(app);
    init();
}

/**
 * @brief Initializes the solver (student-implemented).
 */
void DepthFirstSolver::init()
{
    // Initialize visited to ensure the board is seen as unexplored at
    // the start
    list = vector<Coordinate>();
    for (unsigned int i = 0; i < WIDTH; i++)
    {
        for (unsigned int j = 0; j < HEIGHT; j++)
        {
            visited[i][j] = false;
        }
    }
}

/**
 * @brief Deinitializes the solver.
 */
DepthFirstSolver::~DepthFirstSolver()
{
    delete stack;
    deinit();
}


/**
 * @brief Deinitializes the solver (student-implemented).
 */
void DepthFirstSolver::deinit()
{
    // I did not dynamically allocate any memory, so none needs to be freed
}

/**
 * @brief Solves the maze given by `maze`.
 *
 * @param[in] maze MazeGrid object that stores the maze to be
 * solved.
 */
void DepthFirstSolver::solve(MazeGrid *maze)
{
    
    Coordinate position = Coordinate(MAZE_START_X, MAZE_START_Y);
    stack->push(position);
    list.push_back(position);
    int moves = 0;
    while(!stack->is_empty())
    {
        position = stack->peek(); // Updates position 
        visited[position.x][position.y] = true; // Marks position as visited
        
        if (position.x == MAZE_END_X && position.y == MAZE_END_Y)
        {
            return; // We have found the end!!
        }
    
        moves = maze->get_possible_moves(position.x, position.y);
        
        // A single coordinate is pushed onto the stack if it is in the 
        // avaliable moves, and it has not yet been visited. 
        if ((moves & E) && !(visited[position.x + 1][position.y]))
        {
            stack->push(Coordinate(position.x + 1, position.y));
            list.push_back(Coordinate(position.x + 1, position.y));
        }
        else if ((moves & W) && !(visited[position.x - 1][position.y]))
        {
            stack->push(Coordinate(position.x - 1, position.y));
            list.push_back(Coordinate(position.x - 1, position.y));
        }
        else if ((moves & S) && !(visited[position.x][position.y + 1]))
        {
            stack->push(Coordinate(position.x, position.y + 1));
            list.push_back(Coordinate(position.x, position.y + 1));
        }
        else if ((moves & N) && !(visited[position.x][position.y - 1]))
        {
            stack->push(Coordinate(position.x, position.y - 1));
            list.push_back(Coordinate(position.x, position.y - 1));
        }
        else
        {
            stack->pop();
            list.pop_back();
        }
        
    }
    
}

/**
 * @brief Retrieves the current path through the maze.
 *
 * @return Vector storing the current path through the maze.
 */
vector<Coordinate> DepthFirstSolver::get_path()
{
    // The list variable mirrors the stack, and can be accessed without
    // being destroyed

    return list;
}

