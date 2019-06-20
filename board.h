#ifndef __BOARD_H__
#define __BOARD_H__

struct hnode{
	char *action;
	char *cells;
	struct hnode* next;
};


class board{
	public:
		board(int,int,bool);	//Constructor
		~board();	//Destructor
		void stats();
		void display();
		void randomize(int);
		bool checkwin();
		bool tap(int);
		int choices();
		void write_history();
	private:
		int rows;
		int cols;
		int num_cells;
		int nmoves;
		char *cells;
		bool debug;
		struct hnode* history;
		struct hnode* current;
};




#endif
