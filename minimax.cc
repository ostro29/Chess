#include "minimax.hh"
#include "move.hh"




int score(std::string piece)
{
    if (piece[0] == 'w')
    {
        if (piece == "wpawn")
            return 1;
        if (piece == "wbishop")
            return 3;
        if (piece == "whorse")
            return 3;
        if (piece == "wtower")
            return 5;
        if (piece == "wqueen")
            return 10;
    }
    if (piece[0] == 'b')
    {
        if (piece == "bpawn")
            return -1;
        if (piece == "bbishop")
            return -3;
        if (piece == "bhorse")
            return -3;
        if (piece == "btower")
            return -5;
        if (piece == "bqueen")
            return -10;
    }
    return 0;
}

int total_score(boardt board)
{
    int sum = 0;
    for(size_t i = 0; i < 8; i++)
        for(size_t j = 0; j < 8; j++)
            sum += score(board[i][j]);
    std::pair<int , int> wking = find_king(board , "wking");
    std::pair<int , int> bking = find_king(board , "bking");
    if (check_mate(board , wking.first , wking.second))
        sum += 10000;
    if (check_mate(board , bking.first , bking.second))
        sum -= 10000;
    return sum;
} 

Mtree filltree(boardt board , char player, Mtree &tree , int depth)
{
    if (depth == 0)
        return tree;
    std::cout << "DEPTH " << depth << '\n';
    std::vector<boardt> res1;
    for(size_t i = 0; i < 8; i++)
    {
        for(size_t j = 0; j < 8; j++)
        {
            if (board[i][j] != "" && board[i][j][0] == player)
            {
                std::vector<boardt> res2 = possible_move(board , i , j);
                res1.insert(res1.end() , res2.begin(), res2.end());
            }
        }
    }
    for (auto it = res1.begin() ; it != res1.end() ; it++ , tree.nbchildren_++)
    {
        int score = total_score(*it);
        tree.children_.push_back(Mtree(!player , *it , score));
    }
    char nextplayer = player == 'w' ? 'b' : 'w';
    for (int i = 0; i < tree.nbchildren_; i++)
    {
        filltree(tree.children_[i].board_ , nextplayer, tree.children_[i] , depth - 1);
    }
    return tree;
}

int minimax(Mtree tree, int depth, char player)
{
    if (depth == 0)
        return total_score(tree.board_);

    if (player == 'w')
    {
        int maxeval = -10000;
        for (auto it = tree.children_.begin(); it != tree.children_.end(); it++)
        {
            int eval = minimax(*it , depth - 1, 'b');
            maxeval = std::max(maxeval , eval);
        }
        return maxeval;
    }
    else
    {
        int mineval = 10000;
        for (auto it = tree.children_.begin(); it != tree.children_.end(); it++)
        {
            int eval = minimax(*it , depth - 1, 'w');
            mineval = std::min(mineval , eval);
        }
        return mineval;
    }
    
}

std::pair<int , boardt> minimax2(boardt board, bool player , int depth , int alpha, int beta)
{
    std::pair<int , int> bking = find_king(board , "bking");
    std::pair<int , int> wking = find_king(board , "wking");
    if (depth == 0 || check_mate(board , bking.first , bking.second) || check_mate(board , wking.first , wking.second))
    {   
        return std::make_pair(total_score(board), board);
    }
    std::vector<boardt> res1;
    char p = player ? 'w' : 'b';
    for(size_t i = 0; i < 8; i++)
    {
        for(size_t j = 0; j < 8; j++)
        {
            if (board[i][j] != "" && board[i][j][0] == p)
            {
                std::vector<boardt> res2 = possible_move(board , i , j);
                res1.insert(res1.end() , res2.begin(), res2.end());
            }
        }
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (res1.begin(), res1.end(), std::default_random_engine(seed));
    boardt bestmove;
    int bestmovevalue = player ? -100000 : 100000;

    for (auto it = res1.begin(); it != res1.end(); it++)
    {
        int value = minimax2(*it, !player, depth - 1, alpha , beta).first;


        if (player)
        {
            if (value > bestmovevalue)
            {
                bestmovevalue = value;
                bestmove = *it;
            }
            alpha = std::max(alpha, value);
        } 
        else 
        {
            if (value < bestmovevalue) 
            {
                bestmovevalue = value;
                bestmove = *it;
            }
            beta = std::min(beta , value);
        }
        if (beta <= alpha)
            break;
    }
    return std::make_pair(bestmovevalue, bestmove);
}

std::pair<int , boardt> minimax3(int depth , boardt board , bool IsMax)
{
    if (depth == 0)
    {   
        boardt rboard;
        return std::make_pair(total_score(board), rboard);
    }
    char player = IsMax ? 'w' : 'b';
    std::vector<boardt> res1;
    for(size_t i = 0; i < 8; i++)
    {
        for(size_t j = 0; j < 8; j++)
        {
            if (board[i][j] != "" && board[i][j][0] == player)
            {
                std::vector<boardt> res2 = possible_move(board , i , j);
                res1.insert(res1.end() , res2.begin(), res2.end());
            }
        }
    }
    if (IsMax)
    {
        int bestMove = -99999;
        boardt rboard;
        for (auto it = res1.begin(); it != res1.end(); it++)
        {
            if (minimax3(depth - 1, *it , !IsMax).first > bestMove)
            {
                rboard = *it;
                bestMove = minimax3(depth - 1, *it , !IsMax).first;
            }
        }
        return std::make_pair(bestMove, rboard);
    }
    else
    {
        int bestMove = 99999;
        boardt rboard;
        for (auto it = res1.begin(); it != res1.end(); it++)
        {
            bestMove = std::min(bestMove, minimax3(depth - 1 , *it, !IsMax).first);
            if (minimax3(depth - 1, *it , !IsMax).first < bestMove)
            {
                rboard = *it;
                bestMove = minimax3(depth - 1, *it , !IsMax).first;
            }
        }
        return std::make_pair(bestMove, rboard);
    }
    
}

int main()
{
    //std::vector<boardt> res = possible_move(board , 5 , 7);
    //for (auto it = res.begin(); it != res.end(); ++it)
    //    board_dump(*it);
    
    boardt board;
    // INIT BOARD
    for(size_t i = 0; i < 8; i++)
    {
        board[1][i] = "bpawn";
        board[6][i] = "wpawn";
    }
    board[0][0] = "btower";
    board[0][7] = "btower";
    board[7][0] = "wtower";
    board[7][7] = "wtower";
    board[0][1] = "bhorse";
    board[0][6] = "bhorse";
    board[7][1] = "whorse";
    board[7][6] = "whorse";
    board[0][2] = "bbishop";
    board[0][5] = "bbishop";
    board[7][2] = "wbishop";
    board[7][5] = "wbishop";
    board[0][3] = "bqueen";
    board[7][3] = "wqueen";
    board[0][4] = "bking";
    board[7][4] = "wking";
    for(size_t i = 2; i < 6; i++)
        for(size_t j = 0; j < 8; j++)
            board[i][j] = "";

    /*Mtree root('w' , board , 0);
    filltree(board , 'w', root , 5);
    std::cout << "NBCHILDREN :"<< root.nbchildren_ << "\n";
    std::cout <<  "GRANDCHILDREN :" <<  root.children_[0].children_[0].children_[0].nbchildren_ << '\n';
    board_dump(root.children_[0].children_[0].children_[0].children_[0].board_);*/

    // board[1][1] = "wqueen";
    // board[7][3] = "";
    // board[4][2] = "wpawn";
    // board[6][2] = "";
    // board[3][2] = "bpawn";
    // board[1][2] = "";
    // board[2][3] = "bpawn";
    // board[1][3] = "";
    // board[5][5] = "btower";
    // board[0][0] = "";
    // board[6][2] = "bking";
    // board[0][4] = "";

    // board[4][0] = "wpawn";
    // board[6][0] = "";
    // board[4][2] = "wpawn";
    // board[6][2] = "";
    // board[5][4] = "wpawn";
    // board[6][4] = "";
    // board[0][0] = "";
    // board[0][1] = "btower";
    // board[2][2] = "bhorse";


    board_dump(board);

    // std::vector<boardt> rboard = possible_move(board , 7 , 5);
    // for (auto it = rboard.begin(); it != rboard.end(); it++)
    //    board_dump(*it);
    // return total_score(board);
    for (int i = 2; i < 1000; i++)
    {
        //char player = i%2 == 0 ? 'w' : 'b';
        bool player = i%2 == 0? true : false;
        std::pair<int , boardt> res = minimax2(board , player, 2, -1000000, 1000000);
        //std::pair<int , boardt> res = minimax3(3 , board , player);
        board = res.second;
        board_dump(board);
        std::cout << "ACTUAL Value " << total_score(board) << '\n';
        std::cout << "Predicted VALUE : " << res.first << "\n\n";
    }

    // auto res = king_move(board , 6 , 2);
    // for (auto it = res.begin(); it != res.end(); it++)
    // {
    //     board_dump(*it);
    //     std::cout << "KING : x = " << find_king(*it , "bking").first  << " y = " << find_king(*it , "bking").second << '\n';
    // }
}