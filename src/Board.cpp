#include "Board.h"


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
    if (depth==0 || board.isGameOver())
    {
        return make_pair(make_pair(make_pair(-1,-1), make_pair(-1,-1)),evaluate(board,isComputerMax));
    }

    vector<pair< pair<int,int>,pair<int,int> >> moves = board.get_all_moves();
    pair< pair<int,int>,pair<int,int> > best_move = moves[0];



    if(isComputerMax)
    {
        int max_eval = -100000;

        for(pair< pair<int,int>,pair<int,int> > m:moves)
        {
            Board temp_board = board;

            board = board.make_move(m.first,m.second,board);

            pair<pair<pair<int,int>,pair<int,int>>,int>  out = minimax(board,depth-1,false,alpha,beta);

            int current_eval = out.second;

            board = temp_board;

            if (current_eval>max_eval)
            {
                max_eval = current_eval;
                best_move = m;
            }

            alpha = max(alpha,current_eval);

            if (beta<=alpha)
            {
                break;
            }

        }

        return make_pair(best_move,max_eval);

    }
    else
    {
        int min_eval = 100000;

        for(pair< pair<int,int>,pair<int,int> > m:moves)
        {
            Board temp_board = board;

            board = board.make_move(m.first,m.second,board);

            pair<pair<pair<int,int>,pair<int,int>>,int>  out = minimax(board,depth-1,false,alpha,beta);

            int current_eval = out.second;

            board = temp_board;

            if (current_eval<min_eval)
            {
                min_eval = current_eval;
                best_move = m;
            }

            beta = min(beta,current_eval);

            if(beta<=alpha)
            {
                break;
            }

        }

        return make_pair(best_move,min_eval);
    }


}
