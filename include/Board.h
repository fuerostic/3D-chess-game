#ifndef BOARD_H
#define BOARD_H
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
#include "Player.h"
#include "Piece.h"

class Board
{
private:
    bool white;
    Player player1 =  Player(1,true,true);
    Player player2 =  Player(2,false,false);

    bool board_filled[8][8] = {{true,true,true,true,true,true,true,true},{true,true,true,true,true,true,true,true},
        {false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},
        {false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},
        {true,true,true,true,true,true,true,true},{true,true,true,true,true,true,true,true}
    };

    Piece pieces[32] = {  Piece(0,true,true),Piece(1,true,true),Piece(2,true,true),Piece(3,true,true),
                          Piece(4,true,true),Piece(5,true,true),Piece(6,true,true),Piece(7,true,true),
                          Piece(8,true,true),Piece(9,true,true),Piece(10,true,true),Piece(11,true,true),
                          Piece(12,true,true),Piece(13,true,true),Piece(14,true,true),Piece(15,true,true),
                          Piece(16,false,false),Piece(17,false,false),Piece(18,false,false),Piece(19,false,false),
                          Piece(20,false,false),Piece(21,false,false),Piece(22,false,false),Piece(23,false,false),
                          Piece(24,false,false),Piece(25,false,false),Piece(26,false,false),Piece(27,false,false),
                          Piece(28,false,false),Piece(29,false,false),Piece(30,false,false),Piece(31,false,false)
                       };

    vector <pair<int,pair<vector< pair<int,int> >,int>>> all_valid_moves;
    vector <pair<int,pair<vector< pair<int,int> >,int>>>  all_scoring_moves;

public:

    Board()
    {


        int counter= 0;

        for (int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                position[i][j] = -1;
                valid_places[i][j] = -1;
                scoring_position[i][j] = -1;
                selected_position[i][j] = -1;
            }
        }

        bool white = true;

        for( int i=0; i<8; i++)
        {
            for( int j=0; j<8; j++)
            {
                if(i<2 || i>5)
                {
                    selected_position[i][j] = 0;
                    position[i][j] = counter;
                    //cout<< pieces[counter].getXindex()<<" "<<pieces[counter].getYindex() <<endl;
                    counter++;
                }
            }
        }

    }

    Player& getPlayer(int id)
    {
        if(id==1)
        {
            return this->player1;
        }
        else
        {
            return this->player2;
        }
    }

    void calculate_valid_moves()
    {

    }

    void drawBoard()
    {
        glEnable(GL_TEXTURE_2D);

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,3);
        glTranslatef(-5,0,-5);
        glScalef(10,1,10);
        drawCube(1);
        glPopMatrix();



        glDisable(GL_TEXTURE_2D);
    }




    void draw()
    {
        glPushMatrix();
        glPushMatrix();

        this->drawBoard();

        glPopMatrix();

        for( int i=0; i<8; i++)
        {
            for( int j=0; j<8; j++)
            {
                if(position[i][j]!=-1)
                {
                    int counter = position[i][j];
                    pieces[counter].setXindex(j);
                    pieces[counter].setYindex(i);
                    position[i][j] = pieces[counter].getID();
                    //cout<< pieces[counter].getXindex()<<" "<<pieces[counter].getYindex() <<endl;

                    glPushMatrix();
                    pieces[counter].draw();
                    glPopMatrix();

                    if(selected_position[j][i]==1)
                    {
                        glPushMatrix();
                        pieces[counter].draw_selection();
                        glPopMatrix();

                        pieces[counter].resetValidMoves();
                        pieces[counter].calculate_valid_moves();

                        //cout<<"valid moves"<<endl;

                        for(pair<int,int> i: pieces[counter].getValidMoves())
                        {
                            //cout<< "("<<i.first<<","<<i.second<<"),";
                            glPushMatrix();
                            pieces[counter].draw_valid_move(6,i.first,i.second);
                            glPopMatrix();
                        }
                        //cout<<endl<<"scoring moves"<<endl;
                        for(pair<int,int> i: pieces[counter].getScoringMoves())
                        {
                            //cout<< "("<<i.first<<","<<i.second<<"),";
                            glPushMatrix();
                            pieces[counter].draw_valid_move(5,i.first,i.second);
                            glPopMatrix();
                        }
                        //cout<<endl ;
                    }




                    counter++;
                }



                //cout<<position[i][j]<<" ";
            }
            //cout<<endl;
        }

        glPopMatrix();
    }

    Piece getPiece(int ID)
    {
        return this->pieces[ID];
    }

    void movePiece(int indx,int indy,int ID)
    {
        Piece piece = this->getPiece(ID);
        GLfloat movx, movy;

        int nowx = piece.getYindex();
        int nowy = piece.getXindex();

        movx = (indx-nowx)/10;
        movy = (indy-nowy)/10;

        for(int i=0; i<10; i++)
        {

            piece.setXindex(nowy+movy);
            piece.setYindex(nowx+movx);
            unsigned int microseconds = 500;
            usleep(microseconds);

        }
        piece.setXindex(indx);
        piece.setYindex(indy);

        glPushMatrix();
        piece.draw();
        glPopMatrix();

    }

    void movePieceOutside(int indx,int indy,int ID)
    {
        Piece piece = this->getPiece(ID);
        GLfloat movx, movy;

        int nowx = piece.getYindex();
        int nowy = piece.getXindex();

        movx = (indx-nowx)/10;
        movy = (indy-nowy)/10;

        for(int i=0; i<10; i++)
        {

            piece.setXindex(nowy+movy);
            piece.setYindex(nowx+movx);
            unsigned int microseconds = 500;
            usleep(microseconds);

        }
        piece.setXindex(indx);
        piece.setYindex(indy);

        glPushMatrix();
        piece.draw();
        glPopMatrix();

    }
};


#endif // BOARD_H
