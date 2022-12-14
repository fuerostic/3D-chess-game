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
class Board;
extern pair<pair<pair<int,int>,pair<int,int>>,int>  minimax(Board board, int depth,bool isComputerMax,int alpha,int beta);



class Board
{
private:
    int seconds;
    bool white;
    bool gameOver;
    bool computerWon;
    bool computerTurn;
    int num[10]={10,11,12,13,14,15,16,17,18,19};
    stack<Piece>selected;
    int pos[8][8];
    Player player1 =  Player(1,true,true);
    Player player2 =  Player(2,false,false);
    vector<pair< pair<int,int>,pair<int,int>  >> all_moves;

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

//    vector <pair<int,pair<vector< pair<int,int> >,int>>> all__moves;
    //vector <pair<int,pair<vector< pair<int,int> >,int>>>  all_scoring_moves;

//    map<int,vector<pair<pair<int,int>,int>>> all_moves;

public:
    //int time;

    Board()
    {

        int seconds =0;
        int counter= 0;

        for (int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                position[i][j] = -1;
                pos[i][j] = -1;
//                valpiece.getID()_places[i][j] = -1;
//                scoring_position[i][j] = -1;
                selected_position[i][j] = -1;
            }
        }
        bool computerWon = false;
        bool white = true;

        for( int i=0; i<8; i++)
        {
            for( int j=0; j<8; j++)
            {
                if(i<2 || i>5)
                {
                    selected_position[i][j] = 0;
                    position[i][j] = counter;
                    pos[i][j] = counter;
                    //cout<< pieces[counter].getXindex()<<" "<<pieces[counter].getYindex() <<endl;
                    counter++;
                }
            }
        }

        this->computerTurn = false;
        this->gameOver= false;

    }


    int getSeconds()
    {
        return this->seconds;
    }

    void setSeconds(int second)
    {
        this->seconds = second;
    }
    stack<Piece>& getSelected()
    {
        return this->selected;
    }

    vector <Piece> getPieces()
    {
        vector <Piece> p;

        for(int i=0;i<32;i++)
        {
            p.push_back(pieces[i]);
        }

        return p;
    }

    vector<vector<int>> getPosition()
    {
        vector<vector<int>> v;

        for(int i=0;i<8;i++)
        {
            vector<int>r(8) ;

            for(int j=0;j<8;j++)
            {
                r[j] = (this->pos[i][j]);
            }

            v.push_back(r);
        }


        return v;
    }


    void setPosition(vector<vector<int>> p)
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                this->pos[i][j] = p[i][j];
            }
        }
    }


    void updatePosition()
    {
        memcpy(this->pos, position, sizeof(this->pos));
    }


    Player& getPlayer(int ID)
    {
        if(ID==1)
        {
            return this->player1;
        }
        else
        {
            return this->player2;
        }
    }


    Board getSelf()
    {
        return *this;
    }

    vector<pair< pair<int,int>,pair<int,int> >> get_all_moves()
    {
        for(Piece piece: pieces)
        {
            vector<pair<pair<int,int>,int>> moves = piece.getAllScores();

            for(pair<pair<int,int>,int> i : moves)
            {
                all_moves.push_back(make_pair(make_pair(piece.getXindex(),piece.getYindex()),i.first));
            }
        }

        return this->all_moves;
    }


    bool isComputerWon()
    {
        return this->computerWon;
    }

    bool isGameOver()
    {

        if(this->getPiece(4).getCaught()==true || this->getPlayer(1).getPiecesLeft()==0)
        {
            this->gameOver=true;
            this->computerWon = false;
            cout<<"gameover"<<endl ;
        }
        else if(this->getPiece(28).getCaught()==true || this->getPlayer(2).getPiecesLeft()==0)
        {
            this->gameOver=true;
            this->computerWon = true;
            cout<<"gameover"<<endl ;
        }


        return this->gameOver;
    }


    Board make_move(pair<int,int>i , pair <int,int>j,Board board)
    {
        vector<vector<int>> pos = board.getPosition();
        int id1 = pos[j.second][j.first];
        int id2 = pos[i.second][i.first];
        Piece piece = board.getPiece(id1);


        if(id2!=-1)
        {
            Piece piece2 = board.getPiece(id2);

            if((id2>=0 && id2<16 && id1>15) )
            {
                board.getPlayer(2).setScore(board.getPlayer(2).getScore()+ piece2.getScore());
                board.getPlayer(2).setScoredPiecesNumber(board.getPlayer(2).getScoredPiecesNumber()+1);
                board.getPlayer(1).setPiecesLeft(board.getPlayer(1).getPiecesLeft()-1);

            }
            else if((id2>=16 && id2<32 && id1>=0 && id1<16))
            {
                board.getPlayer(2).setScore(board.getPlayer(2).getScore()+ piece2.getScore());
                board.getPlayer(2).setScoredPiecesNumber(board.getPlayer(2).getScoredPiecesNumber()+1);
                board.getPlayer(1).setPiecesLeft(board.getPlayer(1).getPiecesLeft()-1);
            }
            board.getPiece(id2).setCaught(true);
            pos[i.second][i.first] = id1;
            pos[j.second][j.first] = -1;
            piece.setXindex(i.first);
            piece.setYindex(i.second);

        }
        else
        {
            pos[i.second][i.first] = id1;
            pos[j.second][j.first] = -1;
            piece.setXindex(i.first);
            piece.setYindex(i.second);
        }

        board.setPosition(pos);

        return board;

    }


    vector<pair<pair<int,int>,int> >calculate_vald_moves(Piece piece,int pos[][8])
    {

        vector<pair<pair<int,int>,int> >scores;

        const int king_moves[2][8] = {{0,0,1,1,1,-1,-1,-1},{1,-1,0,1,-1,0,1,-1}};
        const int queen_moves[2][8] = {{0,0,1,1,1,-1,-1,-1},{1,-1,0,1,-1,0,1,-1}};
        const int bishop_moves[2][4] = {{1,1,-1,-1}, {1,-1,1,-1} };
        const int knight_moves[2][8] = { {1,1,2,2,-1,-1,-2,-2}, {2,-2,1,-1,2,-2,1,-1} };
        const int rook_moves[2][4] = { {0,0,1,-1}, {1,-1,0,0} };
        const int pawn_moves[2][3] = { {0,-1,1}, {1,1,1} };


        int tempx;
        int tempy;

        if((piece.getID()>=8 && piece.getID()<16) || (piece.getID()>=16 && piece.getID()<24))
        {
            for(int i =0; i<3; i++)
            {
                tempx = piece.getXindex() + pawn_moves[0][i];
                tempy = piece.getYindex() + (piece.getDirection() * pawn_moves[1][i]);


                if ((tempx<0 || tempy <0 || tempx>8 || tempy>8 || (pos[tempy][tempx]<16  && pos[tempy][tempx]!=-1  && piece.getID()<16) || (pos[tempy][tempx]>=16 && piece.getID()>=16)) && pos[tempy][tempx]!=-1 )
                {
                    break;
                }

                else if(pos[tempy][tempx]==-1 && i==0)
                {

                    scores.push_back(make_pair(make_pair(tempx,tempy),0));

                }
                else
                {
                    if(pos[tempy][tempx]<16 && pos[tempy][tempx]!=-1 && piece.getID()>=16 && i!=0)
                    {

                        scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[pos[tempy][tempx]]));
                        break;
                    }
                    else if(pos[tempy][tempx]>=16 && piece.getID()<16 && i!=0)
                    {

                        scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[pos[tempy][tempx]]));
                        break;
                    }
                }
            }
        }
        else if(piece.getID()==0 || piece.getID()==7 || piece.getID()==24 || piece.getID()==31)
        {


            for(int i =0; i<4; i++)
            {
                int traverse=1;

                while(traverse<9)
                {
                    tempx = piece.getXindex() + (rook_moves[0][i]*traverse);
                    tempy = piece.getYindex() + (rook_moves[1][i]*traverse);




                    if (tempx<0 || tempy <0 || tempx>=8 || tempy>=8 || (pos[tempy][tempx]<16  && pos[tempy][tempx]!=-1  && piece.getID()<16) || (pos[tempy][tempx]>=16 && piece.getID()>=16))
                    {
                        break ;
                    }
                    else if(pos[tempy][tempx]==-1 && (tempx>=0 && tempy >=0 && tempx<8 && tempy<8 ))
                    {

                        scores.push_back(make_pair(make_pair(tempx,tempy),0));
                    }
                    else
                    {
                        if(pos[tempy][tempx]<16 && piece.getID()>=16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[pos[tempy][tempx]]));
                            break;
                        }
                        else if(pos[tempy][tempx]>=16 && piece.getID()<16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[pos[tempy][tempx]]));
                            break;
                        }
                    }


                    traverse++;
                }



            }
        }
        else if(piece.getID()==2 || piece.getID()==5 ||  piece.getID()==26 ||piece.getID()==29 )
        {

            for(int i =0; i<4; i++)
            {
                int traverse=1;

                while(traverse<9)
                {
                    tempx = piece.getXindex() + (bishop_moves[0][i]*traverse);
                    tempy = piece.getYindex() + (bishop_moves[1][i]*traverse);

                    //cout<<"tempx " <<tempx <<" tempy "<<tempy << " " << pos[tempy][tempx]<<endl;

                    if (tempx<0 || tempy <0 || tempx>=8 || tempy>=8 || (pos[tempy][tempx]<16  && pos[tempy][tempx]!=-1  && piece.getID()<16) || (pos[tempy][tempx]>=16 && piece.getID()>=16))
                    {
                        break;
                    }
                    else if(pos[tempy][tempx]==-1 && (tempx>=0 && tempy >=0 && tempx<8 && tempy<8 ))
                    {

                        scores.push_back(make_pair(make_pair(tempx,tempy),0));
                    }
                    else
                    {
                        if(pos[tempy][tempx]<16 && piece.getID()>=16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[pos[tempy][tempx]]));
                            break;
                        }
                        else if(pos[tempy][tempx]>=16 && piece.getID()<16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[pos[tempy][tempx]]));
                            break;
                        }
                    }

                    traverse++;
                }



            }
        }
        else if(piece.getID()==1 ||  piece.getID()==6 ||  piece.getID()==25 ||  piece.getID()==30)
        {


            for(int i =0; i<8; i++)
            {
                int traverse=1;

                while(traverse<2)
                {
                    tempx = piece.getXindex() + (knight_moves[0][i]*traverse);
                    tempy = piece.getYindex() + (knight_moves[1][i]*traverse);

                    if (tempx<0 || tempy <0 || tempx>=8 || tempy>=8 || (pos[tempy][tempx]<16  && pos[tempy][tempx]!=-1  && piece.getID()<16) || (pos[tempy][tempx]>=16 && piece.getID()>=16))
                    {
                        break;
                    }
                    else if(pos[tempy][tempx]==-1 && (tempx>=0 && tempy >=0 && tempx<8 && tempy<8 ))
                    {

                        scores.push_back(make_pair(make_pair(tempx,tempy),0));
                    }
                    else
                    {
                        if(pos[tempy][tempx]<16 && piece.getID()>=16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[pos[tempy][tempx]]));
                            break;
                        }
                        else if(pos[tempy][tempx]>=16 && piece.getID()<16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[pos[tempy][tempx]]));
                            break;
                        }
                    }

                    traverse++;
                }



            }
        }
        else if(piece.getID()==3 || piece.getID()==27)
        {

            for(int i =0; i<8; i++)
            {
                int traverse=1;

                while(traverse<9)
                {

                    tempx = piece.getXindex() + (queen_moves[0][i]*traverse);
                    tempy = piece.getYindex() + (queen_moves[1][i]*traverse);

                    if (tempx<0 || tempy <0 || tempx>=8 || tempy>=8 || (pos[tempy][tempx]<16  && pos[tempy][tempx]!=-1  && piece.getID()<16) || (pos[tempy][tempx]>=16 && piece.getID()>=16))
                    {
                        break;
                    }
                    else if(pos[tempy][tempx]==-1 && (tempx>=0 && tempy >=0 && tempx<8 && tempy<8 ))
                    {

                        scores.push_back(make_pair(make_pair(tempx,tempy),0));
                    }
                    else
                    {
                        if(pos[tempy][tempx]<16 && piece.getID()>=16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[pos[tempy][tempx]]));
                            break;
                        }
                        else if(pos[tempy][tempx]>=16 && piece.getID()<16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[pos[tempy][tempx]]));
                            break;
                        }
                    }
                    traverse++;
                }

            }
        }
        else
        {
            for(int i =0; i<8; i++)
            {
                tempx = piece.getXindex() + king_moves[0][i];
                tempy = piece.getYindex() + (king_moves[1][i]);

                if (tempx<0 || tempy <0 || tempx>=8 || tempy>=8 || (pos[tempy][tempx]<16  && pos[tempy][tempx]!=-1  && piece.getID()<16) || (pos[tempy][tempx]>=16 && piece.getID()>=16))
                {
                    continue;
                }

                else if(pos[tempy][tempx]==-1 && (tempx>=0 && tempy >=0 && tempx<8 && tempy<8 ))
                {

                    scores.push_back(make_pair(make_pair(tempx,tempy),0));
                }
                else
                {
                    if(pos[tempy][tempx]<16 && piece.getID()>=16)
                    {

                        scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[pos[tempy][tempx]]));
                        break;
                    }
                    else if(pos[tempy][tempx]>=16 && piece.getID()<16)
                    {

                        scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[pos[tempy][tempx]]));
                        break;
                    }
                }
            }
        }

    }
    void changeTurn()
    {
        this->computerTurn = !this->computerTurn;

//        if()
        if(computerTurn)
        {
            pair<pair<pair<int,int>,pair<int,int>>,int>  best_move = minimax(getSelf(),6,true,-INFINITE,INFINITE);

            cout<<best_move.first.second.first<<" " <<best_move.first.second.second<<" ID="<<position[best_move.first.second.second][best_move.first.second.first]<< " " <<best_move.first.first.first<< " " <<best_move.first.first.second <<endl;


            this->moveAiPiece(position[best_move.first.second.second][best_move.first.second.first],best_move.first.first);

            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    cout<<position[i][j]<<" ";
                }
                cout<<endl;
            }


            this->computerTurn = !this->computerTurn;
        }

//        if(!computerTurn)
//        {
//            if(this->num==5)
//            {
//                this->num = 4;
//            }
//            else
//            {
//                this->num = 5;
//            }
//        }






    }

    void setGameOver(bool stat)
    {
        this->gameOver = stat;
    }

    void setComputerWon(bool stat)
    {
        this->computerWon = stat;
    }


    bool isComputerTurn()
    {
        return this->computerTurn;
    }

    void drawMenuCard()
    {
        glEnable(GL_TEXTURE_2D);

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,20);
        glTranslatef(-5,5,-3);
        glRotatef(35,1,0,0);
        glScalef(10,1,10);
        drawCube(1);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        //title

        glEnable(GL_TEXTURE_2D);

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,21);
        glTranslatef(-2,4.8,-2);
        glRotatef(35,1,0,0);
        glScalef(4,1,4);
        drawCube(1);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        //buttons : PLAY

        glEnable(GL_TEXTURE_2D);

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,22);
        glTranslatef(-1.5,2,1.5);
        glRotatef(33,1,0,0);
        glScalef(3,1,1);
        drawCube(1);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        //button blitz

        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,25);
        glTranslatef(-1.5,1.2,2.5);
        glRotatef(33,1,0,0);
        glScalef(3,1,1);
        drawCube(1);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        //button exit

        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,23);
        glTranslatef(-1.5,.5,3.5);
        glRotatef(33,1,0,0);
        glScalef(3,1,1);
        drawCube(1);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);




    }


    void drawPauseMenuCard()
    {
        glEnable(GL_TEXTURE_2D);

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,20);
        glTranslatef(-5,5,-3);
        glRotatef(35,1,0,0);
        glScalef(10,1,10);
        drawCube(1);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        //title

        glEnable(GL_TEXTURE_2D);

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,21);
        glTranslatef(-2,4.8,-2);
        glRotatef(35,1,0,0);
        glScalef(4,1,4);
        drawCube(1);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        //buttons : Resume

        glEnable(GL_TEXTURE_2D);

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,24);
        glTranslatef(-1.5,2,1.5);
        glRotatef(33,1,0,0);
        glScalef(3,1,1);
        drawCube(1);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        //button Main menu

        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,26);
        glTranslatef(-1.5,1.2,2.5);
        glRotatef(33,1,0,0);
        glScalef(3,1,1);
        drawCube(1);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        //button exit

        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,23);
        glTranslatef(-1.5,.5,3.5);
        glRotatef(33,1,0,0);
        glScalef(3,1,1);
        drawCube(1);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

    }

    void drawWinnerCard(int num)
    {
        glEnable(GL_TEXTURE_2D);

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,20);
        glTranslatef(-5,5,-3);
        glRotatef(35,1,0,0);
        glScalef(10,1,10);
        drawCube(1);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        //title

        glEnable(GL_TEXTURE_2D);

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,21);
        glTranslatef(-2,4.8,-2);
        glRotatef(35,1,0,0);
        glScalef(4,1,4);
        drawCube(1);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        //buttons : Resume

        glEnable(GL_TEXTURE_2D);

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,num);
        glTranslatef(-1.5,1.5,2.5);
        glRotatef(33,1,0,0);
        glScalef(3,1,2);
        drawCube(1);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

//        //button Main menu
//
//        glEnable(GL_TEXTURE_2D);
//        glPushMatrix();
//        glBindTexture(GL_TEXTURE_2D,26);
//        glTranslatef(-1.5,1.2,2.5);
//        glRotatef(33,1,0,0);
//        glScalef(3,1,1);
//        drawCube(1);
//        glPopMatrix();
//
//        glDisable(GL_TEXTURE_2D);
//
//        //button exit
//
//        glEnable(GL_TEXTURE_2D);
//        glPushMatrix();
//        glBindTexture(GL_TEXTURE_2D,23);
//        glTranslatef(-1.5,.5,3.5);
//        glRotatef(33,1,0,0);
//        glScalef(3,1,1);
//        drawCube(1);
//        glPopMatrix();
//
//        glDisable(GL_TEXTURE_2D);

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

    void drawScoreCard()
    {
        int ai_score[3]= {0,0,0};
        int human_score[3]= {0,0,0};
        int minuten[2] = {0,0};
        int seconden[2] = {0,0};

//        cout<<this->getPlayer(1).getScore()<<endl;
//        cout<<this->getPlayer(3).getScore()<<endl;

        int num1=this->getPlayer(1).getScore();
        int num2= this->getPlayer(2).getScore();

        int counter=3;
        while(num1!=0)
        {
            ai_score[counter-1] = num1%10;
            num1/=10;
            counter--;
        }

        counter=3;
        while(num2!=0)
        {
            human_score[counter-1] = num2%10;
            num2/=10;
            counter--;
        }

        int m = this->seconds/60;
        int s = this->seconds-(m*60);


        counter =2;
        while(m!=0)
        {
            minuten[counter-1] = m%10;
            m/=10;
            counter--;
        }


        counter=2;
        while(s!=0)
        {
            seconden[counter-1] = s%10;
            s/=10;
            counter--;
        }


        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,6);
        glTranslatef(-8,6.5,-7);
        glRotatef(40,1,0,0);
        glScalef(16,.2,4.7);
        drawCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);


        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,9);
        glTranslatef(-5,6.1,-6);
        glRotatef(40,1,0,0);
        glScalef(1,.2,1);
        drawCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);


        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,8);
        glTranslatef(4,6.1,-6);
        glRotatef(40,1,0,0);
        glScalef(1,.2,1);
        drawCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);


        //glPushMatrix();

        //human score show

        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,num[human_score[0]]);
        glTranslatef(3,5,-5);
        glRotatef(40,1,0,0);
        glScalef(1,.2,1);
        drawCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);


        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,num[human_score[1]]);
        glTranslatef(4,5,-5);
        glRotatef(40,1,0,0);
        glScalef(1,.2,1);
        drawCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);


        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,num[human_score[2]]);
        glTranslatef(5,5,-5);
        glRotatef(40,1,0,0);
        glScalef(1,.2,1);
        drawCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        //glPopMatrix();

        //AI score show

        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,num[ai_score[0]]);
        glTranslatef(-6,5,-5);
        glRotatef(40,1,0,0);
        glScalef(1,.2,1);
        drawCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);


        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,num[ai_score[1]]);
        glTranslatef(-5,5,-5);
        glRotatef(40,1,0,0);
        glScalef(1,.2,1);
        drawCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);


        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,num[ai_score[2]]);
        glTranslatef(-4,5,-5);
        glRotatef(40,1,0,0);
        glScalef(1,.2,1);
        drawCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);






        //Time

        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,num[minuten[0]]);
        glTranslatef(-1.25,6,-5);
        glRotatef(40,1,0,0);
        glScalef(.5,.2,.5);
        drawCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);


        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,num[minuten[1]]);
        glTranslatef(-.75,6,-5);
        glRotatef(40,1,0,0);
        glScalef(.5,.2,.5);
        drawCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,30);
        glTranslatef(-0.25,6,-5);
        glRotatef(40,1,0,0);
        glScalef(.5,.2,.5);
        drawCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);


        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,num[seconden[0]]);
        glTranslatef(0.25,6,-5);
        glRotatef(40,1,0,0);
        glScalef(.5,.2,.5);
        drawCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);


        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,num[seconden[1]]);
        glTranslatef(0.75,6,-5);
        glRotatef(40,1,0,0);
        glScalef(.5,.2,.5);
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

                pos[i][j] = position[i][j];

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

                        //cout<<"valpiece.getID() moves"<<endl;

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



        this->drawScoreCard();


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


    void moveAiPiece(int ID,pair<int,int>to)
    {
        Piece piece = this->getPiece(ID);


        if(position[to.first][to.second]!=-1)
        {
            Piece piece2 = this->getPiece(position[to.first][to.second]);
//            if(position[to.second][to.first]<16)
//            {
//                this->player2.setScore(this->player2.getScore()+piece2.getScore() );
//                this->player2.setScoredPiecesNumber(this->player2.getScoredPiecesNumber()+1);
//                this->player1.setPiecesLeft(this->player1.getPiecesLeft()-1);
//            }
            //else
            if(position[to.second][to.first]>=16)
            {
                this->player1.setScore(this->player1.getScore()+piece2.getScore() );
                this->player1.setScoredPiecesNumber(this->player1.getScoredPiecesNumber()+1);
                this->player2.setPiecesLeft(this->player2.getPiecesLeft()-1);

            }

            this->getPiece(position[to.first][to.second]).setCaught(true);

            if(position[to.first][to.second]==28)
            {
                this->gameOver = true;
                this->computerWon = true;

                cout<<"gameoover"<<endl;

            }
        }

        GLfloat movx, movy;

        int nowx = piece.getYindex();
        int nowy = piece.getXindex();

        piece.setXindex(to.first);
        piece.setYindex(to.second);

        position[to.second][to.first] = ID;
        pos[to.second][to.first] = ID;

        position[nowx][nowy] = -1;
        pos[nowx][nowy] = -1;



        glPushMatrix();
        piece.draw();
        glPopMatrix();


    }


    void movePieceOutspiece(int indx,int indy,int ID)
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
