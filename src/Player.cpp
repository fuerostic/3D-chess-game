#include "Player.h"

int id_set_close[16]= {16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
int id_set_far[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};


Player::Player(int id,bool computer,bool white)
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

