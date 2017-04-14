/*
 * main.c
 *
 *  Created on: 6 Apr 2017
 *      Author: kiowa
 */

#include <stdio.h>
#include "crossfireOperations.h"

int main(){
	setvbuf(stdout,NULL,_IONBF,0);
	int row,column,boardSize;

	makePlayer();

		struct slot *upLeft;
	struct slot *upRight;
	struct slot *downLeft;
	struct slot *downRight;

	boardSize = getBoardSize();
	createBoard(boardSize,&upLeft,&upRight,&downLeft,&downRight);
	
	struct slot gameBoard[boardSize][boardSize];

	for(i = 0; i < boardSize; i++){
		for(j = 0; j < boardSize; j++){
			gameBoard[i][j].row = i;
			gameBoard[i][j].column = j;
			gameBoard[i][j].slotType = slotAssign(boardSize);
		}
	}

	printf("The board is as follows:\n");
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			printf("([%d][%d] %d)\t",gameBoard[i][j].row, gameBoard[i][j].column, gameBoard[i][j].slotType);
		}
		printf("\n");
	}
	
	srand(time(NULL));
	for(i=0;i<playerCount;i++){
		player[i].rowp = rand()%boardSize;
		player[i].columnP = rand()%boardSize;
		player[i].slotType = gameBoard[player[i].rowp][player[i].columnP].slotType;
	}
	
	for(i=0;i<playerCount;i++){
		printf("%s (%d, %.2f) is on slot [%d][%d] %d\n", player[i].name, player[i].class,player[i].life,player[i].rowp,player[i].columnP, player[i].slotType);
	}



return 0;

}

