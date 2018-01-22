/**
 * @file BreadthFirstSolver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for maze solver that implements breadth-first search.
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

#include "BreadthFirstSolver.hpp"

/**
 * @brief Initializes the solver.
 *
 * @param[in] app Pointer to the main MazeSolverApp class.
 */
BreadthFirstSolver::BreadthFirstSolver(class MazeSolverApp *app)
{
    queue = new CoordinateQueue(app);
    init();
}

/**
 * @brief Initializes the solver (student-implemented).
 */
void BreadthFirstSolver::init()
{
    position = Coordinate(MAZE_START_X, MAZE_START_Y);
    for (unsigned int i = 0; i < WIDTH; i++)
    {
        for (unsigned int j = 0; j < HEIGHT; j++)
        {
            visited[i][j].visited = false;
            visited[i][j].from = Coordinate(-1, -1);
        }
    }
}

/**
 * @brief Deinitializes the solver.
 */
BreadthFirstSolver::~BreadthFirstSolver()
{
    delete queue;
    deinit();
}

/**
 * @brief Deinitializes the solver (student-implemented).
 */
void BreadthFirstSolver::deinit()
{
    // I did not dynamically allocate memory, so nothing must be freed
}

/**
 * @brief Solve the maze given by `maze`.
 *
 * @param[in] maze MazeGrid object that stores the maze to be
 * solved.
 * 
Enqueue the first coordinate

while queue is not empty:
    Mark the current position as visited

    if current position is end coordinate:
        Stop the search
    else:
        Enqueue all available moves
 */
void BreadthFirstSolver::solve(MazeGrid *maze)
{
    queue->enqueue(position);
    int moves = 0;
    while (!queue->is_empty())
    {
        visited[position.x][position.y].visited = true;
        
        if (position.x == MAZE_END_X && position.y == MAZE_END_Y)
        {
            return; // We have found the end!!
        }
        
        moves = maze->get_possible_moves(position.x, position.y);
        // If a move is valid and hasn't been visited before, it 
        // is added to the queue. This can result in multiple additions
        // per loop cycle. 
        if ((moves & E) && !(visited[position.x + 1][position.y].visited))
        {
            // update visited to keep track of history
            visited[position.x + 1][position.y].from = position;
            // add coordinate to queue
            queue->enqueue(Coordinate(position.x + 1, position.y));
        }
        if ((moves & W) && !(visited[position.x - 1][position.y].visited))
        {
            visited[position.x - 1][position.y].from = position;
            queue->enqueue(Coordinate(position.x - 1, position.y));
        }
        if ((moves & S) && !(visited[position.x][position.y + 1].visited))
        {
            queue->enqueue(Coordinate(position.x, position.y + 1));
            visited[position.x][position.y + 1].from = position;
        }
        if ((moves & N) && !(visited[position.x][position.y - 1].visited))
        {
            visited[position.x][position.y - 1].from = position;
            queue->enqueue(Coordinate(position.x, position.y - 1));
        }
        position = queue->dequeue();
    }
}

/**
 * @brief Retrieves the current path through the maze.
 *
 * @return Vector storing the current path through the maze.
 */
vector<Coordinate> BreadthFirstSolver::get_path()
{
    vector<Coordinate> list;
    Coordinate pos = position;
    bool found = false;
    while (!found)
    {
        list.push_back(pos);
        pos = visited[pos.x][pos.y].from;
        if (pos.x == MAZE_START_X && pos.y == MAZE_START_Y)
        {
            found = true;
        }
    }
    list.push_back(Coordinate(MAZE_START_X, MAZE_START_Y));

    return list;
}

