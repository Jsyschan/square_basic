#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "board.h"

using namespace std;

//Goal is to fill the entire board with Xs; remember----0 INDEXING


bool board::tap(int n){
	//Check if cell is valid
	if(n < 0 || n >= num_cells) return false;

	//printf("\nMove %d, tapping %d\t\n",nmoves+1,n);

	//Find the row and col for the number
	int i=0, j=0, cn=0;
	while( (i*cols)+j != n){
		j++;
		if(j == cols){	i++;	j=0;	}
	}


	//TOP LEFT: i-1, j-1
	if( (i-1) >= 0 && (j-1) >= 0){
		cn = ((i-1)*cols)+(j-1);
		if( cells[cn] == '0')	
			cells[cn] = 'X';
		else if(cells[cn] == 'X')
			cells[cn] = '0';
	}

	//TOP: i-1, j
	if( (i-1) >= 0){
		cn = ((i-1)*cols)+(j);
		if( cells[cn] == '0')	
			cells[cn] = 'X';
		else if(cells[cn] == 'X')
			cells[cn] = '0';
	}



	//TOP RIGHT: i-1; j+1
	if( (i-1) >= 0 && (j+1) < cols){
		cn = ((i-1)*cols)+(j+1);
		if( cells[cn] == '0')	
			cells[cn] = 'X';
		else if(cells[cn] == 'X')
			cells[cn] = '0';
	}




	//RIGHT i, j+1
	if( (j+1) < cols){
		cn = ((i)*cols)+(j+1);
		if( cells[cn] == '0')	
			cells[cn] = 'X';
		else if(cells[cn] == 'X')
			cells[cn] = '0';
	}




	//LOWER RIGHT: i+1, j+1
	if( (i+1) < rows && (j+1) < cols){
		cn = ((i+1)*cols)+(j+1);
		if( cells[cn] == '0')	
			cells[cn] = 'X';
		else if(cells[cn] == 'X')
			cells[cn] = '0';
	}




	//BOTTOM: i+1, j
	if( (i+1) < rows ){
		cn = ((i+1)*cols)+(j);
		if( cells[cn] == '0')	
			cells[cn] = 'X';
		else if(cells[cn] == 'X')
			cells[cn] = '0';
	}




	//LOWER LEFT: i+1, j-1
	if( (i+1) < rows && (j-1) >= 0){
		cn = ((i+1)*cols)+(j-1);
		if( cells[cn] == '0')	
			cells[cn] = 'X';
		else if(cells[cn] == 'X')
			cells[cn] = '0';
	}




	//LEFT : i, j-1
	if(  (j-1) >= 0){
		cn = ((i)*cols)+(j-1);
		if( cells[cn] == '0')	
			cells[cn] = 'X';
		else if(cells[cn] == 'X')
			cells[cn] = '0';
	}




	//SELF
	if( cells[n] == '0')	
		cells[n] = 'X';
	else if(cells[n] == 'X')
		cells[n] = '0';



	if(current->next == NULL){
		current->next = (hnode *) malloc(sizeof(struct hnode));
		current->next->next = NULL;
		current->next->cells = (char *) malloc(sizeof(int)*num_cells);
		for(int i=0; i<num_cells; i++) current->next->cells[i] = cells[i];//Save Cells
		current->next->action = (char *) malloc(sizeof(char)*25);
		sprintf(current->next->action,"Tapping %d\n",n);


	}
	current = current->next;
	nmoves++;

}








bool board::checkwin(){
	for(int i=0; i<num_cells; i++){
		if(cells[i] == '0') return false;
	}
	return true;
}








//This is a bare-bones write history function
void board::write_history(){
	struct hnode *tmp = history;

	int cell;
	FILE *fp;
	fp = fopen("test.txt","w+");

	while(tmp != NULL){

		fprintf(fp,"------------------------------------------------------\n");
		fprintf(fp,tmp->action);
		fprintf(fp,"\n\n");
		for(int i=0; i<rows; i++){		//Current Row
			fprintf(fp,"    ");
			for(int j=0; j<cols; j++){	//Current Col
				cell = (i*cols)+j;
				fprintf(fp,"%c",tmp->cells[cell]);
				if((j+1) == cols) fprintf(fp,"\n");

			}
		}
		fprintf(fp,"\n\n");
		tmp = tmp->next;
	}
	fprintf(fp,"------------------------------------------------------\n");
	fprintf(fp,"\nEND OF GAME. TOTAL ACTIONS = %d\n",nmoves);
	fclose(fp);
};




//Constructor
board::board(int R, int C, bool debug_flag){
	rows = R;
	cols = C;
	num_cells = R*C;
	nmoves = 0;
	cells = (char *) malloc(sizeof(char)*num_cells);
	for(int i=0; i<num_cells; i++) cells[i] = 'X';

	if(debug_flag == true) 
		debug = true;
	else 
		debug = false;

	//Start the history chain here
	history = (hnode *) malloc(sizeof(struct hnode));
	history->next = NULL;
	history->cells = (char *) malloc(sizeof(char)*num_cells);
	for(int i=0; i<num_cells; i++) history->cells[i] = 'X';
	history->action = (char *) malloc(sizeof(char)*25);
	sprintf(history->action,"In the beginning...\n");
	current = history;

};

//Destructor
board::~board(){	free(cells);	free(history); };

//Get the number of cells;
int board::choices(){ return num_cells; }


//Print Board Statistics
void board::stats(){
	printf("Num of rows is %d, Num of Cols is %d\n",rows,cols);
}

//Set a certain number of cells to be zero
void board::randomize(int rn){
	//Add error statement here

	//Prepare Stack


	int rcell;
	for(int i=0; i<rn; i++){
		rcell = rand() % num_cells;
		if(debug == true) printf("Flipping Cell %d\n",rcell);
		cells[rcell] = '0';
	}

	if(current->next == NULL){
		current->next = (hnode *) malloc(sizeof(struct hnode));
		current->next->next = NULL;
		current->next->cells = (char *) malloc(sizeof(int)*num_cells);
		for(int i=0; i<num_cells; i++) current->next->cells[i] = cells[i];//Save Cells
		current->next->action = (char *) malloc(sizeof(char)*25);
		sprintf(current->next->action,"Randomizing\n");
	}
	current = current->next;
}

//Display the board
void board::display(){
	int i,j,cell;

	if(debug == true){
		for(i=0; i<rows; i++){		//Current Row
			for(j=0; j<cols; j++){	//Current Col
				cell = (i*cols)+j;
				printf("Row: %-2d\tCol: %-2d\tCell: %-2d\n",i,j,(i*cols)+j);

			}
		}
	}

	printf("\n\n");
	for(i=0; i<rows; i++){		//Current Row
		printf("    ");
		for(j=0; j<cols; j++){	//Current Col
			cell = (i*cols)+j;
			//printf("Row: %-2d\tCol: %-2d\tCell: %-2d\n",i,j,(i*cols)+j);
			printf("%c",cells[cell]);
			if((j+1) == cols) printf("\n");

		}
	}
	printf("\n\n");
}















