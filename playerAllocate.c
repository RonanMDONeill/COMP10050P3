/*
 * playerAllocate.c
 *
 *  Created on: 7 Apr 2017
 *      Author: kiowa
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crossfireOperations.h"
#include <unistd.h>
#include <time.h>
#include "abilities.h"



void makePlayer(int *playerCountPtr){
	setvbuf(stdout, NULL, _IONBF, 0);

	int playerCount;


    srand(time(NULL));
	int i,choice;//merged both our variables//

    printf("How many players are there? max = 6\n");
    fflush(stdout);//fixes the eclipse bug//
    scanf("%d", &playerCount);
    puts("");


        for(i=0;i<playerCount;i++){//I refer using i in for loops but feel free to change it when you modify the code //


        	printf("Enter the characters name\n");
        	fflush(stdout);
        	scanf("%s", &player[i].name);//assigning the string to a character array in the struct//
        	printf("Choose its class\n0:Ogre\n1:Wizard\n2:Elf\n3:Human\n");
        	fflush(stdout);
        	scanf("%d", &choice);
        	//assigning a player class to the struct//
            player[i].life = 100;
			player[i].userNum = i;

        	switch(choice){

        		case(0):{
        			player[i].class = Ogre;
        			break;
        		}
        		case(1):{
        			player[i].class = Wizard;
        			break;
        		}
        		case(2):{
        			player[i].class = Elf;
        			break;
        		}
        		case(3):{
        			player[i].class = Human;
        			break;
        		}
        	}


        	puts("");//prints a space//
        }

        abilities( playerCount, player);




        //printing out the name and abilities//


     /*   for(i=0;i<playerCount;i++){
            printf("%s (%s, %.2f) is on slot [%d][%d]\n", player[i].name,ClassEnum(player[i].class),player[i].life,player[i].rowp,player[i].columnP);
//            printf("smartness: %d\n",player[i].smartness);
//            printf("strength: %d\n",player[i].strength);
//            printf("magic_Skills: %d\n",player[i].magic_Skills);
//            printf("Luck: %d\n",player[i].Luck);
//            printf("Dexterity: %d\n",player[i].Dexterity);
        }*/

		*playerCountPtr = playerCount;


}




