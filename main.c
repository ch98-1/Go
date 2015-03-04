//Copyright (C) 2014-2015  Corwin Hansen
#include "main.h"

int main(void){//no arguments to start
	printf("\n");//first character

	init();//initialise variables

	//place pieces for test
	place(1,1,BLACK);//black
	place(2,1,WHITE);//white

	printboard();//print out the board

	exit(EXIT_SUCCESS);//end of program
}

void printboard(void){//print out bord following the macros with space between each
	int i, j;
	printf("  ");//first 2 spaces
	for (i = 0; i < BOARD_SIZE; i++){//printf number for column
		printf("%2d", i + 1);//print number for column
	}
	printf("\n");//newline
	for (i = 0; i < BOARD_SIZE; i++){//each row
		printf("%2d ", i + 1);//print number for row
		for (j = 0; j < BOARD_SIZE; j++){//each position
			switch (board[i][j]){
			case BLACK://black
				printf(BLACK_PIECE);//print black
				break;
			case WHITE://white
				printf(WHITE_PIECE);//print white
				break;
			case STAR://spacial
				printf(STAR_POINT);//print white
				break;
			default://blank
				printf(BLANK_POINT);//blank piece
				break;
			}
		}
		printf("\n");//newline
	}


}



void init(void){//initialise variables
	memset(board, 0, BOARD_SIZE*BOARD_SIZE);//clear board
	//place / mark star points
	//4,4 points
	place(4, 4, STAR);
	place(4, 16, STAR);
	place(16, 4, STAR);
	place(16, 16, STAR);
	//4,10 points
	place(4, 10, STAR);
	place(10, 4, STAR);
	place(10, 16, STAR);
	place(16, 10, STAR);
	//10,10 points
	place(10, 10, STAR);
}


void place(unsigned char x, unsigned char y, unsigned char piece){//place a piece on board
	board[y - 1][x - 1] = piece;//set piece
}