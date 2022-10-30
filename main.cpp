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
#include "include/Game.h"

using namespace std;


double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1366, windowWidth=768;
GLboolean bRotate = false, uRotate = false;
GLfloat gscale=1,cdist=0,fdist=0; //zooming constant
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;

GLfloat x=0,y=0,z=0,roll=0,pitch=0, yaw=0,eyex= 0,eyey=10,eyez=7,dx=0,dy=0,dz=0,xaxis=0,yaxis=1,zaxis=0;

//float color[]={1.0,1.0,1.0};
//GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//GLfloat mat_ambient[] = { color[0]*.3, color[1]*.3, color[2]*.3,1.0 };
//GLfloat mat_diffuse[] = { color[0], color[1], color[2], 1.0 };
//GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//GLfloat mat_shininess[] = {60};

GLuint ID[]={1,2,3,4,5,6};

int p1_caught=0;
int p2_caught=0;

//GLfloat pos_x[8] ={-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5};
//GLfloat pos_y[8] ={-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5};
////GLfloat scored_lobby_p1[2][16]= {{-6.5,-6.5,-6.5,-6.5,-6.5,-6.5,-6.5,-6.5,-7.5,-7.5,-7.5,-7.5,-7.5,-7.5,-7.5,-7.5},{-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5,-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5}};
////GLfloat scored_lobby_p2[2][16]= {{6.5,6.5,6.5,6.5,6.5,6.5,6.5,6.5,7.5,7.5,7.5,7.5,7.5,7.5,7.5,7.5},{-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5,-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5}};
//GLfloat x_diff[] = {0.55,0.6,0.63,0.7,0.7,0.7,0.8,0.82};
//GLfloat y_diff[] = {0.23,0.25,0.3,0.3,0.35,0.4,0.4,0.45};
//
//GLfloat x_start_points[] = {-2.37,-2.48,-2.59,-2.72,-2.85,-3,-3.21,-3.42,-3.61};
//GLfloat y_start_points[] = {4,3.77,3.51,3.21,2.91,2.57,2.17,1.78,1.30};


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




//
//static int position[8][8];
//static int valid_places[8][8];
//static int scoring_position[8][8];
//static int selected_position[8][8];



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


void textDisplay( int x, int y, char *st)
{
    int l,i;

    l=strlen( st ); // see how many characters are in text string.
    glRasterPos2i( x, y); // location to start printing text
    glColor3f(1,0,0);
    for( i=0; i <l;  i++)  // loop until i is greater then l
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]); // Print a character on the screen
    }
}


Game game;

//Board board;



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
            //cout<<x<<endl;
            xpos= i;
        }

        //cout<<endl<<(x_start_points[ypos]+ (i*x_diff[ypos]))<<" " <<(x_start_points[ypos]+ ((i+1)*x_diff[ypos])) <<endl;
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


    if(position[ypos][xpos]==-1 && !game.getBoard().getSelected().empty())
    {
        Piece piece = game.getBoard().getSelected().top();

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
            game.getBoard().getSelected().pop();
            game.getBoard().getPiece(piece.getID()).setSelected(false);
            game.getBoard().movePiece(xpos,ypos,piece.getID());
            position[ypos][xpos] = piece.getID();
            position[piece.getYindex()][piece.getXindex()] = -1;

            game.getBoard().changeTurn();

            //cout<<"moved to "<<xpos<<" "<<ypos<<endl;
        }
        else
            return;


    }
    else if(position[ypos][xpos]!=-1 && !game.getBoard().getSelected().empty())
    {

        if((game.getBoard().getPiece(position[ypos][xpos]).isComputer() && game.getBoard().isComputerTurn()) || (!game.getBoard().getPiece(position[ypos][xpos]).isComputer() && !game.getBoard().isComputerTurn()))
        {
            Piece piece = game.getBoard().getSelected().top();
            game.getBoard().getSelected().pop();
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
//            else if(find(scores.begin(), scores.end(), i) != scores.end())
//            {
//
//                Piece piece2 = game.getBoard().getPiece(position[ypos][xpos]);
//                piece2.setCaught(true);
//                if(piece2.isComputer())
//                {
//                    game.getBoard().getPlayer(1).setPiecesLeft(game.getBoard().getPlayer(1).getPiecesLeft()-1);
//                    game.getBoard().getPlayer(2).setScore(game.getBoard().getPlayer(2).getScore()+ piece2.getScore());
//                    p1_caught++;
//                }
//                else
//                {
//                    game.getBoard().getPlayer(2).setPiecesLeft(game.getBoard().getPlayer(2).getPiecesLeft()-1);
//                    game.getBoard().getPlayer(1).setScore(game.getBoard().getPlayer(1).getScore()+ piece2.getScore());
//                    p2_caught++;
//                }
//
//                cout<<endl<<"Player 1 pieces left "<<game.getBoard().getPlayer(1).getPiecesLeft()<<endl;
//                cout<<endl<<"Player 2 pieces left "<<game.getBoard().getPlayer(2).getPiecesLeft()<<endl;
//
//
//                cout<<endl<<"Player 1 score "<<game.getBoard().getPlayer(1).getScore()<<endl;
//                cout<<endl<<"Player 2 score "<<game.getBoard().getPlayer(2).getScore()<<endl;
//
//
//                //selected.pop();
//                game.getBoard().getPiece(piece.getID()).setSelected(false);
//                game.getBoard().movePiece(xpos,ypos,piece.getID());
//                position[ypos][xpos] = piece.getID();
//                position[piece.getYindex()][piece.getXindex()] = -1;
//
//                game.changeTurn();
//
//
//                //cout<<"reached 2"<<endl;
//
//
//            }
            else
            {
                game.getBoard().getPiece(piece.getID()).setSelected(false);
                game.getBoard().getPiece(position[ypos][xpos]).setSelected(true);
                Piece piece2 = game.getBoard().getPiece(position[ypos][xpos]);
                game.getBoard().getSelected().push(piece2);
            }
        }

        else if((!game.getBoard().getPiece(position[ypos][xpos]).isComputer() && game.getBoard().isComputerTurn()) || (game.getBoard().getPiece(position[ypos][xpos]).isComputer() && !game.getBoard().isComputerTurn()))
        {
            Piece piece = game.getBoard().getSelected().top();
            game.getBoard().getSelected().pop();
            piece.resetValidMoves();
            piece.calculate_valid_moves();



            vector <pair<int,int>> valids = piece.getValidMoves();
            vector <pair<int,int>> scores = piece.getScoringMoves();
            pair<int,int> i = make_pair(xpos,ypos);

            if(find(scores.begin(), scores.end(), i) != scores.end())
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

                game.getBoard().changeTurn();


                //cout<<"reached 2"<<endl;


            }
            else
            {
//                Piece piece = selected.top();
//                selected.pop();
                game.getBoard().getPiece(piece.getID()).setSelected(false);
            }

        }



        //cout<<"selected "<<xpos<<" "<<ypos<<endl;
    }

    else if(position[ypos][xpos]!=-1 && game.getBoard().getSelected().empty())
    {
        if((game.getBoard().getPiece(position[ypos][xpos]).isComputer() && game.getBoard().isComputerTurn()) || (!game.getBoard().getPiece(position[ypos][xpos]).isComputer() && !game.getBoard().isComputerTurn()))
        {
            game.getBoard().getPiece(position[ypos][xpos]).setSelected(true);
            Piece piece2 = game.getBoard().getPiece(position[ypos][xpos]);
            game.getBoard().getSelected().push(piece2);

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


    game.getBoard().updatePosition();

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

    textDisplay(5,5,"game is on");

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

    //glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
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

    //Board board;

    light();

    glutKeyboardFunc(myKeyboardFunc);
    glutMouseFunc(processMouse);
    //glutFullScreen();
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
