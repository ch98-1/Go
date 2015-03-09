//Copyright (C) 2014-2015  Corwin Hansen
#ifndef MAIN_H//include protection
	#define MAIN_H
#include <string.h> //for simpler data handling
#include <stdlib.h>//standard utility
#include <stdio.h> //input output
#include <math.h> //math
#include <time.h> //randomseed

#define BOARD_SIZE 19 //board size
#define BLACK_PIECE "X " //black piece
#define WHITE_PIECE "O " //white piece
#define BLANK_POINT "+ " //blank spot
#define STAR_POINT "* "//special spots
#define BLACK 1 //black in array
#define WHITE 2 //white in array
#define BLANK 0 //blank in array
#define STAR 3 //star point in aray
#define LOG "log.txt" //log file for all games
#define HELP "Commands:\n help, -h, h, -help, or blank to display this message \n load to load file. input filename when prompted \n save to save file. input filename when prompted \n place <x> <y> to place piece on that position \n new to get new game \n turn to print out turn \n print to print out bord \n pass to pass \n quit to quit \n"
#define MOVEBORDS memcpy(ko, last, BOARD_SIZE*BOARD_SIZE); \
	memcpy(last, board, BOARD_SIZE*BOARD_SIZE); //move bords

unsigned char board[BOARD_SIZE][BOARD_SIZE];//go board. blank is 0, black is 1, white is 2. star points is 3. board[y][x].
unsigned char ko[BOARD_SIZE][BOARD_SIZE];//2 copy's before for checking ko rule.
unsigned char last[BOARD_SIZE][BOARD_SIZE];//last copy of bord.
unsigned char simulation[BOARD_SIZE][BOARD_SIZE];//copy of go board for simulations and scoring.
unsigned char libertysimulation[BOARD_SIZE][BOARD_SIZE];//copy of go board for simulations on liberty counting

unsigned char turn;//if it is black or white turn

unsigned int black_captured;//number of black captured
unsigned int white_captured;//number of white captured

unsigned int black_pass;//if black passed
unsigned int white_pass;//if white passed

unsigned int black_area_score;//area / chinese scoring for black
unsigned int white_area_score;//area / chinese scoring for white
unsigned int black_territory_score;//territory / japanese scoring for black
unsigned int white_territory_score;//territory / japanese scoring for white

unsigned char mode;//game mode. 1 for computer vs human 2 for human vs human black is human. number of human players

unsigned char liberties;//number of liberties


FILE* logfile;//logfile


void printboard(void);//print out bord following the macros with space between each

void init(void);//initialise variables

void place(unsigned char x, unsigned char y, unsigned char piece);//place a piece on board

void territoryscore(void);//count score for territory / japanese scoring

void areascore(void);//count score for area / chinese scoring

void save(const char* file);//save board to file

void load(const char* file);//load board from file

void writelog(const char* message);//write message in to log file

int legal(unsigned char x, unsigned char y, unsigned char piece);//check if that move is legal

void play(void);//make computer play

void pass(unsigned char piece);//pass that turn

void checkliberty(unsigned char x, unsigned char y);//check if it has any liberties and remove if it dosen't

void floodfill(unsigned char x, unsigned char y, unsigned char target, unsigned char replacement);//flood fill untill complete.

void countliberties(unsigned char x, unsigned char y, unsigned char piece);//get number of liberties

#endif