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
    bool white;
    bool gameOver;
    bool computerTurn;
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

    Board()
    {


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

    stack<Piece>& getSelected()
    {
        return this->selected;
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

//    void calculate_best_move_of_ai()
//    {
//        for(int i=0;i<16;i++)
//        {
//            if(pieces[i].getCaught())
//            {
//                continue;
//            }
//
//            pieces[i].resetValidMoves();
//            pieces[i].calculate_valid_moves();
////            vector<int,int> valpiece.getID()_moves= pieces[i].getValpiece.getID()Moves();
////            vector<int,int> scoring_moves = pieces[i].getScoringMoves();
//            vector<pair<pair<int,int>,int> > scores = pieces[i].getAllScores();
//
//            this->all_moves.insert(make_pair(i,scores));
//
//        }
//    }

    Board& getSelf()
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

    bool isGameOver()
    {
        return this->gameOver;
    }

    Board make_move(pair<int,int>i , pair <int,int>j,Board board)
    {
        int id = board.pos[i.second][i.first];
        Piece piece = board.getPiece(id);
        board.pos[i.second][i.first] = -1;
        board.pos[j.second][j.first] = id;
        piece.setXindex(j.first);
        piece.setYindex(j.second);

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
            pair<pair<pair<int,int>,pair<int,int>>,int>  best_move = minimax(getSelf(),1,true,-100,100);

            cout<<best_move.first.second.first<<" " <<best_move.first.second.second<<" ID="<< position[best_move.first.first.second][best_move.first.first.first]<< " " <<best_move.first.first.second<< " " <<best_move.first.first.first <<endl;

            this->movePiece(best_move.first.second.second,best_move.first.second.first,position[best_move.first.first.second][best_move.first.first.first]);
            this->computerTurn = !this->computerTurn;
        }

    }



    bool isComputerTurn()
    {
        return this->computerTurn;
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
