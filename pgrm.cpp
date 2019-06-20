#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>

#include "board.h"

#define DEBUG_MODE false

using namespace std;

void error_check(int, char **);	//Error Checking Function


int main(int argc, char *argv[]){
	srand(time(NULL));
	error_check(argc,argv);


	bool is_success = false;
	board game(atoi(argv[1]),atoi(argv[2]),DEBUG_MODE);
	int ncells = game.choices();
	game.randomize(4);
	game.display();

	while(game.checkwin() != true){
		is_success = game.tap(rand() % ncells);
		game.display();
	}
	game.write_history();

	return 0;
}













//ERROR CHECKER FOR ARGUMENTS
void error_check(int argc, char *argv[]){
	if(argc != 3){
		printf("USAGE: %s #rows #cols\n",argv[0]);
		exit(-1);
	}

	int row = atoi(argv[1]);
	int col = atoi(argv[2]);;

	if( row <= 0){
		printf("\tERROR: %d is an invalid parameter\n",row);
		printf("\t       The number of rows must be a positive integer\n");
		exit(-1);
	}

	if( col <= 0){
		printf("\tERROR: %d is an invalid parameter\n",col);
		printf("\t       The number of columns must be a positive integer\n");
		exit(-1);
	}

}














