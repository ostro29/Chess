#include "minimax.hh"
#include "move.hh"

int score(std::string piece, int x, int y)
{
    std::array<std::array<float, 8>, 8> WPE{{{0, 0, 0, 0, 0, 0, 0, 0},
                                           {5, 5, 5, 5, 5, 5, 5, 5},
                                           {1, 1, 2, 3, 3, 2, 1, 1},
                                           {0.5, 0.5, 1, 2.5, 2.5, 1, 0.5, 0.5},
                                           {0, 0, 0, 2, 2, 0, 0, 0},
                                           {0.5, -0.5, -1, 0, 0, -1, -0.5, 0.5},
                                           {0.5, 1, 1, -2, -2, 1, 1, 0.5},
                                           {0, 0, 0, 0, 0, 0, 0, 0}}};

    std::array<std::array<float, 8>, 8> WHE{{{-5, -4, -3, -3, -3, -3, -4, -5},
                                           {-4, -2, 0, 0, 0, 0, -2, -4},
                                           {-3, 0, 1, 1.5, 1.5, 1, 0, -3},
                                           {-3, 0.5, 1.5, 2, 2, 1.5, 0.5, -3},
                                           {-3, 0, 1.5, 2, 2, 1.5, 0, -3},
                                           {-3, 0.5, 1, 1.5, 1.5, 1, 0.5, -3},
                                           {-4, -2, 0, 0.5, 0.5, 0, -2, -4},
                                           {-5, -4, -3, -3, -3, -3, -4, -5}}};

    std::array<std::array<float, 8>, 8> WBE{{{-2, -1, -1, -1, -1, -1, -1, -2},
                                           {-1, 0, 0, 0, 0, 0, 0, -1},
                                           {-1, 0, 0.5, 1, 1, 0.5, 0, -1},
                                           {-1, 0.5, 0.5, 1, 1, 0.5, 0.5, -1},
                                           {-1, 0, 1, 1, 1, 1, 0, -1},
                                           {-1, 1, 1, 1, 1, 1, 1, -1},
                                           {-1, 0.5, 0, 0, 0, 0, 0.5, -1},
                                           {-2, -1, -1, -1, -1, -1, -1, -2}}};

    std::array<std::array<float, 8>, 8> WTE{{{0, 0, 0, 0, 0, 0, 0, 0},
                                           {0.5, 1, 1, 1, 1, 1, 1, 0.5},
                                           {-0.5, 0, 0, 0, 0, 0, 0, -0.5},
                                           {-0.5, 0, 0, 0, 0, 0, 0, -0.5},
                                           {-0.5, 0, 0, 0, 0, 0, 0, -0.5},
                                           {-0.5, 0, 0, 0, 0, 0, 0, -0.5},
                                           {-0.5, 0, 0, 0, 0, 0, 0, -0.5},
                                           {0, 0, 0, 0.5, 0.5, 0, 0, 0}}};

    std::array<std::array<float, 8>, 8> WQE{{{-2, -1, -1, -0.5, -0.5, -1, -1, -2},
                                           {-1, 0, 0, 0, 0, 0, 0, -1},
                                           {-1, 0, 0.5, 0.5, 0.5, 0.5, 0, -1},
                                           {-0.5, 0, 0.5, 0.5, 0.5, 0.5, 0, -0.5},
                                           {0, 0, 0.5, 0.5, 0.5, 0.5, 0, -0.5},
                                           {-1, 0.5, 0.5, 0.5, 0.5, 0.5, 0, -1},
                                           {-1, 0, 0.5, 0, 0, 0, 0, -1},
                                           {-2, -1, -1, -0.5, -0.5, -1, -1, -2}}};

    std::array<std::array<float, 8>, 8> WKE{{{-3, -4, -4, -5, -5, -4, -4, -3},
                                           {-3, -4, -4, -5, -5, -4, -4, -3},
                                           {-3, -4, -4, -5, -5, -4, -4, -3},
                                           {-3, -4, -4, -5, -5, -4, -4, -3},
                                           {-2, -3, -3, -4, -4, -3, -3, -2},
                                           {-1, -2, -2, -2, -2, -2, -2, -1},
                                           {2, 2, 0, 0, 0, 0, 2, 2},
                                           {2, 3, 1, 0, 0, 1, 3, 2}}};

    std::array<std::array<float, 8>, 8> BPE = WPE;
    std::reverse(BPE.begin() , BPE.end());

    std::array<std::array<float, 8>, 8> BTE = WTE;
    std::reverse(BTE.begin() , BTE.end());

    std::array<std::array<float, 8>, 8> BBE = WBE;
    std::reverse(BBE.begin() , BBE.end());

    std::array<std::array<float, 8>, 8> BHE = WHE;
    std::reverse(BHE.begin() , BHE.end());
    
    std::array<std::array<float, 8>, 8> BQE = WQE;
    std::reverse(BQE.begin() , BQE.end());

    std::array<std::array<float, 8>, 8> BKE = WKE;
    std::reverse(BKE.begin() , BKE.end());

    if (piece[0] == 'w')
    {
        if (piece == "wpawn")
            return 10 + WPE[x][y];
        if (piece == "wbishop")
            return 30 + WBE[x][y];
        if (piece == "whorse")
            return 30 + WHE[x][y];
        if (piece == "wtower")
            return 50 + WTE[x][y];
        if (piece == "wqueen")
            return 100 + WQE[x][y];
        if (piece == "wking")
            return 100 + WKE[x][y];
    }
    if (piece[0] == 'b')
    {
        if (piece == "bpawn")
            return -10 - BPE[x][y];
        if (piece == "bbishop")
            return -30 - BBE[x][y];
        if (piece == "bhorse")
            return -30 - BHE[x][y];
        if (piece == "btower")
            return -50 - BTE[x][y];
        if (piece == "bqueen")
            return -100 - BQE[x][y];
        if (piece == "bking")
            return - 100 - BKE[x][y];
    }
    return 0;
}

int total_score(boardt board)
{
    int sum = 0;
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            sum += score(board[i][j], i, j);
    std::pair<int, int> wking = find_king(board, "wking");
    std::pair<int, int> bking = find_king(board, "bking");
    if (check_mate(board, wking.first, wking.second))
        sum += 10000;
    if (check_mate(board, bking.first, bking.second))
        sum -= 10000;
    return sum;
}

Mtree filltree(boardt board, char player, Mtree &tree, int depth)
{
    if (depth == 0)
        return tree;
    std::cout << "DEPTH " << depth << '\n';
    std::vector<boardt> res1;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (board[i][j] != "" && board[i][j][0] == player)
            {
                std::vector<boardt> res2 = possible_move(board, i, j);
                res1.insert(res1.end(), res2.begin(), res2.end());
            }
        }
    }
    for (auto it = res1.begin(); it != res1.end(); it++, tree.nbchildren_++)
    {
        int score = total_score(*it);
        tree.children_.push_back(Mtree(!player, *it, score));
    }
    char nextplayer = player == 'w' ? 'b' : 'w';
    for (int i = 0; i < tree.nbchildren_; i++)
    {
        filltree(tree.children_[i].board_, nextplayer, tree.children_[i], depth - 1);
    }
    return tree;
}

std::pair<int, boardt> minimax2(boardt board, bool player, int depth, int alpha, int beta)
{
    std::pair<int, int> bking = find_king(board, "bking");
    std::pair<int, int> wking = find_king(board, "wking");
    if (depth == 0 || check_mate(board, bking.first, bking.second) || check_mate(board, wking.first, wking.second))
    {
        return std::make_pair(total_score(board), board);
    }
    std::vector<boardt> res1;
    char p = player ? 'w' : 'b';
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (board[i][j] != "" && board[i][j][0] == p)
            {
                std::vector<boardt> res2 = possible_move(board, i, j);
                res1.insert(res1.end(), res2.begin(), res2.end());
            }
        }
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(res1.begin(), res1.end(), std::default_random_engine(seed));
    boardt bestmove;
    int bestmovevalue = player ? -100000 : 100000;

    for (auto it = res1.begin(); it != res1.end(); it++)
    {
        int value = minimax2(*it, !player, depth - 1, alpha, beta).first;

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
            beta = std::min(beta, value);
        }
        if (beta <= alpha)
            break;
    }
    return std::make_pair(bestmovevalue, bestmove);
}

int main()
{

    boardt board;
    // INIT BOARD
    for (size_t i = 0; i < 8; i++)
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
    for (size_t i = 2; i < 6; i++)
        for (size_t j = 0; j < 8; j++)
            board[i][j] = "";

    board_dump(board);
    for (int i = 2; i < 1000; i++)
    {
        bool player = i % 2 == 0 ? true : false;
        std::pair<int, boardt> res = minimax2(board, player, 3, -1000000, 1000000);
        board = res.second;
        board_dump(board);
        std::cout << "ACTUAL Value " << total_score(board) << '\n';
        std::cout << "Predicted VALUE : " << res.first << "\n\n";
    }
}