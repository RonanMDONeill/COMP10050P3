/*
 * distantAttack.c
 *
 *  Created on: 9 Apr 2017
 *      Author: rónan
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "crossfireOperations.h"

void distantAttack(int idNum, int playerCount, struct players_ *player, int BOARD_SIZE, struct slot *upLeft,struct slot *upRight,struct slot *downLeft,struct slot *downRight){
	
	int x, y, choice;
	struct slot* currSlot = NULL;
	struct slot *foundSlots;
	bool explored[BOARD_SIZE][BOARD_SIZE];
	int count = 0, count2 = 0;
	int number[7];
	
	/*If the the required slot is closer to the down-right
	 * corner of the board the search starts from downRight,
	 * which points to slot at position (boardSize-1, boarSize -1)*/
	if(player[idNum].rowp >= BOARD_SIZE/2){
		if(player[idNum].columnP >= BOARD_SIZE/2)
			currSlot = reachDesiredElement(player[idNum].rowp,player[idNum].columnP, downRight);
		else
		/*If the the required slot is closer to the down-left
		* corner of the board the search starts from downLeft,
		* which points to slot at position (boardSize-1, 0)*/
			currSlot = reachDesiredElement(player[idNum].rowp,player[idNum].columnP,downLeft);
	} else {
		/*If the the required slot is closer to the up-right
		* corner of the board the search starts from upRight,
		* which points to slot at position (0, boarSize -1)*/
		if(player[idNum].columnP >= BOARD_SIZE/2)
			currSlot = reachDesiredElement(player[idNum].rowp,player[idNum].columnP, upRight);
		/*If the the required slot is closer to the up-left
		* corner of the board the search starts from upLeft,
		* which points to slot at position (0, 0)*/
		else currSlot = reachDesiredElement(player[idNum].rowp,player[idNum].columnP,upLeft);
	}
	
	foundSlots = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(struct slot ));
	
	for(x = 0; x < BOARD_SIZE; x++){
		for(y = 0; y < BOARD_SIZE; y++){
			explored[x][y] = false;
		}
	}

	if(currSlot!= NULL){
		findSlots(BOARD_SIZE, 4, 0, currSlot, foundSlots, &count, explored); // fill a struct with found slots inside a distance of 1
	}
	
	
	// scanning found slots to see if any players are positioned in those them
	for(x = 0; x < count; x++){
		for(y = 0; y < count; y++){
			if(player[y].userNum != idNum){
				if(player[y].rowp == foundSlots[x].row && player[y].columnP == foundSlots[x].column){
					number[count2] = player[y].userNum;				// if player is found in slot, player number is placed in an array
					count2++;
				}
			}
		}
	}

	
	if(count2 > 0){
		// give options on which player to attack
		printf("%s, which player would you like to attack? Current Dexterity: %d\n", player[idNum].name, player[idNum].Dexterity);
		for(x = 0; x < count2; x++){
			printf("%d. %s -> LP: %.0f Dex: %d\n", x+1, player[number[x]].name, player[number[x]].life, player[number[x]].Dexterity);
		}	
	
		scanf("%d", &choice); // not valid option
		while(choice < 1 || choice > count2){
			printf("Sorry that is not a valid option, please try again: ");
			scanf("%d", &choice);
		}
	
		choice -= 1;
	
		if(player[number[choice]].Dexterity < player[idNum].Dexterity){ // attack output
			player[number[choice]].life -=  (0.3) * player[idNum].strength;
		}
	}
	else{
		printf("There is no one to attack!\n");
	}
}
	