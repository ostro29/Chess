#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <algorithm> 
#include <cstdlib>
#include <random>
#include <chrono>
#include "move.hh"

typedef std::array<std::array<std::string , 8>, 8> boardt;

class Mtree
{

public:
    Mtree(char player, boardt board, int value)
    {
        player_ = player;
        value_ = value;
        alpha_ = -1000;
        beta_ = 1000;
        nbchildren_ = 0;
        board_ = board;
    }
    ~Mtree() = default;

    std::vector<Mtree> getchildren()
    {
        return children_;
    }

    boardt board_;
    char player_;
    int value_;
    int alpha_;
    int beta_;
    std::vector<Mtree> children_;
    int nbchildren_;
};