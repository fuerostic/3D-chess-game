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
    bool started;
    bool finished ;
    bool computerWon;
    bool blitz;



public:
    Game()
    {
        this->pause = false;
        this->started= false;
        this->finished =true;
        this->computerWon = false;
        this->blitz = false;

    }



    void resetGame()
    {
        this->getBoard().~Board();
        this->player1.~Player();
        this->player2.~Player();
        Game();
    }


//    Board move_virtual_piece(int pos[][8],Piece piece,int x, int y,Board board)
//    {
//        pos
//        board.getPiece(piece.getID()).setXindex(x);
//        board.getPiece(piece.getID()).setYindex(y);
//
//
//
//    }






//    int  minimax(int pos[][8],Board board,int score, int depth, bool isComputerMax,int alpha,int beta)
//    {
//
//
//        if (isMaximizingPlayer)
//        {
//            int bestVal= -10000;
//
//            for(int i=0;i<16;i++)
//            {
//                Piece piece = pieces[i];
//
//            }
//
//
//        }
//    }


    Board& getBoard()
    {
        return this->board;
    }

    void setBlitz(bool stat)
    {
        this->blitz = stat;
    }

    bool isBlitz()
    {
        return this->blitz;
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

    bool isFinished()
    {
        if(this->board.isGameOver())
        {
            this->finished= true;
        }
        return this->finished;
    }

    void setComputerWon(bool stat)
    {
        this->computerWon = stat;
    }

    bool isComputerWon()
    {
        return this->board.isComputerWon();
    }

    void setStarted(bool stat)
    {
        this->started = stat;
    }
    bool isStarted()
    {
        return this->started;
    }


};


#endif // GAME_H
