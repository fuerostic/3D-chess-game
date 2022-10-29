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




public:
    Game()
    {
        this->pause = false;
        this->finished =false;
        this->computerWon = false;

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


};


#endif // GAME_H
