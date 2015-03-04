//Copyright (C) 2014-2015  Corwin Hansen
#ifndef MAIN_H//include protection
	#define MAIN_H
#include <string.h> //for simpler data handling
#include <stdlib.h>//standard utility
#include <stdio.h> //input output
#include <math.h> //math

#define BOARD_SIZE 19 //board size
#define BLACK_PIECE "x " //black piece
#define WHITE_PIECE "o " //white piece
#define BLANK_POINT ". " //blank spot
#define STAR_POINT "+ "//special spots
#define BLACK 1 //black in array
#define WHITE 2 //white in array
#define BLANK 0 //blank in array
#define STAR 3 //star point in aray


unsigned char board[BOARD_SIZE][BOARD_SIZE];//go board. blank is 0, black is 1, white is 2. board[y][x].

void printboard(void);//print out bord following the macros with space between each

void init(void);//initialise variables

void place(unsigned char x, unsigned char y, unsigned char piece);//place a piece on board


#endif