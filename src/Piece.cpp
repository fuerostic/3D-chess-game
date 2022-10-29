#include "Piece.h"

//Piece::~Piece()
//{
//    //dtor
//}

const int king_moves[2][8] = {{0,0,1,1,1,-1,-1,-1},{1,-1,0,1,-1,0,1,-1}};
const int queen_moves[2][8] = {{0,0,1,1,1,-1,-1,-1},{1,-1,0,1,-1,0,1,-1}};
const int bishop_moves[2][4] = {{1,1,-1,-1}, {1,-1,1,-1} };
const int knight_moves[2][8] = { {1,1,2,2,-1,-1,-2,-2}, {2,-2,1,-1,2,-2,1,-1} };
const int rook_moves[2][4] = { {0,0,1,-1}, {1,-1,0,0} };
const int pawn_moves[2][3] = { {0,-1,1}, {1,1,1} };

GLfloat pos_x[8] = {-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5};
GLfloat pos_y[8] = {-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5};
//GLfloat scored_lobby_p1[2][16]= {{-6.5,-6.5,-6.5,-6.5,-6.5,-6.5,-6.5,-6.5,-7.5,-7.5,-7.5,-7.5,-7.5,-7.5,-7.5,-7.5},{-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5,-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5}};
//GLfloat scored_lobby_p2[2][16]= {{6.5,6.5,6.5,6.5,6.5,6.5,6.5,6.5,7.5,7.5,7.5,7.5,7.5,7.5,7.5,7.5},{-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5,-3.5,-2.5,-1.5,-0.5,0.5,1.5,2.5,3.5}};
GLfloat x_diff[] = {0.55,0.6,0.63,0.7,0.7,0.7,0.8,0.82};
GLfloat y_diff[] = {0.23,0.25,0.3,0.3,0.35,0.4,0.4,0.45};

GLfloat x_start_points[] = {-2.37,-2.48,-2.59,-2.72,-2.85,-3,-3.21,-3.42,-3.61};
GLfloat y_start_points[] = {4,3.77,3.51,3.21,2.91,2.57,2.17,1.78,1.30};

int score_by_id[32]={5,3,3,9,100,3,3,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,3,3,9,100,3,3,5};


float color[]= {1.0,1.0,1.0};
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { color[0]*.3, color[1]*.3, color[2]*.3,1.0 };
GLfloat mat_diffuse[] = { color[0], color[1], color[2], 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = {60};


//static int position[8][8];
//static int valid_places[8][8];
//static int scoring_position[8][8];
//static int selected_position[8][8];



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




void drawCube(float length,float shine)
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

        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glTexCoord2f(0,1);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
        glTexCoord2f(1,1);
    }
    glEnd();

//    glPushMatrix();
//    glTranslatef(.5,.5,.5);
//    glutSolidCube(length);
//    glPopMatrix();


}
