#ifndef PLAYER_H
#define PLAYER_H
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


using namespace std;

class Player
{
private:
    int player_ID;
    bool computer;
    int score;
    int scored_pieces;
    int pieces_left;
    bool win;
    bool checkmate;
    bool white;
    int piece_set[16];
    vector<pair<pair<int,int>,int> > all_moves;



public:

    Player(int id,bool computer,bool white);
    ~Player()
    {
        cout<<"Destroyed objects"<<endl;
    }



    int getID()
    {
        return this->player_ID;
    }
    void setID(int id)
    {
        this->player_ID = id;
    }

    bool isComputer()
    {
        return this->computer;
    }
    void setComputer(bool computer )
    {
        this->computer = computer;
    }

    int getScore()
    {
        return this->score;
    }
    void setScore(int score)
    {
        this->score = score;
        cout<<endl<<"score changed"<<endl;
    }

    int getScoredPiecesNumber()
    {
        return this->scored_pieces;
    }
    void setScoredPiecesNumber(int num)
    {
        this->scored_pieces = num;
    }

    int getPiecesLeft()
    {
        return this->pieces_left;
    }
    void setPiecesLeft(int num)
    {
        this->pieces_left = num;
    }

    bool isWon()
    {
        return this->win;
    }
    void setWon(bool stat)
    {
        this->win = stat;
    }

    bool isCheckmate()
    {
        return this->checkmate;
    }
    void setCheckmate(bool stat)
    {
        this->checkmate = stat;
    }

    bool isWhite()
    {
        return this->white;
    }
    void setWhite(bool stat)
    {
        this->white =stat;
    }

};


#endif // PLAYER_H
