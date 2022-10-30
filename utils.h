




vector<pair<pair<int,int>,pair<int,int> > > calculate_valid_moves(Board board)
{
    const int king_moves[2][8] = {{0,0,1,1,1,-1,-1,-1},{1,-1,0,1,-1,0,1,-1}};
    const int queen_moves[2][8] = {{0,0,1,1,1,-1,-1,-1},{1,-1,0,1,-1,0,1,-1}};
    const int bishop_moves[2][4] = {{1,1,-1,-1}, {1,-1,1,-1} };
    const int knight_moves[2][8] = { {1,1,2,2,-1,-1,-2,-2}, {2,-2,1,-1,2,-2,1,-1} };
    const int rook_moves[2][4] = { {0,0,1,-1}, {1,-1,0,0} };
    const int pawn_moves[2][3] = { {0,-1,1}, {1,1,1} };

    vector<Piece> pieces = board.getPieces();
    vector<pair<pair<int,int>,pair<int,int> > >scores;
    vector<vector<int>> pos = board.getPosition();


    for(Piece piece: pieces)
    {
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

                    scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));

                }
                else
                {
                    if(pos[tempy][tempx]<16 && pos[tempy][tempx]!=-1 && piece.getID()>=16 && i!=0)
                    {

                        scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
                        break;
                    }
                    else if(pos[tempy][tempx]>=16 && piece.getID()<16 && i!=0)
                    {

                        scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
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

                        scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
                    }
                    else
                    {
                        if(pos[tempy][tempx]<16 && piece.getID()>=16)
                        {
                            scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
                            break;
                        }
                        else if(pos[tempy][tempx]>=16 && piece.getID()<16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
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

                        scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
                    }
                    else
                    {
                        if(pos[tempy][tempx]<16 && piece.getID()>=16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
                            break;
                        }
                        else if(pos[tempy][tempx]>=16 && piece.getID()<16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
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

                        scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
                    }
                    else
                    {
                        if(pos[tempy][tempx]<16 && piece.getID()>=16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
                            break;
                        }
                        else if(pos[tempy][tempx]>=16 && piece.getID()<16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
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

                        scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
                    }
                    else
                    {
                        if(pos[tempy][tempx]<16 && piece.getID()>=16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
                            break;
                        }
                        else if(pos[tempy][tempx]>=16 && piece.getID()<16)
                        {

                            scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
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

                    scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
                }
                else
                {
                    if(pos[tempy][tempx]<16 && piece.getID()>=16)
                    {

                        scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
                        break;
                    }
                    else if(pos[tempy][tempx]>=16 && piece.getID()<16)
                    {

                        scores.push_back(make_pair(make_pair(tempx,tempy),make_pair(piece.getXindex(),piece.getYindex())));
                        break;
                    }
                }
            }
        }

    }

    return scores;

}
