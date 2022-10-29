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
#include "BmpLoader.h"

using namespace std;


double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1366, windowWidth=768;
GLboolean bRotate = false, uRotate = false;
GLfloat gscale=1,cdist=0,fdist=0; //zooming constant
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;

GLfloat x=0,y=0,z=0,roll=0,pitch=0, yaw=0,eyex= 0,eyey=10,eyez=7,dx=0,dy=0,dz=0,xaxis=0,yaxis=1,zaxis=0;

float color[]={1.0,1.0,1.0};
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { color[0]*.3, color[1]*.3, color[2]*.3,1.0 };
GLfloat mat_diffuse[] = { color[0], color[1], color[2], 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = {60};

GLuint ID[]={1,2,3,4,5,6};

int p1_caught=0;
int p2_caught=0;

GLfloat pos_x[8] ={-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5};
GLfloat pos_y[8] ={-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5};
//GLfloat scored_lobby_p1[2][16]= {{-6.5,-6.5,-6.5,-6.5,-6.5,-6.5,-6.5,-6.5,-7.5,-7.5,-7.5,-7.5,-7.5,-7.5,-7.5,-7.5},{-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5,-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5}};
//GLfloat scored_lobby_p2[2][16]= {{6.5,6.5,6.5,6.5,6.5,6.5,6.5,6.5,7.5,7.5,7.5,7.5,7.5,7.5,7.5,7.5},{-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5,-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5}};
GLfloat x_diff[] = {0.55,0.6,0.63,0.7,0.7,0.7,0.8,0.82};
GLfloat y_diff[] = {0.23,0.25,0.3,0.3,0.35,0.4,0.4,0.45};

GLfloat x_start_points[] = {-2.37,-2.48,-2.59,-2.72,-2.85,-3,-3.21,-3.42,-3.61};
GLfloat y_start_points[] = {4,3.77,3.51,3.21,2.91,2.57,2.17,1.78,1.30};


int anglex= 0, angley = 0, anglez = 0;          //rotation angles
int window;
int wired=0;
int shcpt=1;
int animat = 0;
const int L=20;
const int dgre=3;
int ncpt=L+1;
int clikd=0;
const int nt = 40;				//number of slices along x-direction
const int ntheta = 20;


const int king_moves[2][8] = {{0,0,1,1,1,-1,-1,-1},{1,-1,0,1,-1,0,1,-1}};
const int queen_moves[2][8] = {{0,0,1,1,1,-1,-1,-1},{1,-1,0,1,-1,0,1,-1}};
const int bishop_moves[2][4] = {{1,1,-1,-1}, {1,-1,1,-1} };
const int knight_moves[2][8] = { {1,1,2,2,-1,-1,-2,-2}, {2,-2,1,-1,2,-2,1,-1} };
const int rook_moves[2][4] = { {0,0,1,-1}, {1,-1,0,0} };
const int pawn_moves[2][3] = { {0,-1,1}, {1,1,1} };




static int position[8][8];
static int valid_places[8][8];
static int scoring_position[8][8];
static int selected_position[8][8];


int id_set_close[16]= {16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
int id_set_far[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

double ex=0, ey=0, ez=15, lx=0,ly=0,lz=0, hx=0,hy=1,hz=0;

float wcsClkDn[3],wcsClkUp[3];
///////////////////////////////
class point1
{
public:
    point1()
    {
        x=0;
        y=0;
    }
    int x;
    int y;
} clkpt[2];
int flag=0;
GLint viewport[4]; //var to hold the viewport info
GLdouble modelview[16]; //var to hold the modelview info
GLdouble projection[16]; //var to hold the projection matrix info


//////////////////////////
void scsToWcs(float sx,float sy, float wcsv[3] );
void processMouse(int button, int state, int x, int y);
void matColor(float kdr, float kdg, float kdb,  float shiny, int frnt_Back=0, float ambFactor=1.0, float specFactor=1.0);


class Board;
class Piece;
class Spot;
class Player;


static void getNormal3p(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}


void drawCube(float length,float shine=60)
{

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);



    static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, length}, //1
    {length, 0.0, 1.0}, //2
    {length, 0.0, 0.0}, //3
    {0.0, length, 0.0}, //4
    {0.0, length, length}, //5
    {length, length, length}, //6
    {length, length, 0.0}  //7
};

    static GLubyte quadIndices[6][4] =
    {
        {0, 1, 2, 3}, //bottom
        {4, 5, 6, 7}, //top
        {5, 1, 2, 6}, //front
        {0, 4, 7, 3}, // back is clockwise
        {2, 3, 7, 6}, //right
        {1, 5, 4, 0}  //left is clockwise
    };


    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
//        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
//        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
//        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
//        glVertex3fv(&v_cube[quadIndices[i][3]][0]);

        glVertex3fv(&v_cube[quadIndices[i][0]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);glTexCoord2f(1,1);
    }
    glEnd();

//    glPushMatrix();
//    glTranslatef(.5,.5,.5);
//    glutSolidCube(length);
//    glPopMatrix();


}

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

public:
    Player(int id,bool computer,bool white)
    {
        this->player_ID = id;
        this->computer = computer;
        this->score=0;
        this->scored_pieces=0;
        this->pieces_left=16;
        this->win =false;
        this->checkmate= false;
        this->white = white;

        if(this->computer)
        {
            copy(this->piece_set,this->piece_set+16, id_set_far);
        }
        else
        {
            copy(this->piece_set,this->piece_set+16, id_set_close);
        }
    }

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
    int direction = 1;
    bool caught;
    bool computer;

public:

    Piece(int ID,bool white,bool computer)
    {
        this->ID = ID;
        this->white = white;
        this->caught = false;
        this->computer = computer;
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
        else{
            this->score = 100;
        }

    }

    vector<pair<int,int>> getValidMoves()
    {
        return this->valid_moves;
    }

    vector<pair<int,int>> getScoringMoves()
    {
        return this->scoring_moves;
    }

    void resetValidMoves()
    {
        valid_moves.clear();
        scoring_moves.clear();
    }
    void calculate_valid_moves()
    {
        int tempx;
        int tempy;

        if((this->ID>=8 && this->ID<16) || (this->ID>=16 && this->ID<24))
        {
            for(int i =0;i<3;i++)
            {
                tempx = this->xindex + pawn_moves[0][i];
                tempy = this->yindex + (this->direction * pawn_moves[1][i]);


                if ((tempx<0 || tempy <0 || tempx>8 || tempy>8 || (position[tempy][tempx]<16  && position[tempy][tempx]!=-1  && this->ID<16) || (position[tempy][tempx]>=16 && this->ID>=16)) && position[tempy][tempx]!=-1 )
                {
                    continue;
                }

                else if(position[tempy][tempx]==-1 && i==0)
                {
                    this->valid_moves.push_back(make_pair(tempx,tempy));
                }
                else
                {
                    if(position[tempy][tempx]<16 && position[tempy][tempx]!=-1 && this->ID>=16 && i!=0)
                    {
                        this->scoring_moves.push_back(make_pair(tempx,tempy));
                    }
                    else if(position[tempy][tempx]>=16 && this->ID<16 && i!=0)
                    {
                        this->scoring_moves.push_back(make_pair(tempx,tempy));
                    }
                }
            }
        }
        else if(this->ID==0 || this->ID==7 || this->ID==24 || this->ID==31)
        {


                for(int i =0;i<4;i++)
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
                        }
                        else
                        {
                            if(position[tempy][tempx]<16 && this->ID>=16)
                            {
                                this->scoring_moves.push_back(make_pair(tempx,tempy));
                                break;
                            }
                            else if(position[tempy][tempx]>=16 && this->ID<16)
                            {
                                this->scoring_moves.push_back(make_pair(tempx,tempy));
                                break;
                            }
                        }


                    traverse++;
                    }



                }
        }
        else if(this->ID==2 || this->ID==5 ||  this->ID==26 ||this->ID==29 )
        {

                for(int i =0;i<4;i++)
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
                    }
                    else
                    {
                        if(position[tempy][tempx]<16 && this->ID>=16)
                        {
                            this->scoring_moves.push_back(make_pair(tempx,tempy));
                            break;
                        }
                        else if(position[tempy][tempx]>=16 && this->ID<16)
                        {
                            this->scoring_moves.push_back(make_pair(tempx,tempy));
                            break;
                        }
                    }

                    traverse++;
                }



            }
        }
        else if(this->ID==1 ||  this->ID==6 ||  this->ID==25 ||  this->ID==30)
        {


                for(int i =0;i<8;i++)
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
                    }
                    else
                    {
                        if(position[tempy][tempx]<16 && this->ID>=16)
                        {
                            this->scoring_moves.push_back(make_pair(tempx,tempy));
                            break;
                        }
                        else if(position[tempy][tempx]>=16 && this->ID<16)
                        {
                            this->scoring_moves.push_back(make_pair(tempx,tempy));
                            break;
                        }
                    }

                    traverse++;
                }



            }
        }
        else if(this->ID==3 || this->ID==27)
        {

                for(int i =0;i<8;i++)
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
                    }
                    else
                    {
                        if(position[tempy][tempx]<16 && this->ID>=16)
                        {
                            this->scoring_moves.push_back(make_pair(tempx,tempy));
                            break;
                        }
                        else if(position[tempy][tempx]>=16 && this->ID<16)
                        {
                            this->scoring_moves.push_back(make_pair(tempx,tempy));
                            break;
                        }
                    }
                    traverse++;
                }

            }
        }
        else{
            for(int i =0;i<8;i++)
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
                }
                else
                {
                    if(position[tempy][tempx]<16 && this->ID>=16)
                    {
                        this->scoring_moves.push_back(make_pair(tempx,tempy));
                        break;
                    }
                    else if(position[tempy][tempx]>=16 && this->ID<16)
                    {
                        this->scoring_moves.push_back(make_pair(tempx,tempy));
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
        else{

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

class Board
{
private:
    bool white;
    Player player1 =  Player(1,true,true);
    Player player2 =  Player(2,false,false);

    bool board_filled[8][8] = {{true,true,true,true,true,true,true,true},{true,true,true,true,true,true,true,true},
    {false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},
    {false,false,false,false,false,false,false,false},{false,false,false,false,false,false,false,false},
    {true,true,true,true,true,true,true,true},{true,true,true,true,true,true,true,true}};

    Piece pieces[32] = {  Piece(0,true,true),Piece(1,true,true),Piece(2,true,true),Piece(3,true,true),
                        Piece(4,true,true),Piece(5,true,true),Piece(6,true,true),Piece(7,true,true),
                        Piece(8,true,true),Piece(9,true,true),Piece(10,true,true),Piece(11,true,true),
                        Piece(12,true,true),Piece(13,true,true),Piece(14,true,true),Piece(15,true,true),
                        Piece(16,false,false),Piece(17,false,false),Piece(18,false,false),Piece(19,false,false),
                        Piece(20,false,false),Piece(21,false,false),Piece(22,false,false),Piece(23,false,false),
                        Piece(24,false,false),Piece(25,false,false),Piece(26,false,false),Piece(27,false,false),
                        Piece(28,false,false),Piece(29,false,false),Piece(30,false,false),Piece(31,false,false)};

public:

    Board()
    {


        int counter= 0;

        for (int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                position[i][j] = -1;
                valid_places[i][j] = -1;
                scoring_position[i][j] = -1;
                selected_position[i][j] = -1;
            }
        }

        bool white = true;

        for( int i=0;i<8;i++)
        {
            for( int j=0;j<8;j++)
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

        for( int i=0;i<8;i++)
        {
            for( int j=0;j<8;j++)
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

        for(int i=0;i<10;i++)
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

        for(int i=0;i<10;i++)
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

Game game;

//Board board;

stack<Piece>selected;

void calculate_index(GLfloat x, GLfloat y)
{


    int xpos = -1,ypos = -1;

    for(int j=0;j<8;j++)
    {
        if(y>=y_start_points[j+1] && y<y_start_points[j])
        {
            ypos=j;
            break;
        }
    }

    if(ypos==-1)
    {
        //cout<<endl<<"invalid point y"<<endl;
        return;
    }
    //cout<<endl<<ypos<<endl;

    for (int i=0;i<8;i++)
    {
        if(x>= (x_start_points[ypos]+ (i*x_diff[ypos])) && x<(x_start_points[ypos]+ ((i+1)*x_diff[ypos])))
        {
            cout<<x<<endl;
            xpos= i;
        }

        cout<<endl<<(x_start_points[ypos]+ (i*x_diff[ypos]))<<" " <<(x_start_points[ypos]+ ((i+1)*x_diff[ypos])) <<endl;
    }



    if(xpos==-1)
    {
        //cout<<"invalid point"<<endl;
        return;
    }
    else
    {
            //cout<<endl<<"X: "<<xpos<<"Y: "<<ypos<<endl;
    }


    if(position[ypos][xpos]==-1 && !selected.empty())
    {
        Piece piece = selected.top();

        piece.resetValidMoves();
        piece.calculate_valid_moves();

        vector <pair<int,int>> valids = piece.getValidMoves();
        vector <pair<int,int>> scores = piece.getScoringMoves();

        pair<int,int> i = make_pair(xpos,ypos);

        //cout<<"move on : " <<i.first <<" "<<i.second<<endl;
        //cout<<"valids"<<endl;
//        for(pair<int,int> j: valids)
//        {
//            cout<< j.first<<" "<<j.second<<endl;
//        }

        if (find(valids.begin(), valids.end(), i) != valids.end())
        {
            selected.pop();
            game.getBoard().getPiece(piece.getID()).setSelected(false);
            game.getBoard().movePiece(xpos,ypos,piece.getID());
            position[ypos][xpos] = piece.getID();
            position[piece.getYindex()][piece.getXindex()] = -1;

            game.changeTurn();

            //cout<<"moved to "<<xpos<<" "<<ypos<<endl;
        }
        else
            return;


    }
    else if(position[ypos][xpos]!=-1 && !selected.empty())
    {

        if((game.getBoard().getPiece(position[ypos][xpos]).isComputer() && game.isComputerTurn()) || (!game.getBoard().getPiece(position[ypos][xpos]).isComputer() && !game.isComputerTurn()))
        {
            Piece piece = selected.top();
            selected.pop();
            piece.resetValidMoves();
            piece.calculate_valid_moves();



            vector <pair<int,int>> valids = piece.getValidMoves();
            vector <pair<int,int>> scores = piece.getScoringMoves();
            pair<int,int> i = make_pair(xpos,ypos);

            //cout<<"reached 1"<<endl;

            if(piece.getXindex()==xpos && piece.getYindex()==ypos)
            {
                game.getBoard().getPiece(piece.getID()).setSelected(false);
            }
            else if(find(scores.begin(), scores.end(), i) != scores.end())
            {

                Piece piece2 = game.getBoard().getPiece(position[ypos][xpos]);
                piece2.setCaught(true);
                if(piece2.isComputer())
                {
                    game.getBoard().getPlayer(1).setPiecesLeft(game.getBoard().getPlayer(1).getPiecesLeft()-1);
                    game.getBoard().getPlayer(2).setScore(game.getBoard().getPlayer(2).getScore()+ piece2.getScore());
                    p1_caught++;
                }
                else
                {
                    game.getBoard().getPlayer(2).setPiecesLeft(game.getBoard().getPlayer(2).getPiecesLeft()-1);
                    game.getBoard().getPlayer(1).setScore(game.getBoard().getPlayer(1).getScore()+ piece2.getScore());
                    p2_caught++;
                }

                cout<<endl<<"Player 1 pieces left "<<game.getBoard().getPlayer(1).getPiecesLeft()<<endl;
                cout<<endl<<"Player 2 pieces left "<<game.getBoard().getPlayer(2).getPiecesLeft()<<endl;


                cout<<endl<<"Player 1 score "<<game.getBoard().getPlayer(1).getScore()<<endl;
                cout<<endl<<"Player 2 score "<<game.getBoard().getPlayer(2).getScore()<<endl;


                //selected.pop();
                game.getBoard().getPiece(piece.getID()).setSelected(false);
                game.getBoard().movePiece(xpos,ypos,piece.getID());
                position[ypos][xpos] = piece.getID();
                position[piece.getYindex()][piece.getXindex()] = -1;

                game.changeTurn();


                //cout<<"reached 2"<<endl;


            }
            else
            {
                game.getBoard().getPiece(piece.getID()).setSelected(false);
                game.getBoard().getPiece(position[ypos][xpos]).setSelected(true);
                Piece piece2 = game.getBoard().getPiece(position[ypos][xpos]);
                selected.push(piece2);
            }
        }



        //cout<<"selected "<<xpos<<" "<<ypos<<endl;
    }

    else if(position[ypos][xpos]!=-1 && selected.empty())
    {
        if((game.getBoard().getPiece(position[ypos][xpos]).isComputer() && game.isComputerTurn()) || (!game.getBoard().getPiece(position[ypos][xpos]).isComputer() && !game.isComputerTurn()))
        {
            game.getBoard().getPiece(position[ypos][xpos]).setSelected(true);
            Piece piece2 = game.getBoard().getPiece(position[ypos][xpos]);
            selected.push(piece2);

        }

        //cout<<"selected "<<xpos<<" "<<ypos<<endl;
    }

//    for(int i=0;i<8;i++)
//    {
//        for(int j=0;j<8;j++)
//        {
//            cout<<position[i][j]<<" " ;
//        }
//        cout<<endl;
//    }

}

void scsToWcs(float sx,float sy, float wcsv[3] )
{

    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
    GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
    glGetDoublev( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info

    winX = sx;
    winY = (float)viewport[3] - (float)sy;
    winZ = 0;

    //get the world coordinates from the screen coordinates
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
    wcsv[0]=worldX;
    wcsv[1]=worldY;
    wcsv[2]=worldZ;


}

void processMouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(flag!=1)
        {
            flag=1;
            clkpt[0].x=x;
            clkpt[0].y=y;
        }


        scsToWcs(clkpt[0].x,clkpt[0].y,wcsClkDn);
        calculate_index(wcsClkDn[0],wcsClkDn[1]);
        //cout<<"\nD: "<<x<<" "<<y<<" "<<z<<" wcs: "<<wcsClkDn[0]<<" "<<wcsClkDn[1]<<" "<<wcsClkDn[2]<<endl;


    }
    else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if (flag==1)
        {
            clkpt[1].x=x;
            clkpt[1].y=y;
            flag=0;
        }
        float wcs[3];
        scsToWcs(clkpt[1].x,clkpt[1].y,wcsClkUp);
        //cout<<"\nU: "<<x<<" "<<y<<" "<<z<<" wcs: "<<wcsClkUp[0]<<" "<<wcsClkUp[1]<<" "<<wcsClkUp[2];

        clikd=!clikd;
    }
}



//void game()
//{
//
//    //Board board;
//
//    glPushMatrix();
//    game.getBoard().draw();
//    glPopMatrix();
//
//}



void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {

    //object zooming
    case 'z':
        gscale+=.2;
        break;

    case 'x':
        gscale-=.2;
        break;

//viewer zooming

    case 'c':
        cdist+=1;
        break;
    case 'v':
        cdist-=1;
        break;

//window zooming

    case 'n':
        fdist+=1;
        break;

    case 'm':
        fdist-=1;
        break;

    //fanswitch

    case 's':
    case 'S':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;


    case '-':
       Tzval+=1;
        break;

    case '+':
        Tzval-=1;
        break;
    case  'i':
        Tyval+=1;
        break;
    case 'k':
        Tyval-=1;
        break;



    case 27:	// Escape key
        exit(1);
    }
}

void LoadTexture(const char*filename,GLuint ID)
{
    cout<<filename<<endl;
    cout<<ID<<endl;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}


void animate()
{
    if (bRotate == true)
    {
        theta += 10.2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 10.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    glutPostRedisplay();

}

void light()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0, 50.0, 0, 1.0 };

    glEnable( GL_LIGHT0);
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

  /*  GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0); */
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

void display(void)
{

    glClearColor(0.75,0.78,0.815,0.7);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-7, 6, -7, 7, 8, 70);

    //gluPerspective(60,1,5,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyex+cdist,eyey+cdist,eyez+cdist, x+dx,y+dy,z+dz, xaxis,yaxis,zaxis);

    glViewport(0, 0, windowHeight, windowWidth);

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    light();

    glPushMatrix();
    glRotatef(0+ Tzval,0,1,0);
    glRotatef(Tyval,1,0,0);
    glScalef(gscale,gscale,gscale);
    //drawBoard();
    //draw_selection();
    //drawPawn(1);
    //drawRook(1);
    //drawKnight(1);
    //drawBishop(1);
    //drawQueen(1);
    //drawKing(1);
    //game();
    game.getBoard().draw();
    //initialize();

    glPopMatrix();


    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    glFlush();
    glutSwapBuffers();
}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("3D Chess");

    glEnable(GL_TEXTURE_2D);
    for(int i=0;i<sizeof(ID)/sizeof(ID[0]);i++)
    {
        string tex= "C:\\Users\\EON\\Documents\\Codes\\Graphics lab\\3D chess\\textures\\" + to_string(ID[i]) + ".bmp";
        LoadTexture(tex.c_str(),ID[i]);
    }



    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    Board board;

    light();

    glutKeyboardFunc(myKeyboardFunc);
    glutMouseFunc(processMouse);
    //glutFullScreen();
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
