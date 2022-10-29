#ifndef GAME_H
#define GAME_H
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include <time.h>
#include<iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#include <unistd.h>
#include "Board.h"

class Game
{
private:
    Board board ;
    Player player1 =  Player(1,true,true);
    Player player2 =  Player(2,false,false);
    bool pause ;
    bool finished ;
    bool computerWon;
    bool computerTurn;


public:
    Game()
    {
        this->pause = false;
        this->finished =false;
        this->computerWon = false;
        this->computerTurn = false;
    }


    Board& getBoard()
    {
        return this->board;
    }

    void setPause(bool stat)
    {
        this->pause = stat;
    }

    bool isPaused()
    {
        return this->pause;
    }

    void setFinished(bool stat)
    {
        this->finished = stat;
    }

    bool isFinished(bool stat)
    {
        return this->finished;
    }

    void setComputerWon(bool stat)
    {
        this->computerWon = stat;
    }

    bool isComputerWon()
    {
        return this->computerWon;
    }

    void changeTurn()
    {
        this->computerTurn = !this->computerTurn;
    }

    bool isComputerTurn()
    {
        return this->computerTurn;
    }
};


#endif // GAME_H
