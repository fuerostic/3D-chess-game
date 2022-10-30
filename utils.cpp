#include "utils.h"


vector<pair<pair<int,int>,pair<int,int> > > calculate_all_valid_moves(Board board,bool stat)
{
    const int king_moves[2][8] = {{0,0,1,1,1,-1,-1,-1},{1,-1,0,1,-1,0,1,-1}};
    const int queen_moves[2][8] = {{0,0,1,1,1,-1,-1,-1},{1,-1,0,1,-1,0,1,-1}};
    const int bishop_moves[2][4] = {{1,1,-1,-1}, {1,-1,1,-1} };
    const int knight_moves[2][8] = { {1,1,2,2,-1,-1,-2,-2}, {2,-2,1,-1,2,-2,1,-1} };
    const int rook_moves[2][4] = { {0,0,1,-1}, {1,-1,0,0} };
    const int pawn_moves[2][3] = { {0,-1,1}, {1,1,1} };

    vector<Piece> pieces = board.getPieces();
    vector<pair<pair<int,int>,pair<int,int> > >scores;
    vector<vector<int>>pos = board.getPosition();


    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(pos[i][j]!=-1)
            {
                pieces[pos[i][j]].setXindex(i);
                pieces[pos[i][j]].setXindex(j);
            }
        }
    }


    for(Piece piece: pieces)
    {

        if(stat && piece.getID()>15)
        {
            continue;
        }
        else if(!stat && piece.getID()<16)
        {
            continue;
        }


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


Game calculate_index(GLfloat x, GLfloat y,Game game)
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
        return game;
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
        return game;
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
            return game;


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
                    //p1_caught++;
                }
                else
                {
                    game.getBoard().getPlayer(2).setPiecesLeft(game.getBoard().getPlayer(2).getPiecesLeft()-1);
                    game.getBoard().getPlayer(1).setScore(game.getBoard().getPlayer(1).getScore()+ piece2.getScore());
                    //p2_caught++;
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

    return game;

}

