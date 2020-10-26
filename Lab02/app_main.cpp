#include <iostream>
#include <math.h>
#include "TicTacToe.h"

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif


using namespace std;

/* 
	I didn't know how to print so I searched the web. I found many different ways to output 
	I found that "glutBitmapCharacter" was the easiest for me to use (link below) 
	https://linux.die.net/man/3/glutbitmapcharacter and https://users.cs.jmu.edu/bernstdh/web/common/lectures/summary_opengl-text.php 
	where I looked up open gl functions https://docs.microsoft.com/en-us/windows/win32/opengl/glrasterpos2f 
	When I was using glVertex for positioning to print, it wouldn't work. I couldn't find an answer to why, but I found out about 
	glRasterPos2f
*/


// Store the width and height of the window
int width = 640, height = 640;

TicTacToe game;
string gameDetails = " "; 

//-------------------------------------------------------
// A function to draw the scene
//-------------------------------------------------------
void appDrawScene() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Your code here...
	//gets called after picking 1 or 2 players
	if (game.start){	
		game.drawBoard();
		
		//Setting X and 0
		char cross = 'X';
		char circle = 'O';

		//where X or O will go in each square
		//about the middle of each sqaure
		float xlocations [3] = {-0.7, 0.0, 0.7}; 			//columns
		float ylocations [3] = {0.7, 0.0, -0.7}; 			//rows
		
		//skips the first time around, draws where players clicks at
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				//location on where to print
				glRasterPos2f(xlocations[i], ylocations[j]);
				//was going to make 2 functions that would draw an X and O
				//but ran out of time 
				if (game.getClick(i, j) == 1){
					//color of X and O is based off of drawBoard() in TicTacToe.cpp
					//game.drawCross();
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,circle);
				} 
				else if (game.getClick(i, j) == -1){
					//game.drawCircle();
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,cross);
				}
			}
		}
		
		//output game details
		glColor3f(1,0.3,0.3);
		//location for outputting game details
		glRasterPos2f(-0.99,-0.98);
		for(int i = 0; i < gameDetails.length(); i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameDetails[i]);
		}
		
	} 
	//called before game starts, to start game
	else { 
		string printthis = "Left click for Single player,"; 
		glColor3f(1, 0, 0);
		glRasterPos2f(0.0, 0.0); 
		
		for(int i = 0; i < printthis.length(); i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, printthis[i]);
		}

		printthis = "Right click for TWO player."; 
		glRasterPos2f(0.0, -0.1); 
		
		for(int i = 0; i < printthis.length(); i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, printthis[i]);
		}
	}

	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();
}

//-------------------------------------------------------
// A function to convert window coordinates to scene
// We use it when a mouse event is handled
// Arguments: 	
//	x, y - the coordinates to be updated
//-------------------------------------------------------
void windowToScene(float& x, float& y) {
	x = (2.0f*(x / float(width))) - 1.0f;
	y = 1.0f - (2.0f*(y / float(height)));
}

//-------------------------------------------------------
// A function to handle window resizing
// Called every time the window is resized
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appReshapeFunc(int w, int h) {
	// Window size has changed
	width = w;
	height = h;

	double scale, center;
	double winXmin, winXmax, winYmin, winYmax;

	// Define x-axis and y-axis range
	const double appXmin = -1.0;
	const double appXmax = 1.0;
	const double appYmin = -1.0;
	const double appYmax = 1.0;

	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);

	// Set up the projection matrix using a orthographic projection that will
	// maintain the aspect ratio of the scene no matter the aspect ratio of
	// the window, and also set the min/max coordinates to be the disered ones
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;

	if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
		scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
		center = (appXmax + appXmin) / 2;
		winXmin = center - (center - appXmin)*scale;
		winXmax = center + (appXmax - center)*scale;
		winYmin = appYmin;
		winYmax = appYmax;
	}
	else {
		scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
		center = (appYmax + appYmin) / 2;
		winYmin = center - (center - appYmin)*scale;
		winYmax = center + (appYmax - center)*scale;
		winXmin = appXmin;
		winXmax = appXmax;
	}

	// Now we use glOrtho to set up our viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(winXmin, winXmax, winYmin, winYmax, -1, 1);
}


//-------------------------------------------------------
// A function to handle mouse clicks
// Called every time the mouse button goes up or down
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appMouseFunc(int b, int s, int x, int y) {
	// Convert from Window to Scene coordinates
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);

	// Your code here...
	//when game starts, change turns
	if(game.start && !game.end){
		if(s == GLUT_DOWN){
			//getting player clicks to output X or O
			game.playerOutput(mx, my); 
			//checks if spot is open
			if (!game.spotTaken(mx,my)){
				//changes turns and what to draw
				game.playerInput(mx,my,game.player2Turn); 
				if(game.player2Turn){
					gameDetails = "Player 2 it's your turn";
					//for 1 player, computer plays
					if(game.onePlayer && !game.end){
						bool computer = true;
						int xspot;
						int yspot;
						int goHere;
						/*

						where I was trying to use a for loop to pick a random spot for the computer.
						As I was thinking and working on it, I realized it would be easier to use the swtich function

						for (xspot = 0; xspot < 3; xspot++){
							for(yspot = 0; yspot < 3; yspot++){
								do{
									game.playerInput(xspot,yspot,game.player2Turn);
									computer = false;
									gameDetails = "It's now cross's turn!";
							}
							}
						}
						*/
						while(computer){
							//random number
							srand(time(NULL));
							//for numbers 1 to 9
							goHere = rand() % 9 + 1;
							//goes to random spot of 1 to 9 
							switch(goHere){
								case 1:
									xspot = 0;
									yspot = 0;
									break;
								case 2:
									xspot = 1;
									yspot = 0;
									break;
								case 3:
									xspot = 2;
									yspot = 0;
									break;
								case 4:
									xspot = 0;
									yspot = 1;
									break;
								case 5:
									xspot = 1;
									yspot = 1;
									break;
								case 6:
									xspot = 2;
									yspot = 1;
									break;
								case 7:
									xspot = 0;
									yspot = 2;
									break;
								case 8:
									xspot = 1;
									yspot = 2;
									break;
								case 9:
									xspot = 2;
									yspot = 2;
									break;
							}
							if(!game.spotTaken(xspot,yspot)){
								game.playerInput(xspot,yspot,game.player2Turn);
								computer = false;
								gameDetails = "Player 1's turn!";
							}	
						}
					}					
				} 
				else {
					gameDetails = "Player 1's turn!";
				}
			} 
			else if(game.spotTaken(mx,my)){
				gameDetails = "That spot is taken";
			}
		}
	}
	
	//where to start game, 1 or 2 players
	if(!game.start){
		if(s == GLUT_DOWN){
			//left click for 1 player
			if(b == GLUT_LEFT_BUTTON){
				game.onePlayer = true;
				gameDetails = "Single player game";
				game.start = true;
			} 
			else {
				game.onePlayer = false;
				gameDetails = "Two player game";
				game.start = true;
			}
		}
	}
	
	
	//after board is filled check for winner
	if (game.winnerIs() == 1 || game.winnerIs() == 2 || game.winnerIs() == 3){
		game.end = true;
		int result = game.winnerIs();
		if(result == 1){
			gameDetails = "Player 2 wins! Press 'R' to restart or ESC to quit.";
		} 
		else if(result == 2){
			gameDetails = "Player 1 wins! Press 'R' to restart or ESC to quit.";
		} 
		else if(result == 3){
			gameDetails = "Tie! Press 'R' to restart or ESC to quit.";
		}
		game.gameOver = true;
	}

	// Redraw the scene by calling appDrawScene above
	// so that the point we added above will get painted
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle mouse dragging
// Called every time mouse moves while button held down
// Arguments: 	
//	x, y - current coordinates of the mouse
//-------------------------------------------------------
void appMotionFunc(int x, int y) {
	// Convert from Window to Scene coordinates
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);

	// Your code here...

	// Again, we redraw the scene
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle keyboard events
// Called every time a key is pressed on the keyboard
// Arguments: 	
//	key  - the key that was pressed
//	x, y - coordinates of the mouse when key is pressed
//-------------------------------------------------------
void appKeyboardFunc(unsigned char key, int x, int y) {
	// Define what should happen for a given key press 
	switch (key) {
	// Escape was pressed. Quit the program
	case 27:
		exit(0);
		break;
		// More cases here if you need...
	//restarts the game/clears board
	case 'r': 
		game.gameEnd();
	}
	// After all the state changes, redraw the scene
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window position, size, and title
	glutInitWindowPosition(20, 60);
	// Start with a slightly smaller window (bug in macOS Catalina)
	glutInitWindowSize(width-1, height-1);

	// Create the window
	glutCreateWindow("Tic Tac Toe by Spencer Tang");

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);


	// Set callback for drawing the scene
	glutDisplayFunc(appDrawScene);

	// Set callback for resizing th window
	glutReshapeFunc(appReshapeFunc);

	// Set callback to handle mouse clicks
	glutMouseFunc(appMouseFunc);

	// Set callback to handle mouse dragging
	glutMotionFunc(appMotionFunc);

	// Set callback to handle keyboad events
	glutKeyboardFunc(appKeyboardFunc);
    
	// Resize your window to the desired size (bug in macOS Catalina)
    glutReshapeWindow(width, height);

	// Start the main loop
	glutMainLoop();
}
