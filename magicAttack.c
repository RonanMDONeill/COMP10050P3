/*
 * magicAttack.c
 *
 *  Created on: 11 Apr 2017
 *      Author: rónan
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "crossfireOperations.h"

void magicAttack(int idNum, int playerCount, struct players_ *player){
	
	int x, choice;
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
	
	scanf("%d", &choice);
	while(choice < 1 || choice > count){
		printf("Sorry that is not a valid option, please try again: ");
		scanf("%d", &choice);
	}
	
	choice -= 1;
	
	player[number[choice]].life -= (0.5 * player[idNum].magic_Skills) + (0.2 * player[idNum].smartness); // attack output

}