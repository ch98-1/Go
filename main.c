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
			load(input);//load input
			printboard();//print bord
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
			MOVEBORDS//move the bords
			if (mode == 1){//if computer mode
				writelog("Computer's turn\n");//log that computer is playing
				play();//make computer play white
			}
		}


		else if (strcmp(strtok(input, " "), "place") == 0){//if placing a piece
			char *xstr = strtok(NULL, " ");//get x
			char *ystr = strtok(NULL, " ");//get y
			if (xstr != NULL && ystr != NULL){//if both are valid input
				int x = atoi(xstr);//get x and y position
				int y = atoi(ystr);
				if (x <= BOARD_SIZE && y <= BOARD_SIZE){
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
						MOVEBORDS//move the bords
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
			else{//if bad input
				printf("Invalid input\n");//invalid input
				writelog("Invalid input\n");//write to log
			}
		}



		if (white_pass == 1 && black_pass == 1){//if end of game
			printf("end of game. Calculsting score...\n");//tell that game ended
			writelog("end of game. Calculsting score...\n");//write to log


			memcpy(simulation, board, BOARD_SIZE*BOARD_SIZE);//copy
			territoryscore();//score for territory
			memcpy(simulation, board, BOARD_SIZE*BOARD_SIZE);//copy
			areascore();//score for area

			sprintf(input, "Area score:\n Black: %u   White: %u \n Territory score:\n Black: %u   White: %u\n", black_area_score, white_area_score, black_territory_score, white_territory_score);//make score string
			printf("%s", input);//print score
			writelog(input);//log score
			
			printf("do you want to save? (y/n): ");//prompt if you want to save or not
			writelog("do you want to save? (y/n): ");//log prompt
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
				putlog(BLACK_PIECE);//log black
				break;
			case WHITE://white
				printf(WHITE_PIECE);//print white
				putlog(WHITE_PIECE);//log white
				break;
			case STAR://spacial
				printf(STAR_POINT);//print star
				putlog(STAR_POINT);//log star
				break;
			default://blank
				printf(BLANK_POINT);//blank point
				putlog(BLANK_POINT);//log blank
				break;
			}
		}
		printf("\n");//newline
		putlog("\n");//put newline in log
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
	memset(last, 0, BOARD_SIZE*BOARD_SIZE);//clear last board
	memset(ko, 0, BOARD_SIZE*BOARD_SIZE);//clear ko board
	black_area_score = 0;//reset score values
	white_area_score = 0;
	black_territory_score = 0;
	white_territory_score = 0;
	real = 0;//reset real
	black_captured = 0;//reset captured number
	white_captured = 0;
	black_pass = 0;//reset pass
	white_pass = 0;
	strength = STRENGTH;//set strength to default value
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


	if (piece == BLACK || piece == WHITE){//if one of them is stones
		memcpy(simulation, board, BOARD_SIZE*BOARD_SIZE);//copy
		real = 1;//real move

		unsigned char opponent;//opponent on array
		if (piece == BLACK){//if black
			opponent = WHITE;//opponent is white
		}
		else {
			opponent = BLACK;//opponent is black
		}

		if (x - 1 > 0 && simulation[y - 1][x - 2] == opponent){//left
			checkliberty(x - 1, y);//check for liberty
		}
		if (x + 1 < BOARD_SIZE && simulation[y - 1][x] == opponent){//right
			checkliberty(x + 1, y);//check for liberty
		}
		if (y - 1 > 0 && simulation[y - 2][x - 1] == opponent){//up
			checkliberty(x, y - 1);//check for liberty
		}
		if (y + 1 < BOARD_SIZE && simulation[y][x - 1] == opponent){//down
			checkliberty(x, y + 1);//check for liberty
		}

		real = 0;//not real anymore
		memcpy(board, simulation, BOARD_SIZE*BOARD_SIZE);//copy back
	}
}






void territoryscore(void){//count score for territory / japanese scoring
	removedead();//remove all dead pieces

}






void areascore(void){//count score for area / chinese scoring
	removedead();//remove all dead pieces
	int y, x;
	for (y = 1; y <= BOARD_SIZE; y++){//each row
		for (x = 1; x <= BOARD_SIZE; x++){//each position
			memcpy(simulationcopy, simulation, BOARD_SIZE*BOARD_SIZE);//copy
			touching_black = 0;//reset black
			touching_white = 0;//reset white
			touching_blank = 0;//reset blank
			if (simulationcopy[y - 1][x - 1] == BLACK){
				black_area_score++;//add one to black score
			}
			if (simulationcopy[y - 1][x - 1] == WHITE){
				white_area_score++;//add one to white score
			}
			if (simulationcopy[y - 1][x - 1] == BLANK){//if blank
				checktouching(x, y, BLANK);//check which colors that space is touching
				if (touching_black > 0 && touching_white == 0){//if touching black piece only
					black_area_score++;//add one to black score
				}
				if (touching_white > 0 && touching_black == 0){//if touching white piece only
					white_area_score++;//add one to white score
				}
			}
		}
	}
}






void removedead(){//remove all dead piece on board
	memcpy(libertysimulation, simulation, BOARD_SIZE*BOARD_SIZE);//copy
	int y, x;
	for (y = 1; y <= BOARD_SIZE; y++){//each row
		for (x = 1; x <= BOARD_SIZE; x++){//each position
			if (simulation[y - 1][x - 1] == STAR) simulation[y - 1][x - 1] = BLANK;//replace star with blank
			unsigned char piece = libertysimulation[y - 1][x - 1];//get piece
			eyes = 0;//reset eye count
			if (piece == BLACK || piece == WHITE){//if piece was black or white
				counteyes(x, y, piece);//get number of eyes
				if (eyes < 2){//if there is less then 2 eyes
					floodfill(x, y, piece, BLANK);//floodfill to blank
				}
			}
			else{
				floodfill(x, y, piece, BLANK);//floodfill to blank
			}
			if (simulation[y - 1][x - 1] == 4) simulation[y - 1][x - 1] = BLANK;//replace substitute with blank
		}
	}
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
	//save current
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
	//save last
	for (i = 0; i < BOARD_SIZE; i++){//each row
		for (j = 0; j < BOARD_SIZE; j++){//each position
			int piece = fputc(last[i][j], data);//write piece
			if (piece == EOF){
				printf("data could not be written correctly. Check permission of %s\n", file);//give error message
				writelog("data could not be written correctly. Check permission of the file\n");//log error message
				return;//end function
			}
		}
	}
	//save ko bord
	for (i = 0; i < BOARD_SIZE; i++){//each row
		for (j = 0; j < BOARD_SIZE; j++){//each position
			int piece = fputc(ko[i][j], data);//write piece
			if (piece == EOF){
				printf("data could not be written correctly. Check permission of %s\n", file);//give error message
				writelog("data could not be written correctly. Check permission of the file\n");//log error message
				return;//end function
			}
		}
	}

	int filedata;//get EOF

	filedata = fputc(turn, data);//write turn
	if (filedata == EOF){//if at end of file
		printf("data could not be written correctly. Check permission of %s\n", file);//give error message
		writelog("data could not be written correctly. Check permission of the file\n");//log error message
		return;//end function
	}
	filedata = fputc(mode, data);//write mode
	if (filedata == EOF){//if at end of file
		printf("data could not be written correctly. Check permission of %s\n", file);//give error message
		writelog("data could not be written correctly. Check permission of the file\n");//log error message
		return;//end function
	}
	filedata = fputc(black_pass, data);//write black pass
	if (filedata == EOF){//if at end of file
		printf("data could not be written correctly. Check permission of %s\n", file);//give error message
		writelog("data could not be written correctly. Check permission of the file\n");//log error message
		return;//end function
	}
	filedata = fputc(white_pass, data);//write white pass
	if (filedata == EOF){//if at end of file
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
	//load current
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
	//load last
	for (i = 0; i < BOARD_SIZE; i++){//each row
		for (j = 0; j < BOARD_SIZE; j++){//each position
			int piece = fgetc(data);//load piece
			if (piece == EOF){
				printf("End of file reached. Data is not in a correct format.\n");//give error message
				writelog("End of file reached. Data is not in a correct format.\n");//log error message
				return;//end function
			}
			last[i][j] = piece;
		}
	}
	//load ko bord
	for (i = 0; i < BOARD_SIZE; i++){//each row
		for (j = 0; j < BOARD_SIZE; j++){//each position
			int piece = fgetc(data);//load piece
			if (piece == EOF){
				printf("End of file reached. Data is not in a correct format.\n");//give error message
				writelog("End of file reached. Data is not in a correct format.\n");//log error message
				return;//end function
			}
			ko[i][j] = piece;
		}
	}
	int filedata;//data from file
	filedata = fgetc(data);//load turn
	if (filedata == EOF){
		printf("End of file reached. Data is not in a correct format.\n");//give error message
		writelog("End of file reached. Data is not in a correct format.\n");//log error message
		return;//end function
	}
	else turn = filedata;//copy data
	filedata = fgetc(data);//load mode
	if (filedata == EOF){
		printf("End of file reached. Data is not in a correct format.\n");//give error message
		writelog("End of file reached. Data is not in a correct format.\n");//log error message
		return;//end function
	}
	else mode = filedata;//copy data
	filedata = fgetc(data);//load black pass
	if (filedata == EOF){
		printf("End of file reached. Data is not in a correct format.\n");//give error message
		writelog("End of file reached. Data is not in a correct format.\n");//log error message
		return;//end function
	}
	else black_pass = filedata;//copy data
	filedata = fgetc(data);//load white pass
	if (filedata == EOF){
		printf("End of file reached. Data is not in a correct format.\n");//give error message
		writelog("End of file reached. Data is not in a correct format.\n");//log error message
		return;//end function
	}
	else white_pass = filedata;//copy data
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







void putlog(const char* message){//write message in to log file without added newline
	int status = fputs(message, logfile);//write message and get status
	if (status == EOF){//if data wasn't written
		printf("Could not write lo log file %s. Plese check the file permission.\n Message was %s\n", LOG, message);//give error message
		return;//end function
	}
}






int legal(unsigned char x, unsigned char y, unsigned char piece){//check if that move is legal
	memcpy(simulation, board, BOARD_SIZE*BOARD_SIZE);//copy

	unsigned char opponent;//opponent on array
	if (piece == BLACK){//if black
		opponent = WHITE;//opponent is white
	}
	else {
		opponent = BLACK;//opponent is black
	}

	if (simulation[y - 1][x - 1] == piece || simulation[y - 1][x - 1] == opponent){//if that space is already taken
		return 0;//can't place where there is pieces already 
	}

	if (x <= 0 || x > BOARD_SIZE || y <= 0 || y > BOARD_SIZE){
		return 0;//out of bound
	}

	simulation[y - 1][x - 1] = piece;//place that piece


	int skipsuicide = 0;//if skipping suicide check
	if (x - 1 > 0 && simulation[y - 1][x - 2] == opponent){//left
		simulation[y - 1][x - 1] = piece;//place that piece
		checkliberty(x - 1, y);//check for liberty
		if (liberties == 0) {//if there was no liberties
			skipsuicide = 1;//took opponent before suicide
		}
	}
	if (x + 1 <= BOARD_SIZE && simulation[y - 1][x] == opponent){//right
		simulation[y - 1][x - 1] = piece;//place that piece
		checkliberty(x + 1, y);//check for liberty
		if (liberties == 0) {//if there was no liberties
			skipsuicide = 1;//took opponent before suicide
		}
	}
	if (y - 1 > 0 && simulation[y - 2][x - 1] == opponent){//up
		simulation[y - 1][x - 1] = piece;//place that piece
		checkliberty(x, y - 1);//check for liberty
		if (liberties == 0) {//if there was no liberties
			skipsuicide = 1;//took opponent before suicide
		}
	}
	if (y + 1 <= BOARD_SIZE && simulation[y][x - 1] == opponent){//down
		simulation[y - 1][x - 1] = piece;//place that piece
		checkliberty(x, y + 1);//check for liberty
		if (liberties == 0) {//if there was no liberties
			skipsuicide = 1;//took opponent before suicide
		}
	}

	if (skipsuicide == 0){//if not skipping suicide check
		checkliberty(x, y);//check at that place

		if (simulation[y - 1][x - 1] != piece){//if it was suicide
			return 0;//Illegal
		}
	}

	if (memcmp(ko, simulation, BOARD_SIZE*BOARD_SIZE) == 0){//if it was same as last last board
		return 0;//Illegal by ko rule
	}

	
	return 1;//it is legal
}







void pass(unsigned char piece){//pass that turn
	if (piece == BLACK){//if black is passing
		black_pass = 1;//set white as passed
	}
	else {
		white_pass = 1;//set black as passed
	}

}





void checkliberty(unsigned char x, unsigned char y){//check if it has any liberties and remove if it dosen't
	unsigned char piece = simulation[y - 1][x - 1];
	liberties = 0;//reset liberties

	memcpy(libertysimulation, simulation, BOARD_SIZE*BOARD_SIZE);//copy

	countliberties(x, y, piece);//get number of liberties
	
	if (liberties == 0){//if there was no liberty
		floodfill(x, y, piece, BLANK);//floodfill to blank
	}

}





void floodfill(unsigned char x, unsigned char y, unsigned char target, unsigned char replacement){//flood fill untill complete.
	if (target == replacement){//if target is replacement
		return;//go back
	}
	if (simulation[y - 1][x - 1] != target){//if node wasn't target
		return;//go back
	}
	simulation[y - 1][x - 1] = replacement;//replace piece
	if (real == 1){
		if (target = BLACK){//if filling black
			black_captured++;//add one to black captured
		}
		if (target = WHITE){//if filling white
			white_captured++;//add one to black captured
		}
	}
	//check for all star points
	//4,4 points
	if (x == 4 && y == 4){//if at star point
		simulation[y - 1][x - 1] = STAR;//place star there
	}
	if (x == 4 && y == 16){//if at star point
		simulation[y - 1][x - 1] = STAR;//place star there
	}
	if (x == 16 && y == 4){//if at star point
		simulation[y - 1][x - 1] = STAR;//place star there
	}
	if (x == 16 && y == 16){//if at star point
		simulation[y - 1][x - 1] = STAR;//place star there
	}
	//4,10 points
	if (x == 4 && y == 10){//if at star point
		simulation[y - 1][x - 1] = STAR;//place star there
	}
	if (x == 10 && y == 4){//if at star point
		simulation[y - 1][x - 1] = STAR;//place star there
	}
	if (x == 10 && y == 16){//if at star point
		simulation[y - 1][x - 1] = STAR;//place star there
	}
	if (x == 16 && y == 10){//if at star point
		simulation[y - 1][x - 1] = STAR;//place star there
	}
	//10,10 points
	if (x == 10 && y == 10){//if at star point
		simulation[y - 1][x - 1] = STAR;//place star there
	}

	if (x - 1 > 0){//left
		floodfill(x - 1, y, target, replacement);//flood fill that direction
	}
	if (x + 1 <= BOARD_SIZE){//right
		floodfill(x + 1, y, target, replacement);//flood fill that direction
	}
	if (y - 1 > 0){//up
		floodfill(x, y - 1, target, replacement);//floodfill that direction
	}
	if (y + 1 <= BOARD_SIZE){//down
		floodfill(x, y + 1, target, replacement);//floodfill that direction
	}

	return;//go back
}






void countliberties(unsigned char x, unsigned char y, unsigned char piece){//get number of liberties
	if (libertysimulation[y - 1][x - 1] != piece){//if node wasn't target
		if (libertysimulation[y - 1][x - 1] == BLANK){//if it was blank
			liberties++;//add one to liberties
		}
		return;//go back
	}
	libertysimulation[y - 1][x - 1] = 4;//replace piece
	if (x - 1 > 0){//left
		countliberties(x - 1, y, piece);//count liberties that direction
	}
	if (x + 1 <= BOARD_SIZE){//right
		countliberties(x + 1, y, piece);//count liberties that direction
	}
	if (y - 1 > 0){//up
		countliberties(x, y - 1, piece);//count liberties that direction
	}
	if (y + 1 <= BOARD_SIZE){//down
		countliberties(x, y + 1, piece);//count liberties that direction
	}

	return;//go back


}







void counteyes(unsigned char x, unsigned char y, unsigned char piece){//get number of eyes
	if (libertysimulation[y - 1][x - 1] != piece){//if node wasn't target
		if (libertysimulation[y - 1][x - 1] == BLANK || libertysimulation[y - 1][x - 1] == STAR || libertysimulation[y - 1][x - 1] == 4){//if it was blank
			memcpy(simulationcopy, simulation, BOARD_SIZE*BOARD_SIZE);//copy
			touching_black = 0;//reset black
			touching_white = 0;//reset white
			touching_blank = 0;//reset blank
			checktouching(x, y, BLANK);//check which colors that space is touching
			if (!(touching_black && touching_white)){//if only touching one color
				floodfill(x, y, BLANK, 4);//floodfill that eye
				eyes++;//add one to liberties
			}
		}
		return;//go back
	}
	libertysimulation[y - 1][x - 1] = 5;//replace piece
	if (x - 1 > 0){//left
		counteyes(x - 1, y, piece);//count liberties that direction
	}
	if (x + 1 < BOARD_SIZE){//right
		counteyes(x + 1, y, piece);//count liberties that direction
	}
	if (y - 1 > 0){//up
		counteyes(x, y - 1, piece);//count liberties that direction
	}
	if (y + 1 < BOARD_SIZE){//down
		counteyes(x, y + 1, piece);//count liberties that direction
	}

	return;//go back

}






void checktouching(unsigned char x, unsigned char y, unsigned char piece){//check which colors that space is touching
	if(simulationcopy[y - 1][x - 1] == BLACK){//if node was black
		touching_black++;//it is touching black
	}
	if (simulationcopy[y - 1][x - 1] == WHITE){//if node was white
		touching_white++;//it is touching black
	}
	if (simulationcopy[y - 1][x - 1] == BLANK || simulation[y - 1][x - 1] == STAR){//if node was blank
		touching_blank++;//it is touching black
	}

	if (simulationcopy[y - 1][x - 1] != piece){//if node wasn't target
		return;//go back
	} 
	simulationcopy[y - 1][x - 1] = 4;//mark that piece
	if (x - 1 > 0){//left
		checktouching(x - 1, y, piece);//count liberties that direction
	}
	if (x + 1 <= BOARD_SIZE){//right
		checktouching(x + 1, y, piece);//count liberties that direction
	}
	if (y - 1 > 0){//up
		checktouching(x, y - 1, piece);//count liberties that direction
	}
	if (y + 1 <= BOARD_SIZE){//down
		checktouching(x, y + 1, piece);//count liberties that direction
	}

	return;//go back

}






void play(void){//make computer play
	turn = WHITE;//set turn
	//random play
	//make better algorithm
	srand(time(NULL));//seed rng with time
	int x, y;//x and y to play
	int i, j = 0;
	int best = -1024;//set best to low number

	for (i = strength; i > 0; i--){//for strength times
		int simx, simy;//simulation x and y
		j = 0;//reset j
		do{
			j++;//add one to j
			if (j > LIMIT){//if no move was found within limit
				goto exit;//break out
			}
			simx = (rand() % (BOARD_SIZE)) + 1;//get new random move
			simy = (rand() % (BOARD_SIZE)) + 1;
		} while (legal(simx, simy, WHITE) == 0);//while it is not a legal move
		white_area_score = 0;//reset area scores
		black_area_score = 0;
		memcpy(simulation, board, BOARD_SIZE*BOARD_SIZE);//copy
		simulation[simy - 1][simx - 1] = WHITE;//place on simulation
		areascore();
		if (white_area_score - black_area_score >= best){
			best = white_area_score - black_area_score;//new best score
			x = simx;//replace x and y
			y = simy;
		}
	}
	exit://exit
	if (best == -1024){//if best wasn't changed
		pass(WHITE);//better to pass then play
		printf("white passed\n");//print that white passed this turn
		putlog("white passed\n");//write that to log file
	}
	else{//move white
		place(x, y, WHITE);//place that piece
		char move[64];//move in string
		sprintf(move, "White move at %d %d\n", x, y);//make move into string
		printf("%s", move);//print that move
		writelog(move);//log that move
	}
	printboard();//print board
	printf("Black's Turn\n");//display turn
	writelog("Black's Turn\n");//log turn
	MOVEBORDS//move bords
	turn = BLACK;//set back turn
}