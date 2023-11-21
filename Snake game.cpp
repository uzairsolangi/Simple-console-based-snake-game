#include<iostream>
#include<conio.h>
#include<windows.h> //for using system("cls") function
#include<cstdlib> //for rand() function. 
//The purpose of using rand() function is spawns the reward randomly on the map.

using namespace std;

bool gameEnd;
const int width =20;
const int height =10;
int x, y, rewardX, rewardY, score;
enum direction {
	STOP =0, UP, DOWN, LEFT, RIGHT
};
direction dir;
int tailX[300], tailY[300];
int nTail;

void initializeGame(){ /*this function is for the the functionality of the objects in the game
                        when it's not started yet*/
	dir= STOP;
	gameEnd= false;
	rewardX= rand() % width;
	rewardY= rand() % height;
	x= width/2;
	y= height/2;
	score=0;
	nTail=0;
}

void displayGame(){ /*this function is for the the design and the making of the map and the objects.*/ 
	system("cls");
	cout<<"\t\t\t\t***************************SNAKE GAME*******************************"<<endl;
	cout<<endl;
	cout<<"\t\t\t\t\t**********PRESS W, S, A, D TO START THE GAME***********"<<endl;
	cout<<"\t\t\t\t\t*************PRESS X TO TERMINATE THE GAME*************"<<endl;
	
	for(int a=0; a < width+2; a++){ //top of the map.
		cout<<"$";
	}
		cout<<endl;
		
	for(int a=0; a < height; a++){
		for(int b=0; b< width; b++){
			if(b==0)
			cout<<"$"; //left wall of the map.
			if(a==y && b==x)
			cout<<"O"; //snake head.
			else if(a==rewardY && b==rewardX)
			cout<<"R"; //reward for points.
			
			else {
				bool print=false;
				for(int c=0; c<nTail; c++){
					if(tailX[c]==b && tailY[c]==a){
						cout<<"o"; //tail of the snake.
						print=true;
					}
					
				}
				if(!print)
				cout<<" ";
			}
			if(b==width-1)
			cout<<"$"; //Right wall of the map.
		}
		cout<<endl;
	}	
	for(int a=0; a<width+2; a++)
	cout<<"$"; //Bottom of the map.
	cout<<endl;
	cout<<"SCORE: "<<score<<endl;
}

void processInput() {
    if (_kbhit()) {
        char key = _getch();
        // Check if the key is a valid direction
        if ((key == 'w' && dir != DOWN) ||
            (key == 's' && dir != UP) ||
            (key == 'a' && dir != RIGHT) ||
            (key == 'd' && dir != LEFT)) {
            // If the key is a valid direction and not opposite, update the direction
        switch (key) {
            case 'w':
            dir = UP;
            break;
            
            case 's':
            dir = DOWN;
            break;
            
            case 'a':
            dir = LEFT;
            break;
            
            case 'd':
            dir = RIGHT;
            break;
            }
        } else if (key == 'x') {
            gameEnd = true;
        }
    }
}

void updateGameState(){  //this function is the logical part of the game.
int	oldX=tailX[0];
int	oldY=tailY[0];
	int old2X, old2Y;
	tailX[0]=x;
	tailY[0]=y;
	
	for(int a=1; a<nTail; a++){
		old2X=tailX[a];
		old2Y=tailY[a];
		tailX[a]=oldX;
		tailY[a]=oldY;
		oldX=old2X;
		oldY=old2Y;
	}
	
	switch(dir){  
		case UP:
			y--;
			break;
			
		case DOWN:
		    y++;
			break;
			
		case LEFT:
		    x--;
			break;
			
		case RIGHT:
		    x++;
			break;
			
		default:
		    break;		
	}
	
	if(x >=width)
	    x=0;
	else if(x < 0)
	    x=width-1;
	
	if(y >= height)
	    y=0;
	else if(y < 0)
	    y = height-1;
		
    for(int a=0; a<nTail; a++)
	   if(tailX[a]==x && tailY[a]==y) //for when the head touches the tail and game terminates.
	       gameEnd = true;  
		   
	if (x == rewardX && y == rewardY) {
        score += 10;
        rewardX = rand() % width;
        rewardY = rand() % height;
        nTail++;
    }	     	    
}

int main(){
	initializeGame();
	while(!gameEnd){  
	displayGame();
	processInput();
	updateGameState();
	Sleep(100); //for speed
	}
  return 0;	
}//END MAIN.
//END PROGRAM.
