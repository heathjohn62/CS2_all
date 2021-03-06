/**
 * @file philosophers.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief This is a warm-up exercise based on the famous "dining
 * philosophers" problem.
 *
 * @section License
 * Copyright (c) 2013-2014 California Institute of Technology.
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

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include "semaphore.hpp"

/**
 * @brief Number of philosophers; also number of forks available.
 */
#define NUMPHILS    (5) // original is 5

/**
 * @brief How long a philosopher needs to pick up a fork (in us).
 */
#define PICKUPTIME  (1000) // original is 1000

/**
 * @brief How long a philosopher needs to drop a fork (in us).
 */
#define DROPTIME    (1000) // original is 1000

/**
 * @brief How long a philosopher eats when he has both forks (in us).
 */
#define EATTIME     (1000000)// original is 1000000

/**
 * @brief How long to wait between display refreshes (in us).
 */
#define DISPLAYINTERVAL (16700) // original is 16700

#define LEFT        (0)
#define RIGHT       (1)

#define MSGRELEASE  (0)
#define MSGPICKUP   (1)

/**
 * @brief Returns the numeric ID of the philosopher immediately to
 * the left.
 */
#define IDLEFT(x)   ((x == 0) ? (NUMPHILS - 1) : (x - 1))

/**
 * @brief Returns the numeric ID of the philosopher immediately to
 * the right.
 */
#define IDRIGHT(x)  ((x == NUMPHILS - 1) ? (0) : (x + 1))

#define USAGE        ("Usage: philosophers -x, x = {g, w, t}\n" \
                      "  g = greedy solution (deadlock)\n" \
                      "  w = waiter solution\n" \
                      "  t = talking solution (Chandy)\n")


/**
 * @brief Encapsulates a "fork" (shared resource). This could be a
 * printer, hard drive, or any other resource that more than one
 * process might wish to use. Forks need not track which philosopher
 * is using them, just whether or not they are being used.
 */
class Fork
{
public:
    /**
     * @brief Initializes the fork.
     */
    Fork()
    {
        dirty = true;
        m = new std::mutex();
    }

    /**
     * @brief Deinitializes the fork.
     */
    ~Fork()
    {
        delete m;
    }

    /**
     * @brief Picks up this fork.
     *
     * @attention Student-implemented function.
     */
    void pick_up()
    {
        m->lock();
    }

    /**
     * @brief Releases this fork.
     *
     * @attention Student-implemented function.
     */
    void release()
    {
        m->unlock();
    }

    /**
     * @brief Returns the state of this fork.
     *
     * @return `true` if the fork is dirty, `false` otherwise.
     */
    bool is_dirty()
    {
        return dirty;
    }

    /**
     * @brief Sets the state of this fork.
     *
     * @param[in] d The new state of the fork: `true` for dirty, `false`
     * for clean.
     */
    void set_dirty(bool d)
    {
        dirty = d;
    }

private:
    /**
     * @brief Describes the current state of the fork.
     */
    bool dirty;
    
    /**
     * @brief Mutex that can block use of the fork
     */
     std::mutex * m;
};


/**
 * @brief Encapsulates a "philosopher", which represents a process in
 * this analogy. Philosophers cannot communicate with one another. When
 * a philosopher is not "eating" (working with a shared resource), he is
 * "thinking" (performing other background tasks). Philosophers require
 * both a left and right fork in order to eat.
 */
class Philosopher
{
public:
    Philosopher(Fork *lf, Fork *rf, int i)
    {
        fork[LEFT] = lf;
        fork[RIGHT] = rf;

        hasfork[LEFT] = false;
        hasfork[RIGHT] = false;

        eating = false;
        id = i;
    }

    ~Philosopher()
    {
        
    }

    void pickup_fork(int which)
    {
        usleep(PICKUPTIME);

        fork[which]->pick_up();
        hasfork[which] = true;
    }

    void release_fork(int which)
    {
        usleep(DROPTIME);

        fork[which]->release();
        hasfork[which] = false;
    }

    void eat()
    {
        eating = true;
        usleep(EATTIME);
        eating = false;

        fork[LEFT]->set_dirty(true);
        fork[RIGHT]->set_dirty(true);
        times_eaten++;
    }
    
    int get_times_eaten()
    {
        return times_eaten;
    }
    
    bool has_fork(int which)
    {
        return hasfork[which];
    }

    bool is_eating()
    {
        return eating;
    }

    int get_id()
    {
        return id;
    }

    Fork *get_fork(int which)
    {
        return fork[which];
    }
    
    /**
      * @brief Recieves a request for the philosopher's right fork if
      * the parameter is true, and the left fork otherwise.
      */
     void recieve_request(bool right)
     {
         if (right)
         {
             r_f_requested = true;
         }
         else
         {
             l_f_requested = true;
         }
     }
     
     /**
      * @brief
      * Returns whether one of their forks has been requested (true for
      * right fork, false for left fork)
      */
      bool requested (bool right)
      {
          if (right)
          {
              return r_f_requested;
          }
          else
          {
              return l_f_requested;
          }
      }
      
protected:
    /**
     * @brief These variables keep track of whether one of their forks 
     * has been requested. 
     */
    bool l_f_requested = false;
    bool r_f_requested = false;

    Fork *fork[2];
    bool hasfork[2], eating;
    int id;
    int times_eaten; // Used to determine if some philosophers are starving
};

/**
 * @brief Array of all philosophers in the system. This can be used
 * by any philosophers to talk to others (Chandy solution).
 */
Philosopher *phils[NUMPHILS];

class TalkingPhilosopher : public Philosopher
{
public:
    TalkingPhilosopher(Fork *lf, Fork *rf, int i) : Philosopher(lf, rf, i)
    {

    }
    
    /**
     * @brief Sends their fork to the philosopher on their right if the
     * parameter is true, and to the philosopher on their left otherwise.
     */
    void send_fork(bool right)
    {
        if (right)
        {
            fork[RIGHT]->set_dirty(false);
            release_fork(RIGHT);
            r_f_requested = false;
            phils[(id + 1) % NUMPHILS]->pickup_fork(LEFT);
        }
        else
        {
            fork[LEFT]->set_dirty(false);
            release_fork(LEFT);
            l_f_requested = false;
            phils[(id + NUMPHILS - 1) % NUMPHILS]->pickup_fork(RIGHT);
        }
    }
    
    /**
     * @brief Requests a fork from their right neighbor if parameter is 
     * true, left neighbor otherwise. 
     */
     void request_fork(bool right)
     {
         if (right)
         {
             // The philosopher on their right will recieve a request
             // for their left fork.
             phils[(id + 1) % NUMPHILS]->recieve_request(false);
         }
         else
         {
             // The philosopher on their left will recieve a request for
             // their right fork. 
             phils[(id + NUMPHILS - 1) % NUMPHILS]->recieve_request(true);
         }
     }
};



/**
 * @attention Student-implemented function
 */
void greedy(Philosopher *phil)
{
    while (true)
    {
        phil->pickup_fork(LEFT);
        phil->pickup_fork(RIGHT);

        phil->eat();

        phil->release_fork(RIGHT);
        phil->release_fork(LEFT);
    }
}


/**
 * @attention Student-implemented function
 * @param philosopher that wants to eat
 * @param table Sephamore denoting the number of empty seats at the 
 * table. Four philosophers may sit at a time. 
 * 
 * I was curious whether this program would lead some philosophers to eat
 * more than others. The answer is no. I edited some of the core functions 
 * so that the final eating count for each philosopher is printed to 
 * "log.txt" in this directory. After speeding up the philosophers to 
 * get swifter data, these meals were printed to log in one minute. 
0: 11068
1: 11595
2: 11148
3: 11215
4: 11811
 */
void waiter(Philosopher * p, Semaphore * table)
{
    while (true)
    {
        table->dec(); //sit down
        p->pickup_fork(LEFT);
        p->pickup_fork(RIGHT);

        p->eat();

        p->release_fork(RIGHT);
        p->release_fork(LEFT);
        table->inc(); //stand up
    }
    
}


/**
 * @attention Student-implemented function
 * 
 * @brief Implementation of the talking philosopher's algorithm. 
 * 
 * This one is much less sporadic than the waiter algorithm, and is
 * completely even across the philosophers. After running it at high 
 * speeds for a few minutes, this was the result in the log:
 * 
0: 5973
1: 5972
2: 5972
3: 5973
4: 5973

 */
void talking(Philosopher *p)
{
    TalkingPhilosopher * phil = (TalkingPhilosopher *)p;
    while (true)
    {
        // If phil doesnt have a fork, they will request it and then take it
        if (!phil->has_fork(LEFT))
        {
            phil->request_fork(false);
        }
        if (!phil->has_fork(RIGHT))
        {
            phil->request_fork(true);
        }
        
        if (phil->has_fork(RIGHT) && phil->has_fork(LEFT))
        {
            phil->eat();
        }
        
        // If the fork has been requested and it is dirty, send it.
        if (phil->requested(true) && phil->has_fork(RIGHT) &&
            phil->get_fork(RIGHT)->is_dirty())
        {
            phil->send_fork(true);
        }
        if (phil->requested(false) && phil->has_fork(LEFT) &&
        phil->get_fork(LEFT)->is_dirty())
        {
            phil->send_fork(false);
        }
        
    }
}


/**
 * @brief Renders an ASCII representation of the philosophers and their
 * forks, indicating which forks are taken and which philosophers are
 * eating.
 */
void update_ascii_display()
{
    while (true)
    {
        erase();

        /* First line: Philosophers and unused forks? */
        for (int i = 0; i < NUMPHILS; i++)
        {
            Philosopher *p = phils[i];
            Philosopher *q = phils[IDLEFT(i)];

            if ((p->has_fork(LEFT) == false) &&
            (q->has_fork(RIGHT) ==  false))
                printw("     F     ");
            else
                printw("           ");

            printw("Phil%i", i);
        }

        printw("\n");

        /* Second line: Which philosophers have which forks? */
        for (int i = 0; i < NUMPHILS; i++)
        {
            Philosopher *p = phils[i];

            printw("           ");

            if (p->has_fork(LEFT) == true)
                if (p->get_fork(LEFT)->is_dirty() == true)
                    printw("L*");
                else
                    printw("L ");
            else
                printw("  ");

            printw(" ");

            if (p->has_fork(RIGHT) == true)
                if (p->get_fork(RIGHT)->is_dirty() == true)
                    printw("R*");
                else
                    printw("R ");
            else
                printw("  ");
        }

        printw("\n ");

        /* Third line: Which philosophers are eating? */
        for (int i = 0; i < NUMPHILS; i++)
        {
            Philosopher *p = phils[i];

            printw("         ");

            if (p->is_eating() == true)
                printw("(munch)");
            else
                printw("       ");
        }
        
        // How many times each philosopher got to eat is printed to a log file
        std::ofstream myfile;
        myfile.open("log.txt");
        for (int i = 0; i < NUMPHILS; i++)
        {
            Philosopher *p = phils[i];
            myfile << i << ": " << p->get_times_eaten() << "\n";
        }
        myfile.close();
        
        
        /* Static delay. */
        refresh();
        usleep(DISPLAYINTERVAL);
    }
}


int main(int argc, char *argv[])
{
    Fork *forks = new Fork[NUMPHILS];
    std::thread **t = new std::thread *[NUMPHILS];

    if (argc != 2)
    {
        std::cout << USAGE << std::endl;
        return -1;
    }    
    if (strcmp(argv[1], "-g") == 0)
    {
        /* Greedy solution (guaranteed deadlock). */
        for (int i = 0; i < NUMPHILS; i++)
        {
            int j = (i + 1) % NUMPHILS;
            phils[i] = new Philosopher(&forks[i], &forks[j], i);
            t[i] = new std::thread(greedy, phils[i]);
        }
    }
    else if (strcmp(argv[1], "-w") == 0)
    {
        /* Waiter solution. */
        Semaphore * table = new Semaphore(4);
        for (int i = 0; i < NUMPHILS; i++)
        {
            int j = (i + 1) % NUMPHILS;
            phils[i] = new Philosopher(&forks[i], &forks[j], i);
            t[i] = new std::thread(waiter, phils[i], table);
        }
    }
    else if (strcmp(argv[1], "-t") == 0)
    {
        /* Talking philosophers (Chandy solution). */
        for (int i = 0; i < NUMPHILS; i++)
        {
            int j = (i + 1) % NUMPHILS;
            phils[i] = new TalkingPhilosopher(&forks[i], &forks[j], i);

            TalkingPhilosopher *phil = (TalkingPhilosopher *) phils[i];

            if (i < IDLEFT(i))
            {
                phil->pickup_fork(LEFT);
            }

            if (i < IDRIGHT(i))
            {
                phil->pickup_fork(RIGHT);
            }
        }

        for (int i = 0; i < NUMPHILS; i++)
            t[i] = new std::thread(talking, phils[i]);
    }
    else
    {
        std::cout << USAGE << std::endl;
        return -1;
    }
    

    /* Enter ncurses mode and begin an ASCII update loop. */
    initscr();
    std::thread *update = new std::thread(update_ascii_display);
    update->join();

    /* Join all running threads. */
    for (int i = 0; i < NUMPHILS; i++)
    {
        t[i]->join();
    }
    
    /* End ncurses mode. */
    endwin();

    // Clean up memory.
    
    delete update;
    for (int i = 0; i < NUMPHILS; i++)
    {
        delete t[i];
    }
    delete[] t;
}
