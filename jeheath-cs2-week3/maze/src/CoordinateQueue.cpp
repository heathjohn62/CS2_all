/**
 * @file CoordinateQueue.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for queue class that stores Coordinate objects.
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

#include "CoordinateQueue.hpp"

#define ANIMATION_DELAY     (25)

/**
 * @brief Initializes the queue.
 *
 * @param[in] app Reference to the MazeSolverApp; needed
 * to render moves.
 */
#ifndef TESTSUITE
CoordinateQueue::CoordinateQueue(class MazeSolverApp *app)
{
    this->app = app;
    init();
}
#else
CoordinateQueue::CoordinateQueue()
{
    init();
}
#endif

/**
 * @brief Initializes the queue (student-implemented).
 */
void CoordinateQueue::init()
{
   /* TODO: Write your initialization code here! */
   front = nullptr;
   rear = nullptr;
}

/**
 * @brief Deinitializes the queue.
 */
CoordinateQueue::~CoordinateQueue()
{
    deinit();
}

/**
 * @brief Deinitializes the queue (student-implemented).
 */
void CoordinateQueue::deinit()
{
    // For the stack implementation, it was sufficient to just pop the 
    // elements out. However, this is much less efficient when using the
    // queue, because it takes linear time to pop each element. We can
    // clear the entire list in linear time instead. 
    queueitem * temp;
    while (rear != nullptr)
    {
        temp = rear;
        rear = rear->next;
        delete temp;
    }
}

/**
 * @brief Enqueues an item by adding it to the bottom of the
 * queue.
 *
 * @param[in] c Coordinate to enqueue onto the queue.
 */
void CoordinateQueue::enqueue(Coordinate c)
{
    /* Do the operation. */
    do_enqueue(c);

#ifndef TESTSUITE
    /* Update the display, if necessary. */
    SDL_Delay(ANIMATION_DELAY);
    this->app->OnRender();
#endif
}

/**
 * @brief Do the actual enqueue operation (student-implemented).
 *
 * @param[in] c Coordinate to enqueue onto the queue.
 */
void CoordinateQueue::do_enqueue(Coordinate c)
{
    queueitem * q = new queueitem;
    q->c = c;
    if (front == nullptr) // Implies the list is empty
    {
        q->next = nullptr;
        front = q; // This item will be both the front and the end of 
        rear = q;  // the queue. 
    }
    else
    {
        q->next = rear;
        rear = q;
    }
}

/**
 * @brief Dequeues an item by removing it from the top.
 *
 * @return The dequeued Coordinate.
 */
Coordinate CoordinateQueue::dequeue()
{
    /* Do the operation. */
    return do_dequeue();
}

/**
 * @brief Do the actual dequeue operation (student-implemented).
 * Throws an exception if an empty list is dequeued. 
 * @return The dequeued Coordinate.
 */
Coordinate CoordinateQueue::do_dequeue()
{
    if (front == nullptr)
    {
        throw "ERROR. There is nothing to dequeue.";
    }
    
    Coordinate coord = front->c;
    
    if (rear->next == nullptr) // Single element queue
    {
        delete rear;
        rear = nullptr;
        front = nullptr;
    }
    else // multi element queue
    {
        queueitem * q = rear;
        queueitem * prev_q = q;
        // This is going to operate in linear time, but without a doubly
        // linked list, I don't think there's a better way to do it.
        while (q->next != nullptr)
        {
            prev_q = q;
            q = q->next;
        }
        front = prev_q;
        front->next = nullptr;
        delete q; 
    }
    return coord;
}

/**
 * @brief Returns the item at the front of the queue without
 * removing it.
 * Throws an exception if an empty list is peeked at. 
 * @return The first Coordinate in the queue.
 */
Coordinate CoordinateQueue::peek()
{
    if (front == nullptr)
    {
        throw "ERROR. You can't peek at an empty queue.";
    }
    return front->c;
}

/**
 * @brief Returns true is the queue is empty, false otherwise.
 *
 * @return Boolean indicating whether the queue is empty.
 */
bool CoordinateQueue::is_empty()
{
    return front == nullptr;
}

