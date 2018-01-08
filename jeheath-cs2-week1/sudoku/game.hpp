/**
 * @author John Heath
 * @date 1.7.18
 * CS2 Assignment 1 Part 3
 */
#ifndef game_hpp
#define game_hpp
#include <stdio.h>
#include <forward_list>
#include <string>
#include <iostream>

using namespace std;

class Game
{
private:
    forward_list<char *> moves;
    Grid grid;
public:
    Game();
    Game(string filename);
    void getMove();
    void removeMove(char *);
    bool inMoves(char *);
    void Run();
    void wipe_moves();
};

#endif /* game_hpp */
