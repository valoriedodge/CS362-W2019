#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
	       struct gameState *state, int handPos, int *bonus);

int chooseAdventurer(struct gameState *state, int handPos);
int chooseSmithy(struct gameState * state, int HandPos);
int chooseMine(struct gameState * state, int choice1, int choice2, int handPos);
int chooseRemodel(struct gameState * state, int choice1, int choice2, int handPos);
int chooseBaron(struct gameState * state, int choice1);

#endif
