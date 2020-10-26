#ifndef TicTacToe_H
#define TicTacToe_H

struct TicTacToe{
		int location[3][3];
        float x;
        float y;
		bool start;
		bool end;
		bool gameOver;
		bool player2Turn;
        bool onePlayer;
        
	

		TicTacToe();
		void drawBoard();
		//void drawCross();
		//void drawCircle();
		void playerInput(int x, int y, bool twoPlayer);
		int getClick(int x, int y);
		bool spotTaken(int x, int y);
		int winnerIs();
		void gameEnd();
		void playerOutput(float &x, float &y);
};

#endif