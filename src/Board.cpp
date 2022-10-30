#include "../include/Board.h"
#include "../utils.h"
#include "random"


extern int evaluate(Board board, bool computerIsMax)
{
    if(computerIsMax)
    {
        return board.getPlayer(1).getScore()- board.getPlayer(2).getScore();
    }
    else
    {
        return board.getPlayer(2).getScore()- board.getPlayer(1).getScore();
    }
}

extern pair<pair<pair<int,int>,pair<int,int>>,int>  minimax(Board board, int depth,bool isComputerMax,int alpha,int beta)
{


    cout<<depth<<endl;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            cout<<board.getPosition()[i][j]<<" ";
        }
        cout<<endl;
    }

    if (depth==0 || board.isGameOver())
    {
        return make_pair(make_pair(make_pair(-1,-1), make_pair(-1,-1)),evaluate(board,isComputerMax));
    }

    vector<pair< pair<int,int>,pair<int,int> >> moves =calculate_all_valid_moves(board,isComputerMax);


    int minx= 0,maxx=moves.size();
    int r = minx + (rand() % static_cast<int>(maxx - minx + 1));
    cout<<"moves count:"<<moves.size()<<endl;

    pair< pair<int,int>,pair<int,int> > best_move = moves[r];

    if(isComputerMax)
    {
        //int max_eval = -INFINITE;
        int current_eval = -INFINITE;

        for(pair< pair<int,int>,pair<int,int> > m:moves)
        {
            Board temp_board = board;

            board = board.make_move(m.first,m.second,board);

            pair<pair<pair<int,int>,pair<int,int>>,int>  out = minimax(board,depth-1,false,alpha,beta);

            //int current_eval = out.second;

            current_eval = max(out.second,current_eval);

            board = temp_board;

            if (current_eval>=beta)
            {
                break;
            }

            if(current_eval>=alpha)
            {
                alpha = max(alpha,current_eval);
                best_move = m;
            }



//            if (current_eval>max_eval)
//            {
//                max_eval = current_eval;
//                best_move = m;
//            }
//
//            alpha = max(alpha,current_eval);
//
//            if (beta<=alpha)
//            {
//                break;
//            }

        }

        //return make_pair(best_move,max_eval);
        return make_pair(best_move,current_eval);

    }
    else
    {
        //int min_eval = INFINITE;
        int current_eval = INFINITE;

        for(pair< pair<int,int>,pair<int,int> > m:moves)
        {
            Board temp_board = board;

            board = board.make_move(m.first,m.second,board);

            pair<pair<pair<int,int>,pair<int,int>>,int>  out = minimax(board,depth-1,true,alpha,beta);

            current_eval = min(out.second,current_eval);

            board = temp_board;

            if (current_eval<=alpha)
            {
                break;
            }

            if(current_eval<beta)
            {
                alpha = min(beta,current_eval);
                best_move = m;
            }

//            if (current_eval<min_eval)
//            {
//                min_eval = current_eval;
//                best_move = m;
//            }
//
//            beta = min(beta,current_eval);
//
//            if(beta<=alpha)
//            {
//                break;
//            }

        }

        return make_pair(best_move,current_eval);
    }


}
