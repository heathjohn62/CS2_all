/**
 * @file testsuite.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Performs tests of the CoordinateQueue and CoordinateStack classes.
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

#include <cstdio>
#include "CoordinateStack.hpp"
#include "CoordinateQueue.hpp"

int main()
{
    Coordinate c;
    CoordinateQueue *queue = new CoordinateQueue();
    CoordinateStack *stack = new CoordinateStack();
    cout << "First we will test the Coordinate Stack implementation" 
         << endl;
    try
    {
        stack->push(Coordinate(1,2));
        stack->push(Coordinate(3,3));
        cout << "Anticipated: (3, 3)    Result: ";
        stack->peek().printCoord();
        cout << "Anticipated: (3, 3)    Result: ";
        stack->pop().printCoord();
        cout << "Anticipated: (1, 2)    Result: ";
        stack->pop().printCoord();
        cout << "Anticipated peek error" << endl;
        stack->peek().printCoord(); // Should print error
    }
    catch (const char* msg)
    {
        cout << msg << endl;
    }
    try
    {
        cout << "Anticipated pop error" << endl;
        stack->pop().printCoord(); // should print error
    }
    catch (const char* msg)
    {
        cout << msg << endl;
    }
    
    cout << "Expected: Empty    Actual: ";
    if (stack->is_empty())
    {
        cout << "Empty" << endl;
    }
    else
    {
        cout << "Non-empty" << endl;
    }
    for (int i = 0; i < 8000000; i++)
    {
        stack->push(Coordinate(5,5)); 
    }
    // This line will let me check if the destructor is working properly
    // If so, I should be able to end the program with a non-empty stack 
    // and still avoid memory leaks. 
    
    cout << "Expected: Non-empty    Actual: ";
    if (stack->is_empty())
    {
        cout << "Empty" << endl;
    }
    else
    {
        cout << "Non-empty" << endl;;
    }
    
    delete stack;
    
    cout << "Now we will test the coordinate queue implementation." 
         << endl;

    try
    {
        queue->enqueue(Coordinate(6,6));
        queue->enqueue(Coordinate(7,7));
        cout << "Expected: (6, 6)    Actual: ";
        queue->dequeue().printCoord();
        cout << "Expected: (7, 7)    Actual: ";
        queue->peek().printCoord();
        cout << "Expected: (7, 7)    Actual: ";
        queue->dequeue().printCoord();
        cout << "Expected peek error." << endl;
        queue->peek().printCoord();
    }
    catch (const char* msg)
    {
        cout << msg << endl;
    }
    try
    {
        cout << "Expected dequeue error." << endl;
        queue->dequeue().printCoord();
    }
    catch (const char* msg)
    {
        cout << msg << endl;
    }
    
    cout << "Expected: Empty    Actual: ";
    if (queue->is_empty())
    {
        cout << "Empty" << endl;
    }
    else
    {
        cout << "Non-empty" << endl;
    }
    
    // Now to check destructor
    queue->enqueue(Coordinate(7,6));
    queue->enqueue(Coordinate(7,5));
    queue->enqueue(Coordinate(7,4));
    // Valgrind suggests the destructor is effective
    
    cout << "Expected: Non-empty    Actual: ";
    if (queue->is_empty())
    {
        cout << "Empty" << endl;
    }
    else
    {
        cout << "Non-empty" << endl;
    }
    
    delete queue;
    

    return 0;
}
/**
 * Tests pass. Errors are printed to the terminal when they should be, 
 * and there are no memory leaks. 
 */
