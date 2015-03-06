//Copyright (C) 2014-2015  Corwin Hansen
#include "main.h"



int main(void){//no arguments to start
	init();//initialise variables and load other things

	char input[128];//message input
	while (1){
		printf(">");//prompt command
		gets(input);//get input
		writelog(input);//write input tolog

		//process input
		if (strcmp(input, "help") == 0 || strcmp(input, "-h") == 0 || strcmp(input, "h") == 0 || strcmp(input, "-help") == 0 || strcmp(input, "") == 0){//if it is one of thise help messages
			printf(HELP);//print help
			writelog(HELP);//log help message
		}


		else  if (strcmp(input, "quit") == 0){//if quitting
			printf("Unsaved data will be eraced. Do you really want to quit? (y/n): ");//prompt if you want to quit or not
			gets(input);//get input
			writelog(input);//log input
			if (strcmp(input, "y") == 0) break;//if input is y, break
		}


		else if (strcmp(input, "save") == 0){//if saving
			printf("Please input the filename: ");//prompt to enter the file
			gets(input);//get input
			writelog(input);//log input
			save(input);//save input
		}


		else if (strcmp(input, "load") == 0){//if loading
			printf("Please input the filename: ");//prompt to enter the file
			gets(input);//get input
			writelog(input);//log input
			load(input);//save input
		}


		else if (strcmp(input, "new") == 0){//if making new game
			printf("Unsaved data will be eraced. Do you really want to make a new game? (y/n): ");//prompt if you want to makem new game or not
			gets(input);//get input
			writelog(input);//log input
			if (strcmp(input, "y") == 0) init();//if input is y, initialise
		}


		else if (strcmp(input, "print") == 0){//if printing bord
			printboard();//print bord
		}


		else if (strcmp(input, "turn") == 0){//if printing bord
			if (turn == BLACK){//display turn
				printf("Black's turn\n");
				writelog("Black's turn\n");//log turn
			}
			else {
				printf("White's turn\n");
				writelog("White's turn\n");//log turn
			}
		}


		else if (strcmp(input, "pass") == 0){//if passing
			pass(turn);
			if (mode == 2){//if 2 player mode
				if (turn == BLACK){//switch turn
					turn = WHITE;
				}
				else {
					turn = BLACK;
				}
			}
			if (mode == 2){//if at mode 2
				if (turn == BLACK){//display turn
					printf("Black's turn\n");
					writelog("Black's turn\n");//log turn
				}
				else {
					printf("White's turn\n");
					writelog("White's turn\n");//log turn
				}
			}
		}


		else if (strcmp(strtok(input, " "), "place") == 0){//if placing a piece
			char *xstr = strtok(NULL, " ");//get x
			char *ystr = strtok(NULL, " ");//get y
			if (xstr != NULL && ystr != NULL){//if both are valid input
				int x = atoi(xstr);//get x and y position
				int y = atoi(ystr);
				if (legal(x, y, turn)){//if it is legal move
					place(x, y, turn);//place piece

					if (turn == BLACK){//if black's turn
						black_pass = 0;//black didn't pass
					}
					else{
						white_pass = 0;//white didn't pass
					}

					if (mode == 2){//if 2 player mode
						if (turn == BLACK){//switch turn
							turn = WHITE;
						}
						else {
							turn = BLACK;
						}
					}

					printboard();//print the bord
					if (mode == 1){//if computer mode
						writelog("Computer's turn\n");//log that computer is playing
						play();//make computer play white
					}
				}
				else{//if it was a illegalmove
					printf("Illegal move\n");//irregal move
					writelog("Illegal move\n");//write to log
				}
			}
			else{//if bad input
				printf("Invalid input\n");//invalid input
				writelog("Invalid input\n");//write to log
			}
		}



		if (white_pass == 1 && black_pass == 1){//if end of game
			printf("end of game. Calculsting score...\n");//tell that game ended
			writelog("end of game. Calculsting score...\n");//write to log

			territoryscore();//score for territory
			areascore();//score for area

			sprintf(input, "Area score:\n Black: %u   White: %u \n Territory score:\n Black: %u   White: %u\n", black_area_score, white_area_score, black_territory_score, white_territory_score);//make score string
			printf("%s", input);//print score
			writelog(input);//log score
			
			printf("do you want to save? (y/n): ");//prompt if you want to save or not
			gets(input);//get input
			writelog(input);//log input
			if (strcmp(input, "y") == 0) {//if input is y
				printf("Please input the filename: ");//prompt to enter the file
				gets(input);//get input
				writelog(input);//log input
				save(input);//save input
			}

			init();//initialse
		}


	} 


	fclose(logfile);//close the log file
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
	if (mode == 2){//if at mode 2
		if (turn == BLACK){//display turn
			printf("Black's turn\n");
			writelog("Black's turn\n");//log turn
		}
		else {
			printf("White's turn\n");
			writelog("White's turn\n");//log turn
		}
	}

}







void init(void){//initialise variables and load other things
	turn = BLACK;//black turn at start
	printf("\n");//newline to make sure it is in next line
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

	//open log file
	logfile = fopen(LOG, "ab");//open for appending file
	if (logfile == NULL){//if it wasn't opened
		printf("log file could not be opened or created. Check prtmission of %s\n", LOG);//send error message
		exit(EXIT_FAILURE);//end of program
	}
	setbuf(logfile, NULL);//unbufferd file

	printf("How many players? (1 for human vs computer, 2 for human vs human): ");
	writelog("How many players? (1 for human vs computer, 2 for human vs human): ");//write prompt to log
	char num[64];//number
	gets(num);//get string for that number
	writelog(num);//write input to log
	mode = atoi(num);//get number from string
	if (mode != 1 && mode != 2){//if not valid input
		mode = 2;//default 2 players
		printf("Invalid input. Using 2 player mode.\n");//give error
		writelog("Invalid input. Using 2 player mode.\n");//log error
	}
	printf("Black's turn\n");//announce turn
	writelog("Black's turn\n");//log turn
}






void place(unsigned char x, unsigned char y, unsigned char piece){//place a piece on board
	board[y - 1][x - 1] = piece;//set piece
	if (piece == BLANK){//if placng blank piece in one of the star points
		//4,4 points
		if (x == 4 && y == 4){//if at star point
			place(4, 4, STAR);
		}
		if (x == 4 && y == 16){//if at star point
			place(4, 16, STAR);
		}
		if (x == 16 && y == 4){//if at star point
			place(16, 4, STAR);
		}
		if (x == 16 && y == 16){//if at star point
			place(16, 16, STAR);
		}
		//4,10 points
		if (x == 4 && y == 10){//if at star point
			place(4, 10, STAR);
		}
		if (x == 10 && y == 4){//if at star point
			place(10, 4, STAR);
		}
		if (x == 10 && y == 16){//if at star point
			place(10, 16, STAR);
		}
		if (x == 16 && y == 10){//if at star point
			place(16, 10, STAR);
		}
		//10,10 points
		if (x == 10 && y == 10){//if at star point
			place(10, 10, STAR);
		}
	}
	//add automatic removal of stones without liberties
}






void territoryscore(void){//count score for territory / japanese scoring
	//need code

}






void areascore(void){//count score for area / chinese scoring
	//need code

}







void save(const char* file){//save board to file
	FILE *data = fopen(file, "wb");//open file for reading
	if (data == NULL){
		printf("could not open or create file. Check prtmission of %s\n", file);//give error message
		writelog("could not open or create file. Check prtmission of file\n");//log error message
		return;//end function
	}
	rewind(data);//set to start
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++){//each row
		for (j = 0; j < BOARD_SIZE; j++){//each position
			int piece = fputc(board[i][j], data);//write piece
			if (piece == EOF){
				printf("data could not be written correctly. Check permission of %s\n", file);//give error message
				writelog("data could not be written correctly. Check permission of the file\n");//log error message
				return;//end function
			}
		}
	}
	int piece = fputc(turn, data);//write turn
	if (piece == EOF){
		printf("data could not be written correctly. Check permission of %s\n", file);//give error message
		writelog("data could not be written correctly. Check permission of the file\n");//log error message
		return;//end function
	}
	piece = fputc(mode, data);//write mode
	if (mode == EOF){
		printf("data could not be written correctly. Check permission of %s\n", file);//give error message
		writelog("data could not be written correctly. Check permission of the file\n");//log error message
		return;//end function
	}
	fclose(data);//close file
}





void load(const char* file){//load board to file
	FILE *data = fopen(file, "rb");//open file for reading
	if (data == NULL){//if it wasn't opend
		printf("could not open file. Check if %s exists", file);//give error message
		writelog("could not open file.Check if file exists");//log error message
		return;//end function
	}
	rewind(data);//set to start
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++){//each row
		for (j = 0; j < BOARD_SIZE; j++){//each position
			int piece = fgetc(data);//load piece
			if (piece == EOF){
				printf("End of file reached. Data is not in a correct format.\n");//give error message
				writelog("End of file reached. Data is not in a correct format.\n");//log error message
				return;//end function
			}
			board[i][j] = piece;
			}
		}
	int turn = fgetc(data);//load turn
	if (turn == EOF){
		printf("End of file reached. Data is not in a correct format.\n");//give error message
		writelog("End of file reached. Data is not in a correct format.\n");//log error message
		return;//end function
	}
	mode = fgetc(data);//load mode
	if (mode == EOF){
		printf("End of file reached. Data is not in a correct format.\n");//give error message
		writelog("End of file reached. Data is not in a correct format.\n");//log error message
		return;//end function
	}
	fclose(data);//close file
}






void writelog(const char* message){//write message in to log file
	int status = fputs(message, logfile);//write message and get status
	if (status == EOF){//if data wasn't written
		printf("Could not write lo log file %s. Plese check the file permission.\n Message was %s\n", LOG, message);//give error message
		return;//end function
	}
	status = fputs("\n", logfile);//write newline
	if (status == EOF){//if data wasn't written
		printf("Could not write lo log file %s. Plese check the file permission.\n Message was %s", LOG, message);//give error message
		return;//end function
	}
}






int legal(unsigned char x, unsigned char y, unsigned char piece){//check if that move is legal
	//just for test write correct code
	return 1;//it is legal
}





void play(void){//make computer play
	//random play
	//make better algorithm
	srand(time(NULL));//seed rng with time
	int x = rand() % (BOARD_SIZE);//get random move
	int y = rand() % (BOARD_SIZE);
	while (legal(x, y, WHITE) == 0){//while it is not a legal move
		int x = rand() % (BOARD_SIZE);//get new random move
		int y = rand() % (BOARD_SIZE);
	}
	place(x, y, WHITE);//place that piece
	char move[64];//move in string
	sprintf(move, "White move at %d %d\n", x, y);//make move into string
	printf("%s", move);//print that move
	writelog(move);//log that move
	printboard();//print board
	printf("Black's Turn\n");//display turn
	writelog("Black's Turn\n");//log turn
}







void pass(unsigned char piece){//pass that turn
	if (piece == BLACK){//if black is passing
		black_pass = 1;//set white as passed
	}
	else {
		white_pass = 1;//set black as passed
	}

}