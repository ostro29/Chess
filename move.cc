#include "move.hh"

bool iv(int x, int y)
{
    return x < 8 && x >= 0 && y < 8 && y >= 0;
}

void board_dump(boardt board)
{
    std::cout << "--------------------------------\n";
    for(size_t i = 0; i < 8; i++)
    {
        std::cout << '|';
        for(size_t j = 0; j < 8; j++)
        {
            if (board[i][j] == "wpawn")
                std::cout << "\033[1;31m P \033[0m|";
            if (board[i][j] == "wbishop")
                std::cout << "\033[1;31m B \033[0m|";
            if (board[i][j] == "whorse")
                std::cout << "\033[1;31m H \033[0m|";
            if (board[i][j] == "wtower")
                std::cout << "\033[1;31m T \033[0m|";
            if (board[i][j] == "wqueen")
                std::cout << "\033[1;31m Q \033[0m|";
            if (board[i][j] == "wking")
                std::cout << "\033[1;31m K \033[0m|";


            if (board[i][j] == "bpawn")
                std::cout << "\033[1;34m P \033[0m|";
            if (board[i][j] == "bbishop")
                std::cout << "\033[1;34m B \033[0m|";
            if (board[i][j] == "bhorse")
                std::cout << "\033[1;34m H \033[0m|";
            if (board[i][j] == "btower")
                std::cout << "\033[1;34m T \033[0m|";
            if (board[i][j] == "bqueen")
                std::cout << "\033[1;34m Q \033[0m|";
            if (board[i][j] == "bking")
                std::cout << "\033[1;34m K \033[0m|";
            
            if (board[i][j] == "")
                std::cout << "   |";
            
        }
        std::cout << '\n';
        std::cout << "--------------------------------\n";
    }
    std::cout << "\n";
    
}

std::vector<boardt> wpawn_move(boardt board, int x, int y)
{
    std::vector<boardt> res;
    // 1 move up
    if (iv(x - 1, y) && board[x - 1][y] == "")
    {
        boardt rboard;
        rboard = board;
        if (x - 1 == 0)
            rboard[x - 1][y] = "wqueen";
        else
            rboard[x - 1][y] = "wpawn";
        rboard[x][y] = "";
        res.push_back(rboard);
    }
    // 2 move up
    if (iv(x - 2, y) && x == 6 && board[x - 1][y] == "" && board[x - 2][y] == "")
    {
        boardt rboard;
        rboard = board;
        rboard[x - 2][y] = "wpawn";
        rboard[x][y] = "";
        res.push_back(rboard);
    }
    // Eat enemy pawn
    if (iv(x - 1, y + 1) && board[x - 1][y + 1][0] == 'b')
    {
        boardt rboard;
        rboard = board;
        if (x - 1 == 0)
            rboard[x - 1][y + 1] = "wqueen";
        else
            rboard[x - 1][y + 1] = "wpawn";
        rboard[x][y] = "";
        res.push_back(rboard);
    }
    if (iv(x - 1, y - 1) && board[x - 1][y - 1][0] == 'b')
    {
        boardt rboard;
        rboard = board;
        if (x - 1 == 0)
            rboard[x - 1][y - 1] = "wqueen";
        else
            rboard[x - 1][y - 1] = "wpawn";
        rboard[x][y] = "";
        res.push_back(rboard);
    }
    return res;
}

std::vector<boardt> bpawn_move(boardt board, int x, int y)
{
    std::vector<boardt> res;
    // 1 move up
    if (iv(x + 1, y) && board[x + 1][y] == "")
    {
        boardt rboard;
        rboard = board;
        if (x + 1 == 7)
            rboard[x + 1][y] = "bqueen";
        else
            rboard[x + 1][y] = "bpawn";
        rboard[x][y] = "";
        res.push_back(rboard);
    }
    // 2 move up
    if (iv(x + 2, y) && x == 1 && board[x + 1][y] == "" && board[x + 2][y] == "")
    {
        boardt rboard;
        rboard = board;
        rboard[x + 2][y] = "bpawn";
        rboard[x][y] = "";
        res.push_back(rboard);
    }
    // Eat enemy pawn
    if (iv(x + 1, y + 1) && board[x + 1][y + 1][0] == 'w')
    {
        boardt rboard;
        rboard = board;
        if (x + 1 == 7)
            rboard[x + 1][y + 1] = "bqueen";
        else
            rboard[x + 1][y + 1] = "bpawn";
        rboard[x][y] = "";
        res.push_back(rboard);
    }
    if (iv(x + 1, y - 1) && board[x + 1][y - 1][0] == 'w')
    {
        boardt rboard;
        rboard = board;
        if (x + 1 == 7)
            rboard[x + 1][y - 1] = "bqueen";
        else
            rboard[x + 1][y - 1] = "bpawn";
        rboard[x][y] = "";
        res.push_back(rboard);
    }
    return res;
}


std::vector<boardt> tower_move2(boardt board , int x , int y)
{
    bool left = true;
    bool right = true;
    bool up = true;
    bool down = true;
    std::vector<boardt> res;
    for (int i = 1; i < 8; i++)
    {
        if (right && y + i < 8)
        {
            if (board[x][y + i][0] == board[x][y][0])
                right = false;
            else
            {
                boardt rboard = board;
                rboard[x][y + i] = board[x][y];
                rboard[x][y] = "";
                res.push_back(rboard);
                if (board[x][y + i] != "")
                    right = false;
            }          
        }
        if (left && y - i >= 0)
        {
            if (board[x][y - i][0] == board[x][y][0])
                left = false;
            else 
            {
                boardt rboard = board;
                rboard[x][y - i] = board[x][y];
                rboard[x][y] = "";
                res.push_back(rboard);
                if (board[x][y - i] != "")
                    left = false;
            }
        }
        if (down && x + i < 8)
        {
            if (board[x + i][y][0] == board[x][y][0])
                down = false;
            else
            {
                boardt rboard = board;
                rboard[x + i][y] = board[x][y];
                rboard[x][y] = "";
                res.push_back(rboard);
                if (board[x + i][y] != "")
                down = false;
            }
        }
        if (up && x - i >= 0)
        {
            if (board[x - i][y][0] == board[x][y][0])
                up = false;
            else
            {
                boardt rboard = board;
                rboard[x - i][y] = board[x][y];
                rboard[x][y] = "";
                res.push_back(rboard);
                if (board[x - i][y] != "")
                    up = false;
            }
        }
    }
    return res;
}

std::vector<boardt> bishop_move(boardt board , int x , int y)
{
    bool ld = true;
    bool lu = true;
    bool ru = true;
    bool rd = true;
    std::vector<boardt> res;
    for (int i = 1; i < 8; i++)
    {
        if (rd && iv(x + i, y + i))
        {
            if (board[x + i][y + i][0] == board[x][y][0])
                rd = false;
            else
            {
                boardt rboard = board;
                rboard[x + i][y + i] = board[x][y];
                rboard[x][y] = "";
                res.push_back(rboard);
                if (board[x + i][y + i] != "")
                    rd = false;
            }
        }
        if (ld && iv(x + i, y - i))
        {
            if (board[x + i][y - i][0] == board[x][y][0])
                ld = false;
            else
            {
                boardt rboard = board;
                rboard[x + i][y - i] = board[x][y];
                rboard[x][y] = "";
                res.push_back(rboard);
                if (board[x + i][y - i] != "")
                    ld = false;
            }
        }
        if (ru && iv(x - i, y + i))
        {
            if (board[x - i][y + i][0] == board[x][y][0])
                ru = false;
            else
            {
                boardt rboard = board;
                rboard[x - i][y + i] = board[x][y];
                rboard[x][y] = "";
                res.push_back(rboard);
                if (board[x - i][y + i] != "")
                    ru = false;
            }
        }
        if (lu && iv(x - i, y - i))
        {
            if (board[x - i][y - i][0] == board[x][y][0])
                lu = false;
            else
            {
                boardt rboard = board;
                rboard[x - i][y - i] = board[x][y];
                rboard[x][y] = "";
                res.push_back(rboard);
                if (board[x - i][y - i] != "" && board[x - i][y - i] != board[x][y])
                    lu = false;
            }
        }
    }
    return res;
}

std::vector<boardt> horse_move(boardt board , int x , int y)
{
    std::vector<boardt> res;
    for(int i = -2; i < 3; i++)
    {
        if (i == 0)
            continue;
        int y1 = 3 - abs(i);
        int y2 = -3 + abs(i);
        boardt rboard;
        if (iv(x + i , y + y1) && board[x + i][y + y1][0] != board[x][y][0])
        {
            rboard = board;
            rboard[x + i][y + y1] = board[x][y];
            rboard[x][y] = "";
            res.push_back(rboard);
        }
        if (iv(x + i , y + y2) && board[x + i][y + y2][0] != board[x][y][0])
        {
            rboard = board;
            rboard[x + i][y + y2] = board[x][y];
            rboard[x][y] = "";
            res.push_back(rboard);
        }
    }
    return res;
}

std::vector<boardt> king_move(boardt board , int x , int y)
{
    std::vector<boardt> res;
    for (int i = -1; i < 2; i += 2)
    {
        boardt rboard;
        if (iv(x + i , y) && board[x + i][y][0] != board[x][y][0])
        {
            rboard = board;
            rboard[x + i][y] = board[x][y];
            rboard[x][y] = "";
            res.push_back(rboard);
        }
        if (iv(x , y + i) && board[x][y + i][0] != board[x][y][0])
        {
            rboard = board;
            rboard[x][y + i] = board[x][y];
            rboard[x][y] = "";
            res.push_back(rboard);
        }
        if (iv(x + i, y + i) && board[x + i][y + i][0] != board[x][y][0])
        {
            rboard = board;
            rboard[x + i][y + i] = board[x][y];
            rboard[x][y] = "";
            res.push_back(rboard);
        }
        if (iv(x - i, y + i) && board[x - i][y + i][0] != board[x][y][0])
        {
            rboard = board;
            rboard[x - i][y + i] = board[x][y];
            rboard[x][y] = "";
            res.push_back(rboard);
        }
    }
    return res;
}

bool check_check(boardt board , int x , int y)
{
    char color = board[x][y][0] == 'w' ? 'b' : 'w';

    std::string horse = "horse";
    horse = color + horse;
    std::string tower = "tower";
    tower = color + tower;
    std::string bishop = "bishop";
    bishop = color + bishop;
    std::string queen = "queen";
    queen = color + queen;
    std::string pawn = "pawn";
    pawn = color + pawn;
    // Check Pawn
    if (pawn == "bpawn")
        if ((iv(x - 1 , y + 1) && board[x - 1][y + 1] == pawn) || (iv(x - 1, y - 1) && board[x - 1][y - 1] == pawn))
            return true;
    if (pawn == "wpawn")
        if ((iv(x + 1, y + 1) && board[x + 1][y + 1] == pawn) || (iv(x + 1, y - 1) && board[x + 1][y - 1] == pawn))
            return true;

    //check horse
    for(int i = -2; i < 3; i++)
    {
        if (i == 0)
            continue;
        int y1 = 3 - abs(i);
        int y2 = -3 + abs(i);
        boardt rboard;
        if (iv(x + i , y + y1) && board[x + i][y + y1] == horse)
            return true;
        if (iv(x + i , y + y2) && board[x + i][y + y2] == horse)
            return true;
    }
    bool left = true;
    bool right = true;
    bool down = true;
    bool up = true;
    bool lu = true;
    bool ld = true;
    bool ru = true;
    bool rd = true;
    // Check Bishop Tower and Queen
    for (int i = 1; i < 8; i++)
    {
        //down
        if (x + i < 8 && down && (board[x + i][y] == tower || board[x + i][y] == queen))
            return true;
        else if (x + i < 8 && board[x + i][y] != "")
            down = false;
        //up
        if (x - i >= 0 && up && (board[x - i][y] == tower || board[x - i][y] == queen))
            return true;
        else if (x - i >= 0 && board[x - i][y] != "")
            up = false;
        //left
        if (y -i >= 0 && left && (board[x][y - i] == tower || board[x][y - i] == queen))
            return true;
        else if (y -i >= 0 && board[x][y - i] != "")
            left = false;
        //right
        if (y  + i < 8 && right && (board[x][y + i] == tower || board[x][y + i] == queen))
            return true;
        else if (y + i  < 8 && board[x][y + i] != "")
            right = false;

        // right down
        if (!iv(x + i, y + i))
            rd = false;
        else if (rd && (board[x + i][y + i] == bishop || board[x + i][y + i] == queen))
            return true;
        else if (board[x + i][y + i] != "")
            rd = false;

        // right up
        if (!iv(x - i, y + i))
            ru = false;
        else if (ru && (board[x - i][y + i] == bishop || board[x - i][y + i] == queen))
            return true;
        else if (board[x - i][y + i] != "")
            ru = false;

        // left down
        if (!iv(x + i, y - i))
            ld = false;
        else if (ld && (board[x + i][y - i] == bishop || board[x + i][y - i] == queen))
            return true;
        else if (board[x + i][y - i] != "")
            ld = false;

        // left up
        if (!iv(x - i, y - i))
            lu = false;
        else if (lu && (board[x - i][y - i] == bishop || board[x - i][y - i] == queen))
            return true;
        else if (board[x - i][y - i] != "")
            lu = false;
    }
    return false;
}

std::pair<int , int> find_king(boardt board , std::string king)
{
    std::vector<boardt> res1; 
    for(size_t i = 0; i < 8; i++)
        for(size_t j = 0; j < 8; j++)
            if (board[i][j] == king)
                return std::make_pair(i , j);
}

bool check_mate(boardt board , int x , int y)
{
    if (!check_check(board , x , y))
        return false;

    std::vector<boardt> res1; 
    for(size_t i = 0; i < 8; i++)
    {
        for(size_t j = 0; j < 8; j++)
        {
            if (board[i][j] != "" && board[i][j][0] == board[x][y][0])
            {
                std::vector<boardt> res2 = possible_move(board , i , j);
                res1.insert(res1.end() , res2.begin(), res2.end());
            }
        }
    }

    for (auto it = res1.begin() ; it != res1.end(); it++)
    {
        std::pair<int , int> pos = find_king(*it, board[x][y]);
        if (!check_check(*it , pos.first, pos.second))
            return false;
    }
    return true;
}

std::vector<boardt> possible_move(boardt board, int x, int y)
{
    std::vector<boardt> res;
    if (board[x][y] == "wpawn")
        res = wpawn_move(board , x , y);
    else if (board[x][y] == "bpawn")
        res = bpawn_move(board , x , y);
    else if (board[x][y] == "wtower" || board[x][y] == "btower")
        res = tower_move2(board , x , y);
    else if (board[x][y] == "wbishop" || board[x][y] == "bbishop")
        res = bishop_move(board, x , y);
    else if (board[x][y] == "whorse" || board[x][y] == "bhorse")
        res = horse_move(board, x , y);
    else if (board[x][y] == "wqueen" || board[x][y] == "bqueen")
    {
        std::vector<boardt> res1 = bishop_move(board, x , y);
        std::vector<boardt> res2 = tower_move2(board , x , y);
        res1.insert(res1.end() , res2.begin(), res2.end());
        res = res1;
    }
    else if (board[x][y] == "wking" || board[x][y] == "bking")
        res = king_move(board , x , y);

    auto it = res.begin();

    while (it != res.end())
    {
        std::string king = board[x][y][0] == 'w' ? "wking" : "bking";
        std::pair<int , int> pos = find_king(*it , king);
        if (check_check(*it , pos.first, pos.second))
            res.erase(it);
        else
            ++it;
    }
    return res;
}