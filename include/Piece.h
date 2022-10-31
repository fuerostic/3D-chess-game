#ifndef PIECE_H
#define PIECE_H
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
#include <bits/stdc++.h>

using namespace std;

extern const int king_moves[2][8] ;
extern const int queen_moves[2][8] ;
extern const int bishop_moves[2][4] ;
extern const int knight_moves[2][8] ;
extern const int rook_moves[2][4] ;
extern const int pawn_moves[2][3] ;

extern GLfloat pos_x[8] ;
extern GLfloat pos_y[8] ;
//GLfloat scored_lobby_p1[2][16]= {{-6.5,-6.5,-6.5,-6.5,-6.5,-6.5,-6.5,-6.5,-7.5,-7.5,-7.5,-7.5,-7.5,-7.5,-7.5,-7.5},{-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5,-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5}};
//GLfloat scored_lobby_p2[2][16]= {{6.5,6.5,6.5,6.5,6.5,6.5,6.5,6.5,7.5,7.5,7.5,7.5,7.5,7.5,7.5,7.5},{-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5,-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5}};
extern GLfloat x_diff[] ;
extern GLfloat y_diff[] ;

extern GLfloat x_start_points[] ;
extern GLfloat y_start_points[] ;

extern int score_by_id[32];

extern float color[];
extern GLfloat no_mat[] ;
extern GLfloat mat_ambient[] ;
extern GLfloat mat_diffuse[] ;
extern GLfloat mat_specular[] ;
extern GLfloat mat_shininess[] ;


static int position[8][8];
static int valid_places[8][8];
static int scoring_position[8][8];
static int selected_position[8][8];

static void getNormal3p(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3);
void drawCube(float length,float shine=60);


class Piece
{
private:
    int ID;
    bool white = true;
    int texture;
    int xindex;
    int yindex;
    int score;
    bool selected = false;
    bool reach_end= false;
    vector<pair<int,int>> valid_moves;
    vector<pair<int,int>> scoring_moves;
    vector<pair<pair<int,int>,int> >scores;
    int direction = 1;
    bool caught;
    bool computer;
    pair<pair<int,int>,int> best_move;

public:

    Piece(int ID,bool white,bool computer)
    {
        this->ID = ID;
        this->white = white;
        this->caught = false;
        this->computer = computer;
        this->best_move= make_pair(make_pair(-1,-1),-1);
        if (white)
        {
            this->texture=1;
            this->direction = 1;
        }
        else
        {
            this->texture=2;
            this->direction = -1;

        }

        if((ID>=8 && ID<16) || (ID>=16 && ID<24))
        {
            this->score = 1;
        }
        else if(ID==0 || ID==7 || ID==24 || ID==31)
        {
            this->score = 5;
        }
        else if(ID==1 || ID==2 || ID==6 || ID==5 || ID==25 || ID==26 ||ID==29 ||  ID==30)
        {
            this->score = 3;
        }
        else if(ID==3 || ID==27)
        {
            this->score = 9;
        }
        else
        {
            this->score = 100;
        }

    }


    Piece()
    {
        ;
    }

    pair<pair<int,int>,int> calculate_best_move()
    {
        this->resetValidMoves();
        this->calculate_valid_moves();

        for(pair<pair<int,int>,int> i: scores)
        {
            if(i.second > best_move.second)
            {
                best_move = i;
            }
        }

        return best_move;
    }

    vector<pair<int,int>> getValidMoves()
    {
        return this->valid_moves;
    }

    vector<pair<int,int>> getScoringMoves()
    {
        return this->scoring_moves;
    }

    vector<pair<pair<int,int>,int> > getAllScores()
    {
        return this->scores;
    }

    void resetValidMoves()
    {
        this->valid_moves.clear();
        this->scoring_moves.clear();
        this->scores.clear();
    }

    void calculate_valid_moves()
    {
        int tempx;
        int tempy;

        if((this->ID>=8 && this->ID<16) || (this->ID>=16 && this->ID<24) && !this->reach_end)
        {
            for(int i =0; i<3; i++)
            {
                tempx = this->xindex + pawn_moves[0][i];
                tempy = this->yindex + (this->direction * pawn_moves[1][i]);


                if ((tempx<0 || tempy <0 || tempx>8 || tempy>8 || (position[tempy][tempx]<16  && position[tempy][tempx]!=-1  && this->ID<16) || (position[tempy][tempx]>=16 && this->ID>=16)) && position[tempy][tempx]!=-1 )
                {
                    break;
                }

                else if(position[tempy][tempx]==-1 && i==0)
                {
                    this->valid_moves.push_back(make_pair(tempx,tempy));
                    this->scores.push_back(make_pair(make_pair(tempx,tempy),0));

                }
                else
                {
                    if(position[tempy][tempx]<16 && position[tempy][tempx]!=-1 && this->ID>=16 && i!=0)
                    {
                        this->scoring_moves.push_back(make_pair(tempx,tempy));
                        this->scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[position[tempy][tempx]]));

                    }
                    else if(position[tempy][tempx]>=16 && this->ID<16 && i!=0)
                    {
                        this->scoring_moves.push_back(make_pair(tempx,tempy));
                        this->scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[position[tempy][tempx]]));
                        break;
                    }
                }
            }
        }
        else if(this->ID==0 || this->ID==7 || this->ID==24 || this->ID==31)
        {


            for(int i =0; i<4; i++)
            {
                int traverse=1;

                while(traverse<9)
                {
                    tempx = this->xindex + (rook_moves[0][i]*traverse);
                    tempy = this->yindex + (rook_moves[1][i]*traverse);




                    if (tempx<0 || tempy <0 || tempx>=8 || tempy>=8 || (position[tempy][tempx]<16  && position[tempy][tempx]!=-1  && this->ID<16) || (position[tempy][tempx]>=16 && this->ID>=16))
                    {
                        break ;
                    }
                    else if(position[tempy][tempx]==-1 && (tempx>=0 && tempy >=0 && tempx<8 && tempy<8 ))
                    {
                        this->valid_moves.push_back(make_pair(tempx,tempy));
                        this->scores.push_back(make_pair(make_pair(tempx,tempy),0));
                    }
                    else
                    {
                        if(position[tempy][tempx]<16 && this->ID>=16)
                        {
                            this->scoring_moves.push_back(make_pair(tempx,tempy));
                            this->scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[position[tempy][tempx]]));
                            break;
                        }
                        else if(position[tempy][tempx]>=16 && this->ID<16)
                        {
                            this->scoring_moves.push_back(make_pair(tempx,tempy));
                            this->scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[position[tempy][tempx]]));
                            break;
                        }
                    }


                    traverse++;
                }



            }
        }
        else if(this->ID==2 || this->ID==5 ||  this->ID==26 ||this->ID==29 )
        {

            for(int i =0; i<4; i++)
            {
                int traverse=1;

                while(traverse<9)
                {
                    tempx = this->xindex + (bishop_moves[0][i]*traverse);
                    tempy = this->yindex + (bishop_moves[1][i]*traverse);

                    //cout<<"tempx " <<tempx <<" tempy "<<tempy << " " << position[tempy][tempx]<<endl;

                    if (tempx<0 || tempy <0 || tempx>=8 || tempy>=8 || (position[tempy][tempx]<16  && position[tempy][tempx]!=-1  && this->ID<16) || (position[tempy][tempx]>=16 && this->ID>=16))
                    {
                        break;
                    }
                    else if(position[tempy][tempx]==-1 && (tempx>=0 && tempy >=0 && tempx<8 && tempy<8 ))
                    {
                        this->valid_moves.push_back(make_pair(tempx,tempy));
                        this->scores.push_back(make_pair(make_pair(tempx,tempy),0));
                    }
                    else
                    {
                        if(position[tempy][tempx]<16 && this->ID>=16)
                        {
                            this->scoring_moves.push_back(make_pair(tempx,tempy));
                            this->scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[position[tempy][tempx]]));
                            break;
                        }
                        else if(position[tempy][tempx]>=16 && this->ID<16)
                        {
                            this->scoring_moves.push_back(make_pair(tempx,tempy));
                            this->scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[position[tempy][tempx]]));
                            break;
                        }
                    }

                    traverse++;
                }



            }
        }
        else if(this->ID==1 ||  this->ID==6 ||  this->ID==25 ||  this->ID==30)
        {


            for(int i =0; i<8; i++)
            {
                int traverse=1;

                while(traverse<2)
                {
                    tempx = this->xindex + (knight_moves[0][i]*traverse);
                    tempy = this->yindex + (knight_moves[1][i]*traverse);

                    if (tempx<0 || tempy <0 || tempx>=8 || tempy>=8 || (position[tempy][tempx]<16  && position[tempy][tempx]!=-1  && this->ID<16) || (position[tempy][tempx]>=16 && this->ID>=16))
                    {
                        break;
                    }
                    else if(position[tempy][tempx]==-1 && (tempx>=0 && tempy >=0 && tempx<8 && tempy<8 ))
                    {
                        this->valid_moves.push_back(make_pair(tempx,tempy));
                        this->scores.push_back(make_pair(make_pair(tempx,tempy),0));
                    }
                    else
                    {
                        if(position[tempy][tempx]<16 && this->ID>=16)
                        {
                            this->scoring_moves.push_back(make_pair(tempx,tempy));
                            this->scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[position[tempy][tempx]]));
                            break;
                        }
                        else if(position[tempy][tempx]>=16 && this->ID<16)
                        {
                            this->scoring_moves.push_back(make_pair(tempx,tempy));
                            this->scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[position[tempy][tempx]]));
                            break;
                        }
                    }

                    traverse++;
                }



            }
        }
        else if((this->ID==3 || this->ID==27) || (this->ID>=8 && this->ID<16) || ((this->ID>=16 && this->ID<24) && this->reach_end))
        {

            for(int i =0; i<8; i++)
            {
                int traverse=1;

                while(traverse<9)
                {

                    tempx = this->xindex + (queen_moves[0][i]*traverse);
                    tempy = this->yindex + (queen_moves[1][i]*traverse);

                    if (tempx<0 || tempy <0 || tempx>=8 || tempy>=8 || (position[tempy][tempx]<16  && position[tempy][tempx]!=-1  && this->ID<16) || (position[tempy][tempx]>=16 && this->ID>=16))
                    {
                        break;
                    }
                    else if(position[tempy][tempx]==-1 && (tempx>=0 && tempy >=0 && tempx<8 && tempy<8 ))
                    {
                        this->valid_moves.push_back(make_pair(tempx,tempy));
                        this->scores.push_back(make_pair(make_pair(tempx,tempy),0));
                    }
                    else
                    {
                        if(position[tempy][tempx]<16 && this->ID>=16)
                        {
                            this->scoring_moves.push_back(make_pair(tempx,tempy));
                            this->scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[position[tempy][tempx]]));
                            break;
                        }
                        else if(position[tempy][tempx]>=16 && this->ID<16)
                        {
                            this->scoring_moves.push_back(make_pair(tempx,tempy));
                            this->scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[position[tempy][tempx]]));
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
                tempx = this->xindex + king_moves[0][i];
                tempy = this->yindex + (king_moves[1][i]);

                if (tempx<0 || tempy <0 || tempx>=8 || tempy>=8 || (position[tempy][tempx]<16  && position[tempy][tempx]!=-1  && this->ID<16) || (position[tempy][tempx]>=16 && this->ID>=16))
                {
                    continue;
                }

                else if(position[tempy][tempx]==-1 && (tempx>=0 && tempy >=0 && tempx<8 && tempy<8 ))
                {
                    this->valid_moves.push_back(make_pair(tempx,tempy));
                    this->scores.push_back(make_pair(make_pair(tempx,tempy),0));
                }
                else
                {
                    if(position[tempy][tempx]<16 && this->ID>=16)
                    {
                        this->scoring_moves.push_back(make_pair(tempx,tempy));
                        this->scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[position[tempy][tempx]]));
                        break;
                    }
                    else if(position[tempy][tempx]>=16 && this->ID<16)
                    {
                        this->scoring_moves.push_back(make_pair(tempx,tempy));
                        this->scores.push_back(make_pair(make_pair(tempx,tempy),score_by_id[position[tempy][tempx]]));
                        break;
                    }
                }
            }
        }







    }


    int getDirection()
    {
        return this->direction;
    }

    void end_reached()
    {
        this->reach_end=true;
        this->score =9;

//        if(this->white)
//        {
//            this->ID=3;
//        }
//        else
//        {
//            this->ID=27;
//        }
    }
    int getID()
    {
        return ID;
    }
    void setID(int ID)
    {

        this->ID = ID;
    }

    int getTexture()
    {
        return this->texture;
    }
    void setTexture(int tex)
    {
        this->texture = tex;
    }

    void setXindex(int x)
    {
        this->xindex = x;
    }

    int getXindex()
    {
        return this->xindex;
    }

    void setYindex(int y)
    {
        this->yindex = y;

        if((this->ID>=8 && this->ID<16 && this->yindex==7) || (this->ID>=16 && this->ID<24 && this->yindex==0) )
        {
            this->end_reached();
        }
    }
    int getYindex()
    {
        return this->yindex;
    }

    void setScore(int score)
    {
        this->score = score;
    }
    int getScore()
    {
        return this->score;
    }

    bool getSelect()
    {
        return this->selected;
    }
    void setSelected(bool selected)
    {
        this->selected = selected;

        if(selected)
        {

            selected_position[this->xindex][this->yindex] =1;
            //cout<<endl<<this->texture<<endl;

        }
        else
        {

            selected_position[this->xindex][this->yindex] =0;
            if (white)
            {
                this->texture=1;
            }
            else
            {
                this->texture=2;
            }
        }

//        for(int i=0;i<8;i++)
//        {
//            for(int j=0;j<8;j++)
//            {
//                cout<<selected_position[i][j]<<" ";
//            }
//
//            cout<<endl;
//        }

    }



    bool getCaught()
    {
        return this->caught;
    }
    void setCaught(bool stat)
    {
        this->caught= stat;
    }

    bool isComputer()
    {
        return this->computer;
    }
    void setComputer(bool stat)
    {
        this->computer = stat;
    }


    void drawPawn(GLuint ID)
    {


        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D,ID);

        if(this->caught)
        {
            return;

        }
        else
        {
            glTranslatef(pos_x[this->xindex],1,pos_y[this->yindex]);
        }


        glPushMatrix();
        glRotatef(90,1,0,0);

        glPushMatrix();

        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


        //lower base
        glPushMatrix();
        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .4, .4, .2,100, 100);
        glutSolidTorus(.1,.3,100,100);
        glPopMatrix();

        //lower base cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.4,32,32);
        glPopMatrix();
        glPopMatrix();

        //lower 2nd base
        glPushMatrix();
        glTranslatef(0,0,-0.2);

        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .3, .3, .2,100, 100);
        glutSolidTorus(.1,.2,100,100);
        glPopMatrix();

        //lower 2nd base cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.3,32,32);
        glPopMatrix();
        glPopMatrix();

        //rising middle column
        glPushMatrix();
        glTranslatef(0,0,-0.6);
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .15, .25, .4,100, 100);
        glPopMatrix();

        //middle column
        glPushMatrix();
        glTranslatef(0,0,-1);
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .15, .15, .4,100, 100);
        glPopMatrix();


        //lower 2nd base
        glPushMatrix();
        glTranslatef(0,0,-1.1);

        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .2, .2, .1,100, 100);
        glPopMatrix();

        //lower 2nd base cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.2,32,32);
        glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,-1);
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.2,32,32);
        glPopMatrix();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0,0,-1.2);
        glutSolidSphere(.2,32,32);
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();
        glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);
    }

    void drawRook(GLuint ID)
    {


        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D,ID);

        if(this->caught)
        {
            return;

        }
        else
        {
            glTranslatef(pos_x[this->xindex],1,pos_y[this->yindex]);
        }
        glPushMatrix();
        glRotatef(90,1,0,0);

        glPushMatrix();

        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


        //lower base
        glPushMatrix();
        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .4, .4, .2,100, 100);
        glutSolidTorus(.1,.3,100,100);
        glPopMatrix();

        //lower base cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.4,32,32);
        glPopMatrix();
        glPopMatrix();

        //lower 2nd base
        glPushMatrix();
        glTranslatef(0,0,-0.2);

        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .3, .3, .2,100, 100);
        glutSolidTorus(.1,.2,100,100);
        glPopMatrix();

        //lower 2nd base cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.3,32,32);
        glPopMatrix();
        glPopMatrix();

        //rising middle column
        glPushMatrix();
        glTranslatef(0,0,-0.6);
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .15, .25, .4,100, 100);
        glPopMatrix();

        //middle column
        glPushMatrix();
        glTranslatef(0,0,-1.2);
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .15, .15, .6,100, 100);
        glPopMatrix();


        //upper base
        glPushMatrix();
        glTranslatef(0,0,-1.3);

        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .2, .2, .1,100, 100);
        glPopMatrix();

        //upper cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.005,.2,32,32);
        glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,-1.2);
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.2,32,32);
        glPopMatrix();
        glPopMatrix();

        //rook crown
        glPushMatrix();
        glTranslatef(0,0,-1.4);

        glPushMatrix();
        glTranslatef(.15,0,0.05);
        glutSolidCube(.1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-.15,0,0.05);
        glutSolidCube(.1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0.15,0.05);
        glutSolidCube(.1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,-.15,0.05);
        glutSolidCube(.1);
        glPopMatrix();


        glPopMatrix();

        glPopMatrix();
        glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);
    }

    void drawKnight(GLuint ID)
    {

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D,ID);

        if(this->caught)
        {
            return;

        }
        else
        {
            glTranslatef(pos_x[this->xindex],1,pos_y[this->yindex]);
        }
        glPushMatrix();

        glRotatef(90,1,0,0);

        glPushMatrix();

        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


        //lower base
        glPushMatrix();
        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .4, .4, .2,100, 100);
        glutSolidTorus(.1,.3,100,100);
        glPopMatrix();

        //lower base cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.4,32,32);
        glPopMatrix();
        glPopMatrix();

        //lower 2nd base
        glPushMatrix();
        glTranslatef(0,0,-0.2);

        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .3, .3, .2,100, 100);
        glutSolidTorus(.1,.2,100,100);
        glPopMatrix();

        //lower 2nd base cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.3,32,32);
        glPopMatrix();
        glPopMatrix();

        //rising middle column
        glPushMatrix();
        glTranslatef(0,0,-0.6);
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .15, .25, .4,100, 100);
        glPopMatrix();

        //body of horse



        glPushMatrix();
        glTranslatef(0,0,-1);
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), 0, .15, .4,100, 100);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.1,0,0);
        glRotatef(-10,0,1,0);

        glPushMatrix();
        glRotatef(14,0,1,0);
        glTranslatef(-0.07,-.075,-1.2);
        glScalef(.5,.25,1);
        drawCube(.7);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(-0.35,-.075,-1.3);
        glRotatef(-5,0,1,0);
        glScalef(.5,.25,.25);
        drawCube(.7);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.35,-.075,-1.4);
        glRotatef(-10,0,1,0);
        glScalef(.5,.25,.25);
        drawCube(.7);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.35,-.075,-1.5);
        glRotatef(-15,0,1,0);
        glScalef(.7,.25,.25);
        drawCube(.7);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(-0.3,-.075,-1.6);
        glRotatef(-30,0,1,0);
        glScalef(.4,.25,.25);
        drawCube(.7);
        glPopMatrix();

        glPopMatrix();



        glPopMatrix();

        glPopMatrix();
        glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);
    }

    void drawBishop(GLuint ID)
    {

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D,ID);

        if(this->caught)
        {
            return;

        }
        else
        {
            glTranslatef(pos_x[this->xindex],1,pos_y[this->yindex]);
        }
        glPushMatrix();
        glRotatef(90,1,0,0);

        glPushMatrix();

        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


        //lower base
        glPushMatrix();
        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .4, .4, .2,100, 100);
        glutSolidTorus(.1,.3,100,100);
        glPopMatrix();

        //lower base cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.4,32,32);
        glPopMatrix();
        glPopMatrix();

        //lower 2nd base
        glPushMatrix();
        glTranslatef(0,0,-0.2);

        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .3, .3, .2,100, 100);
        glutSolidTorus(.1,.2,100,100);
        glPopMatrix();

        //lower 2nd base cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.3,32,32);
        glPopMatrix();
        glPopMatrix();

        //rising middle column
        glPushMatrix();
        glTranslatef(0,0,-0.6);
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .10, .25, .4,100, 100);
        glPopMatrix();

        //middle column
        glPushMatrix();
        glTranslatef(0,0,-1.2);
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .10, .10, .6,100, 100);
        glPopMatrix();


        //upper base
        glPushMatrix();
        glTranslatef(0,0,-1.3);

        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .15, .15, .1,100, 100);
        glPopMatrix();

        //upper cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.005,.15,32,32);
        glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,-1.2);
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.15,32,32);
        glPopMatrix();
        glPopMatrix();

        //bishop crown
        glPushMatrix();
        glTranslatef(0,0,-1.4);

        glPushMatrix();
        glTranslatef(0,0,-.2);
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .1, .02, .6,100, 100);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,-.2);
        glutSolidSphere(.1,32,32);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,-.33);
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .02, .1, .1,100, 100);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0,0,-.35);
        glutSolidSphere(.03,32,32);
        glPopMatrix();

        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
        glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);
    }

    void drawQueen(GLuint ID)
    {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D,ID);

        if(this->caught)
        {
            return;

        }
        else
        {
            glTranslatef(pos_x[this->xindex],1,pos_y[this->yindex]);
        }
        glPushMatrix();
        glRotatef(90,1,0,0);

        glPushMatrix();

        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


        //lower base
        glPushMatrix();
        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .4, .4, .2,100, 100);
        glutSolidTorus(.1,.3,100,100);
        glPopMatrix();

        //lower base cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.4,32,32);
        glPopMatrix();
        glPopMatrix();

        //lower 2nd base
        glPushMatrix();
        glTranslatef(0,0,-0.2);

        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .3, .3, .2,100, 100);
        glutSolidTorus(.1,.2,100,100);
        glPopMatrix();

        //lower 2nd base cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.3,32,32);
        glPopMatrix();
        glPopMatrix();

        //rising middle column
        glPushMatrix();
        glTranslatef(0,0,-0.6);
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .15, .25, .4,100, 100);
        glPopMatrix();

        //middle column
        glPushMatrix();
        glTranslatef(0,0,-1.4);
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .15, .15, .8,100, 100);
        glPopMatrix();


        //upper base
        glPushMatrix();
        glTranslatef(0,0,-1.5);

        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .2, .2, .1,100, 100);
        glPopMatrix();

        //upper cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.005,.2,32,32);
        glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,-1.5);
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.2,32,32);
        glPopMatrix();
        glPopMatrix();

        //queen crown
        glPushMatrix();
        glTranslatef(0,0,-1.6);

        glPushMatrix();
        glTranslatef(0,0,-0.15);
        gluCylinder(gluNewQuadric(), .2, .15, .3,100, 100);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,-0.15);
        glutSolidTorus(.1,.1,100,100);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,-0.2);
        glutSolidSphere(.13,100,100);
        glPopMatrix();

        //    glPushMatrix();
        //    glTranslatef(-0.02,-0.17,-0.25);
        //    glScalef(.1,.7,.1);
        //    drawCube(.5);
        //    glPopMatrix();
        //
        //    glPushMatrix();
        //    glRotatef(90,0,0,1);
        //    glTranslatef(-0.02,-0.17,-0.25);
        //    glScalef(.1,.7,.1);
        //    drawCube(.5);
        //    glPopMatrix();
        //
        //    glPushMatrix();
        //    glRotatef(45,0,0,1);
        //    glTranslatef(-0.02,-0.17,-0.25);
        //    glScalef(.1,.7,.1);
        //    drawCube(.5);
        //    glPopMatrix();
        //
        //
        //    glPushMatrix();
        //    glRotatef(315,0,0,1);
        //    glTranslatef(-0.02,-0.17,-0.25);
        //    glScalef(.1,.7,.1);
        //    drawCube(.5);
        //    glPopMatrix();



        glPopMatrix();


        glPopMatrix();

        glPopMatrix();
        glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);
    }

    void drawKing(GLuint ID)
    {

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D,ID);

        if(this->caught)
        {
            return;

        }
        else
        {
            glTranslatef(pos_x[this->xindex],1,pos_y[this->yindex]);
        }
        glPushMatrix();
        glRotatef(90,1,0,0);

        glPushMatrix();

        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


        //lower base
        glPushMatrix();
        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .4, .4, .2,100, 100);
        glutSolidTorus(.1,.3,100,100);
        glPopMatrix();

        //lower base cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.4,32,32);
        glPopMatrix();
        glPopMatrix();

        //lower 2nd base
        glPushMatrix();
        glTranslatef(0,0,-0.2);

        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .3, .3, .2,100, 100);
        glutSolidTorus(.1,.2,100,100);
        glPopMatrix();

        //lower 2nd base cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.3,32,32);
        glPopMatrix();
        glPopMatrix();

        //rising middle column
        glPushMatrix();
        glTranslatef(0,0,-0.6);
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .15, .25, .4,100, 100);
        glPopMatrix();

        //middle column
        glPushMatrix();
        glTranslatef(0,0,-1.4);
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .15, .15, .8,100, 100);
        glPopMatrix();


        //upper base
        glPushMatrix();
        glTranslatef(0,0,-1.5);

        glPushMatrix();
        glScalef(1,1,1);
        gluCylinder(gluNewQuadric(), .2, .2, .1,100, 100);
        glPopMatrix();

        //upper cover
        glPushMatrix();
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.005,.2,32,32);
        glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,-1.5);
        glRotatef(180,1,0,0);
        gluDisk(gluNewQuadric(),.1,.2,32,32);
        glPopMatrix();
        glPopMatrix();

        //king crown
        glPushMatrix();
        glTranslatef(0,0,-1.6);

        glPushMatrix();
        glTranslatef(0,0,-0.15);
        gluCylinder(gluNewQuadric(), .2, .15, .3,100, 100);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,-0.15);
        glutSolidTorus(.1,.1,100,100);
        glPopMatrix();

        glPushMatrix();
        //glRotatef(90,1,0,0);
        glTranslatef(-0.02,-0.025,-0.6);
        glScalef(.05,.05,.7);
        drawCube(1);
        glPopMatrix();

        glPushMatrix();
        glRotatef(3,0,1,0);
        glTranslatef(-0.02,-0.025,-0.6);
        glScalef(.05,.05,.7);
        drawCube(1);
        glPopMatrix();

        glPushMatrix();
        glRotatef(-3,0,1,0);
        glTranslatef(-0.02,-0.025,-0.6);
        glScalef(.05,.05,.7);
        drawCube(1);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(-0.15,-0.025,-0.4);
        glRotatef(90,0,1,0);
        glScalef(.05,.05,.3);
        drawCube(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.15,-0.025,-0.4);
        glRotatef(95,0,1,0);
        glScalef(.05,.05,.3);
        drawCube(1);
        glPopMatrix();

        glPushMatrix();
        glRotatef(81,0,1,0);
        glTranslatef(.4,-0.025,-0.22);
        glScalef(.05,.05,.3);
        drawCube(1);
        glPopMatrix();

        glPushMatrix();
        glRotatef(95,0,1,0);
        glTranslatef(.4,-0.025,-0.11);
        glScalef(.05,.05,.3);
        drawCube(1);
        glPopMatrix();


        glPopMatrix();


        glPopMatrix();

        glPopMatrix();
        glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);
    }

    void draw()
    {
        if(this->caught)
            return;

        if((this->ID>=8 && this->ID<16) || (this->ID>=16 && this->ID<24))
        {

            if(this->reach_end)
            {
                drawQueen(this->texture);
            }
            else
            {
                this->drawPawn(this->texture);
            }


        }
        else if (this->ID==0 || this->ID==7 || this->ID==24 || this->ID==31)
        {
            this->drawRook(this->texture);
        }
        else if(this->ID==1 ||  this->ID==6 || this->ID==25 ||   this->ID==30)
        {
            this->drawKnight(this->texture);
        }
        else if(this->ID==2 || this->ID==5 || this->ID==26 ||this->ID==29 )
        {
            this->drawBishop(this->texture);
        }
        else if(this->ID==3 || this->ID==27)
        {
            this->drawQueen(this->texture);
        }
        else
        {
            this->drawKing(this->texture);
        }
    }

    void draw_selection()
    {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D,4);

        glTranslatef(pos_x[this->xindex],1,pos_y[this->yindex]);
        glPushMatrix();
        //glColor3f(0,1,0);


        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

        glPushMatrix();
        glTranslatef(-0.5,-.1,-.48);
        glScalef(1,.2,1);
        drawCube(1);
        glPopMatrix();

        glPopMatrix();

        //cout << "created in "<<pos_x[this->yindex]<<" "<<pos_y[this->xindex]<<endl;

        glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);
    }

    void draw_valid_move(int ID,int x,int y)
    {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D,ID);

        glTranslatef(pos_x[x],1,pos_y[y]);
        glPushMatrix();
        //glColor3f(0,1,0);


        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


        if(ID==6)
        {
            glPushMatrix();
            glTranslatef(-0.125,-.1,-.124);
            glScalef(.25,.2,.25);
            drawCube(1);
            glPopMatrix();
        }
        else
        {
            glPushMatrix();
            glTranslatef(-0.5,-.1,-.48);
            glScalef(1,.2,1);
            drawCube(1);
            glPopMatrix();
        }



        glPopMatrix();

        //cout << "created in "<<pos_x[this->yindex]<<" "<<pos_y[this->xindex]<<endl;

        glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);
    }



};


#endif // PIECE_H
