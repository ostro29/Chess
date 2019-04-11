#pragma once
#include <vector>
#include <array>
#include <iostream>

typedef std::array<std::array<std::string , 8>, 8> boardt;

std::vector<boardt> possible_move(boardt board, int x, int y);

void board_dump(boardt board);

bool check_check(boardt board , int x , int y);

bool check_mate(boardt board , int x , int y);

std::pair<int , int> find_king(boardt board , std::string king);