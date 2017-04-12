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

	boardSize= getBoardSize();

	createBoard(boardSize,&upLeft,&upRight,&downLeft,&downRight);

	getDesiredElement(boardSize,&row,&column);

	if(row >= boardSize/2){
			if(column >= boardSize/2)
				reachDesiredElement(row,column,downRight);
			else
			/*If the the required slot is closer to the down-left
			* corner of the board the search starts from downLeft,
			* which points to slot at position (boardSize-1, 0)*/
				reachDesiredElement(row,column,downLeft);
		} else {
			/*If the the required slot is closer to the up-right
			* corner of the board the search starts from upRight,
			* which points to slot at position (0, boarSize -1)*/
			if(column >= boardSize/2)
				reachDesiredElement(row,column, upRight);
			/*If the the required slot is closer to the up-left
			* corner of the board the search starts from upLeft,
			* which points to slot at position (0, 0)*/
			else reachDesiredElement(row,column,upLeft);
		}




return 0;

}

