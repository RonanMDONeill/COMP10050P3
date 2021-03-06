/*
 * userInteraction.c
 *
 *  Created on: 7 Apr 2017
 *      Author: kiowa
 *//*
 * userInteraction.c
 *
 *  Created on: 7 Apr 2017
 *      Author: kiowa
 */

#include <stdio.h>
#include "crossfireOperations.h"

int getBoardSize(){
setvbuf(stdout,NULL,_IOLBF,0);

	int boardSize;
	printf("Please enter the required size of the board\n");
	scanf("%d", &boardSize);
	return boardSize;
}


void getDesiredElement(int boardSize, int * row, int * col){
	setvbuf(stdout,NULL,_IOLBF,0);
	printf("Please enter the column and the Row of the desired slot \n");
	printf("Note that size of the board is %d\n", boardSize);


		do {
			printf("Row: ");
			scanf("%d", row);
			printf("%d\n", *row);
			if(row < 0 && *row >= boardSize)
				printf("Error: Incorrect row dimension\n");
		} while(*row < 0 && *row >= boardSize);


		do {
			printf("Column: ");
			scanf("%d", col);
			printf("%d\n", *col);
			if(*col < 0 && *col >= boardSize)
				printf("Error: Incorrect column dimension\n");
		} while(*col < 0 && *col >= boardSize);
}
