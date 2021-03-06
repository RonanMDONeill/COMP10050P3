/*
 * crossfireOperations.h
 *
 *  Created on: 7 Apr 2017
 *      Author: kiowa + rónan
 */

#ifndef CROSSFIREOPERATIONS_H_
#define CROSSFIREOPERATIONS_H_


typedef int bool;
enum{false,true};

enum slotType{
	ground, hill, city
};

struct slot{
	int row;
	int column;
	struct slot *left;
	struct slot *right;
	struct slot *up;
	struct slot *down;
	enum slotType slotType;
}slot;

enum Classes{
	Ogre , Wizard , Elf , Human
};

struct players_{
    	char name[20];
        enum Classes class;
    	int smartness;
    	int strength;
    	int magic_Skills;
    	int Luck;
    	int Dexterity;
    	double life;
    	int rowp;
    	int columnP;
		enum slotType slotType;
		int userNum;

    }player[7];


int getBoardSize(); // userInteraction.c

void getDesiredElement(int maxsize,int*row,int*col); // userInteraction.c


void createBoard(int boardSize,struct slot **upLeft,struct slot **upRight,struct slot **downLeft,struct slot **downRight); // boardCreation.c


struct slot *  reachDesiredElement(int row, int column, struct slot * initialSlot); // boardCreation.c

void makePlayer(int *playerCountPtr); // playerAllocate.c

void moveORattack(int idNum,int playerCount, struct players_ *player, int BOARD_SIZE, struct slot *upLeft,struct slot *upRight,struct slot *downLeft,struct slot *downRight, struct slot board[BOARD_SIZE][BOARD_SIZE]);

void nearAttack(int idNum, int playerCount, struct players_ *player, int BOARD_SIZE, struct slot *upLeft,struct slot *upRight,struct slot *downLeft,struct slot *downRight, int *opt);

void movePlayer(int idNum, struct players_ *player, int BOARD_SIZE, struct slot *upLeft,struct slot *upRight,struct slot *downLeft,struct slot *downRight, struct slot board[BOARD_SIZE][BOARD_SIZE], int *opt);

void magicAttack(int idNum, int playerCount, struct players_ *player, int *opt);

void distantAttack(int idNum, int playerCount, struct players_ *player, int BOARD_SIZE, struct slot *upLeft,struct slot *upRight,struct slot *downLeft,struct slot *downRight, int *opt);

void findSlots(int boardSize, int reqDist, int currDist,  struct slot * currSlot, struct slot * foundSlots, int * count,  bool explored[boardSize][boardSize]);




int slotAssign(int boardSize); // boardCreation.c
#endif

