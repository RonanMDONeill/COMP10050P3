/*
 * main.c
 *
 *  Created on: 6 Apr 2017
 *      Author: kiowa
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crossfireOperations.h"
#include <unistd.h>
#include <time.h>
const char *ClassEnum(int class);
const char *TypeEnum(int slotType);
int main(){
	setvbuf(stdout,NULL,_IONBF,0);

	int row,column,boardSize;
	int i, j;
	int playerCount, check = 0;


	makePlayer(&playerCount);

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

	srand(time(NULL));
	for(i=0;i<playerCount;i++){
		player[i].rowp = rand()%boardSize;
		player[i].columnP = rand()%boardSize;
		player[i].slotType = gameBoard[player[i].rowp][player[i].columnP].slotType;
	}


	while(playerCount > 1){

		printf("\nThe board is as follows:\n");
		for(int i=0;i<boardSize;i++){
			for(int j=0;j<boardSize;j++){
				printf("([%d][%d] %s)\t",gameBoard[i][j].row, gameBoard[i][j].column, TypeEnum(gameBoard[i][j].slotType));
			}
			printf("\n");
		}

		for(i=0;i<playerCount;i++){
			printf("%s (%s, %.2f) is on slot [%d][%d] %s\n", player[i].name, ClassEnum(player[i].class),player[i].life,player[i].rowp,player[i].columnP, TypeEnum(player[i].slotType));
		}

		for(i = 0; i < playerCount; i++){
			moveORattack(player[i].userNum, playerCount, player, boardSize, upLeft, upRight, downLeft, downRight, gameBoard);
		}

		for(i = 0; i < playerCount; i++){
			printf("%s: %.0f -> [%d][%d]\n", player[i].name, player[i].life, player[i].rowp, player[i].columnP);
		}

		for(i = 0; i < playerCount; i++){
			if(player[i].life <= 0){
				for(j = i; j < playerCount - 1; j++){
					player[j] = player[j+1];
				}
				playerCount--;
			}
		}


	}

	printf("\n%s wins!!!", player[0].name);

	return 0;

}
const char *ClassEnum(int class){
		switch(class){
		case Ogre: return "Ogre";
		case Wizard: return "Wizard";
		case Elf: return "Elf";
		case Human: return "Human";
		}
}

const char *TypeEnum(int slotType){
		switch(slotType){
		case ground: return "Ground";
		case hill: return "Hill";
		case city: return "City";

		}
	}


