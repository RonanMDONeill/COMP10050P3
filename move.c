/*
 * move.c
 *
 *  Created on: 9 Apr 2017
 *      Author: rónan
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "crossfireOperations.h"

void movePlayer(int idNum, struct players_ player[], int BOARD_SIZE, struct slot *upLeft,struct slot *upRight,struct slot *downLeft,struct slot *downRight, struct slot board[BOARD_SIZE][BOARD_SIZE]){
	
	int x, y, choice;
	struct slot *currSlot = NULL; // if not working switch asterix to end of slot
	struct slot *foundSlots;
	bool explored[BOARD_SIZE][BOARD_SIZE];
	int count = 0;
	int boardRow, boardColumn;
	
	
	if(player[idNum].rowp >= BOARD_SIZE/2){
		if(player[idNum].columnP >= BOARD_SIZE/2){
			currSlot = reachDesiredElement(player[idNum].rowp,player[idNum].columnP, downRight);
		}
		else{
			currSlot = reachDesiredElement(player[idNum].rowp,player[idNum].columnP,downLeft);
		}
	}
	else{
		if(player[idNum].columnP >= BOARD_SIZE/2){
			currSlot = reachDesiredElement(player[idNum].rowp,player[idNum].columnP, upRight);
		}
		else{
			currSlot = reachDesiredElement(player[idNum].rowp,player[idNum].columnP,upLeft);
		}
	}

	for(x = 0; x < BOARD_SIZE; x++){
		for(y = 0; y < BOARD_SIZE; y++){
			explored[x][y] = false;
		}
	}

	foundSlots = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(struct slot ));

	if(currSlot!= NULL){
		findSlots(BOARD_SIZE, 1, 0, currSlot, foundSlots, &count, explored); // find available slots to move to
	}
	
	printf("\n%s, where would you like to move to?\n", player[idNum].name);
	for(x = 0; x < count; x++){ // give options to move to
		printf("%d. (%d, %d)\n", x+1, foundSlots[x].row, foundSlots[x].column);
	}
	
	scanf("%d", &choice);
	while(choice < 1 || choice > count){
		printf("Sorry that is not a valid option, please try again: ");
		scanf("%d", &choice);
	}
	
	choice -= 1;
	
	// assigning new slot and slot type
	player[idNum].rowp = foundSlots[choice].row;
	player[idNum].columnP = foundSlots[choice].column;
	player[idNum].slotType == board[player[idNum].rowp][player[idNum].columnP].slotType;
	
	// changing abilities based on new slot type
	if(player[idNum].slotType == 0){
		printf("Ground!\n");
	}
	else if(player[idNum].slotType == 1){
		printf("Hill!\n");
		if(player[idNum].Dexterity < 50){
			player[idNum].strength -= 10;
		}
		else if(player[idNum].Dexterity >= 60){
			player[idNum].strength += 10;
		}
	}
	else if(player[idNum].slotType == 2){
		printf("City!\n");
		if(player[idNum].smartness > 60){
			player[idNum].magic_Skills += 10;
		}
		else if(player[idNum].smartness <= 50){
			player[idNum].Dexterity -= 10;
		}
	}
	
}