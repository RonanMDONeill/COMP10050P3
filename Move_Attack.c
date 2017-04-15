/*
 * Move_Attack.c
 *
 *  Created on: 14 Apr 2017
 *      Author: rónan
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "crossfireOperations.h"


void moveORattack(int idNum,int playerCount, struct players_ *player, int BOARD_SIZE, struct slot *upLeft,struct slot *upRight,struct slot *downLeft,struct slot *downRight, struct slot board[BOARD_SIZE][BOARD_SIZE]){

	int x, choice;
	int option = 0;

	if(player[idNum].life > 0){
		while(option == 0){
			printf("\n%s, would you like to:\n", player[idNum].name);

			if(player[idNum].magic_Skills + player[idNum].smartness > 150){
				printf("1. Move slot?\n2. Attempt a near attack?\n3. Attempt a distant attack?\n4. Attempt a magic attack?\n");
				scanf("%d", &choice);
					while(choice < 1 || choice > 4){
					printf("Sorry that is not a valid option, please try again: ");
					scanf("%d", &choice);
				}
			}
			else{
				printf("1. Move slot?\n2. Attempt a near attack?\n3. Attempt a distant attack?\n");
				scanf("%d", &choice);
				while(choice < 1 || choice > 3){
					printf("Sorry that is not a valid option, please try again: ");
					scanf("%d", &choice);
				}
			}

			switch(choice){
				case 1: movePlayer(idNum, player, BOARD_SIZE, upLeft, upRight, downLeft, downRight, board, &option); break;
				case 2: nearAttack(idNum, playerCount, player, BOARD_SIZE, upLeft, upRight, downLeft, downRight, &option); break;
				case 3: distantAttack(idNum, playerCount, player, BOARD_SIZE, upLeft, upRight, downLeft, downRight, &option); break;
				case 4: magicAttack(idNum, playerCount, player, &option); break;
			}
		}
	}
}

/*
 * nearAttack.c
 *
 *  Created on: 7 Apr 2017
 *      Author: rónan
 */

void nearAttack(int idNum, int playerCount, struct players_ *player, int BOARD_SIZE, struct slot *upLeft,struct slot *upRight,struct slot *downLeft,struct slot *downRight, int *opt){

	int x, y, choice, option;
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
		findSlots(BOARD_SIZE, 1, 0, currSlot, foundSlots, &count, explored); // fill a struct with found slots inside a distance of 1
	}


	// scanning found slots to see if any players are positioned in those them
	for(x = 0; x < count; x++){
		for(y = 0; y < count; y++){
			if(player[y].rowp == foundSlots[x].row && player[y].columnP == foundSlots[x].column){
				number[count2] = player[y].userNum;				// if player is found in slot, player number is placed in an array
				count2++;
			}
		}
	}

	for(x = 0; x < playerCount; x++){ // scan same slot as current player
		if(player[x].userNum != idNum){ // if player found is not current player
			if(player[x].rowp == currSlot->row && player[x].columnP == currSlot->column){
				number[count2] = player[x].userNum;
				count2++;
			}
		}
	}

	if(count2 > 0){
		// give options on which player to attack
		printf("%s, which player would you like to attack? Current Strength: %d\n", player[idNum].name, player[idNum].strength);
		for(x = 0; x < count2; x++){
			printf("%d. %s -> LP: %.0f Str: %d\n", x+1, player[number[x]].name, player[number[x]].life, player[number[x]].strength);
		}

		printf("%d. Cancel\n", x + 1);

		scanf("%d", &choice); // not valid option
		while(choice < 1 || choice > count2 + 1){
			printf("Sorry that is not a valid option, please try again: ");
			scanf("%d", &choice);
		}

		choice -= 1;
		if(choice < count2){
			if(player[number[choice]].strength <= 70){ // attack outcomes
				player[number[choice]].life -=  (0.5) * player[idNum].strength;
				printf("You deal %0.f damage!\n",(0.5) * player[idNum].strength);
			}
			else if(player[number[choice]].strength > 70){
				player[idNum].life -= (0.3) * player[number[choice]].strength;
				printf("You take %.0f damage!!\n", (0.3) * player[number[choice]].strength);
			}
			option = 1;
			*opt = option;
		}
		else{
			option = 0;
			*opt = option;
		}
	}
	else{
		printf("There is no one to attack!\n");
		option = 0;
		*opt = option;
	}

}

/*
 * distantAttack.c
 *
 *  Created on: 9 Apr 2017
 *      Author: rónan
 */


void distantAttack(int idNum, int playerCount, struct players_ *player, int BOARD_SIZE, struct slot *upLeft,struct slot *upRight,struct slot *downLeft,struct slot *downRight, int *opt){

	int x, y, choice;
	struct slot* currSlot = NULL;
	struct slot *foundSlots;
	bool explored[BOARD_SIZE][BOARD_SIZE];
	int count = 0, count2 = 0;
	int number[7];
	int option;

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

		printf("%d. Cancel\n", x + 1);

		scanf("%d", &choice); // not valid option
		while(choice < 1 || choice > count2+1){
			printf("Sorry that is not a valid option, please try again: ");
			scanf("%d", &choice);
		}

		choice -= 1;

		if(choice < count2){
			if(player[number[choice]].Dexterity < player[idNum].Dexterity){ // attack output
				player[number[choice]].life -=  (0.3) * player[idNum].strength;
				printf("You deal %.0f damage!\n", (0.3) * player[idNum].strength);
			}
			else{
				printf("You deal no damage!!\n");
			}
			option = 1;
			*opt = option;
		}
		else{
			option = 0;
			*opt = option;
		}
	}
	else{
		printf("There is no one to attack!\n");
		option = 0;
		*opt = option;
	}
}


/*
 * magicAttack.c
 *
 *  Created on: 11 Apr 2017
 *      Author: rónan
 */


void magicAttack(int idNum, int playerCount, struct players_ *player, int *opt){

	int x, choice, option;
	int number[7];
	int count = 0, attacked = 0;

	for(x = 0; x < playerCount; x++){ // find players to attack
		if(player[x].userNum != idNum){
			number[count] = player[x].userNum;
			count++;
		}
	}


	printf("Which player would you like to attack?\n");
	for(x = 0; x < count; x++){ // give options
		attacked = number[x];
		printf("%d. %s -> %.2f\n", x+1, player[attacked].name, player[attacked].life);
	}

	printf("%d. Cancel\n", x + 1);

	scanf("%d", &choice);
	while(choice < 1 || choice > count + 1){
		printf("Sorry that is not a valid option, please try again: ");
		scanf("%d", &choice);
	}

	choice -= 1;

	if(choice < count){
		player[number[choice]].life -= (0.5 * player[idNum].magic_Skills) + (0.2 * player[idNum].smartness); // attack output
		printf("You deal %0.f damage!\n", (0.5 * player[idNum].magic_Skills) + (0.2 * player[idNum].smartness));
		option = 1;
		*opt = option;
	}

	else{
		option = 0;
		*opt = option;
	}
}

/*
 * move.c
 *
 *  Created on: 9 Apr 2017
 *      Author: rónan
 */


void movePlayer(int idNum, struct players_ *player, int BOARD_SIZE, struct slot *upLeft,struct slot *upRight,struct slot *downLeft,struct slot *downRight, struct slot board[BOARD_SIZE][BOARD_SIZE], int *opt){

	int x, y, choice;
	struct slot *currSlot = NULL; // if not working switch asterix to end of slot
	struct slot *foundSlots;
	bool explored[BOARD_SIZE][BOARD_SIZE];
	int count = 0;
	int boardRow, boardColumn;
	int option;


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

	printf("%d. Cancel\n", x + 1);

	scanf("%d", &choice);
	while(choice < 1 || choice > count + 1){
		printf("Sorry that is not a valid option, please try again: ");
		scanf("%d", &choice);
	}

	choice -= 1;

	if(choice < count){
		// assigning new slot and slot type
		player[idNum].rowp = foundSlots[choice].row;
		player[idNum].columnP = foundSlots[choice].column;
		player[idNum].slotType = board[player[idNum].rowp][player[idNum].columnP].slotType;

		// changing abilities based on new slot type
		if(player[idNum].slotType == 0){
			printf("You are now at level ground!\nYour abilities have not changed.\n");
		}
		else if(player[idNum].slotType == 1){
			printf("You are now on a hill!\n");
			if(player[idNum].Dexterity < 50){
				player[idNum].strength -= 10;
				printf("You lose 10 strength points!!\n");
			}
			else if(player[idNum].Dexterity >= 60){
				player[idNum].strength += 10;
				printf("You gain 10 strength points!\n");
			}
		}
		else if(player[idNum].slotType == 2){
			printf("You are now in a City!\n");
			if(player[idNum].smartness > 60){
				player[idNum].magic_Skills += 10;
				printf("You gain 10 magic points!\n");
			}
			else if(player[idNum].smartness <= 50){
				player[idNum].Dexterity -= 10;
				printf("You lose 10 dexterity points!!\n");
			}
		}
		option = 1;
		*opt = option;
	}
	else{
		option = 0;
		*opt = option;
	}

}
