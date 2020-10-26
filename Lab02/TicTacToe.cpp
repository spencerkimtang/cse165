#include "TicTacToe.h"
#include <iostream>

using namespace std;

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

//constructor
TicTacToe::TicTacToe(){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			location[i][j] = 0;
		}
	}
	end = false;
	start = false;
	gameOver = false;
    x = 0.0;
    y = 1.0;
}

//making TicTacToe
void TicTacToe::drawBoard(){
    glColor3f(0, 1, 0);
    glLineWidth(5);
    glBegin(GL_LINES);
        glVertex2f(0.333, 1);
		glVertex2f(0.333, -1);
		glVertex2f(-0.333, 1);
		glVertex2f(-0.333, -1);
		glVertex2f(1, 0.333);
		glVertex2f(-1, 0.333);
		glVertex2f(1, -0.333);
		glVertex2f(-1, -0.333);
    glEnd();
}

/*
void TicTacToe::drawCross(){
	glColor3f(0, 1, 0);
	glLineWidth(5);
	glBegin(GL_LINES);



	glEnd();
}

void TicTacToe::drawCircle(){
	
}
*/

void TicTacToe::playerInput(int x, int y, bool twoPlayer){
	//setting to 1 or -1 as placeholder in matrix, since won't be able to 
	//tell if the characters
	if(twoPlayer){
		location[x][y] = 1;
		player2Turn = false;
	} 
	else {
		location[x][y] = -1;
		player2Turn = true;
	}
}

int TicTacToe::getClick(int x, int y){
	//return 1 or -1 from playerInput 
	return location[x][y];
}

bool TicTacToe::spotTaken(int x, int y){
	if(location[x][y] == 1 || location[x][y] == -1){
		return true;
	} else {
		return false;
	}
}


int TicTacToe::winnerIs(){

	if (location[0][0] != 0 && location[0][0] == location[1][0] && location[1][0] == location[2][0]){
		if (location[0][0] == 1){
			//player 1 wins
			return 1;
		} 
		else {
			//player 2 wins
			return 2;
		}
	}
	if (location[0][1] != 0 && location[0][1] == location[1][1] && location[1][1] == location[2][1]){
		if (location[0][1] == 1){
			//player 1 wins
			return 1;
		} 
		else {
			//player 2 wins
			return 2;
		}
	}
	if (location[0][2] != 0 && location[0][2] == location[1][2] && location[1][2] == location[2][2]){
		if (location[0][2] == 1){
			//player 1 wins
			return 1;
		} 
		else {
			//player 2 wins
			return 2;
		}
	} 
	
	if (location[0][0] != 0 && location[0][0] == location[0][1] && location[0][1] == location[0][2]){
		if (location[0][0] == 1){
			//player 1 wins
			return 1;
		} 
		else {
			//player 2 wins
			return 2;
		}
	}


	if (location[1][0] != 0 && location[1][0] == location[1][1] && location[1][1] == location[1][2]){
		if (location[1][0] == 1){
			//player 1 wins
			return 1;
		} 
		else {
			//player 2 wins
			return 2;
		}
	}


	if (location[2][0] != 0 && location[2][0] == location[2][1] && location[2][1] == location[2][2]){
		if (location[2][0] == 1){
			//player 1 wins
			return 1;
		} 
		else {
			//player 2 wins
			return 2;
		}
	}
	
	
	if (location[0][0] != 0 && location[0][0] == location[1][1] && location[1][1] == location[2][2]){
		if (location[0][0] == 1){
			//player 1 wins
			return 1;
		} 
		else {
			//player 2 wins
			return 2;
		}
	}
	if (location[2][0] != 0 && location[2][0] == location[1][1] && location[1][1] == location[0][2]){
		if (location[2][0] == 1){
			//player 1 wins
			return 1;
		}
		else {
			//player 2 wins
			return 2;
		}
	}
	
	//check if entire TicTacToe is populated, if so throw tie flag
	bool TicTacToefull = true;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (location[i][j] == 0){ //if theres an empty spot
				TicTacToefull = false;  //then throw not full flag
			}
		}
	}
	if (TicTacToefull){
		return 3; //report tie
	}
	
	//otherwise, report game still happening
	return 0;
}

void TicTacToe::gameEnd(){
	//resets everything and to clear screen
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			location[i][j] = 0;
		}
	}
	end = false;
	gameOver = false;
	start = false;
	onePlayer = false;
	player2Turn = false;
}

void TicTacToe::playerOutput(float &x, float &y){
	//x coordinates converted to matrix location
	if(x > -1 && x < -0.333){
		x = 0;
	} 
	else if(x > -0.333 && x < 0.333){
		x = 1;
	} 
	else if(x > 0.333 && x < 1){
		x = 2;
	}

	//y coordinates converted to matrix location
	if( y < 1 && y > 0.333){
		y = 0;
	} 
	else if (y < 0.333 && y > -0.333){
		y = 1;
	} 
	else if (y < -0.333 && y > -1){
		y = 2;
	}
}