/*
 * cardtes21.c
 * "adventurer"
 */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helper.h"

int main() {
  struct gameState game, testGame;
  int k[10] = {adventurer, adventurer, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
  int i, handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, curr_player = 0;
  int curr_failure = 0, failures = 0;
  initializeGame(2, k, 23, &game);

	printf("----------------- Testing Card: adventurer ----------------\n");

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handpos, &bonus);

	int newCards = 2;
  int coins = 0;
  int lastCard = testGame.hand[0][testGame.handCount[0]-1];
  int secondToLastCard = testGame.hand[0][testGame.handCount[0]-2];
  switch(lastCard){
    case gold:
      coins += 3;
      break;
    case copper:
      coins += 1;
      break;
    case silver:
      coins += 2;
      break;
  }
  switch(secondToLastCard){
    case gold:
      coins += 3;
      break;
    case copper:
      coins += 1;
      break;
    case silver:
      coins += 2;
      break;
  }
	assertEqual(testGame.handCount[curr_player], game.handCount[curr_player] + newCards - 1, &failures);
  printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game.handCount[curr_player] + newCards - 1);
  assertEqual(testGame.numActions, game.numActions - 1, &failures);
  printf("action count = %d, expected = %d\n", testGame.numActions, game.numActions - 1);
  assertEqual(testGame.coins, game.coins + coins, &failures);
  printf("coins = %d, expected = %d\n", testGame.coins, game.coins + coins);
  assertEqual(testGame.numBuys, game.numBuys, &failures);
  printf("buys = %d, expected = %d\n", testGame.numBuys, game.numBuys);

  for(i=0; i<treasure_map+1;i++){
    if(i != adventurer){
      curr_failure = checkCardPiles(i, &game, &testGame);
    }
  }
  if(curr_failure == 0){
    printSuccess();
    printf("all other card piles unaltered\n");
  }

  failures += curr_failure;
  failures += comparePlayerState(1, &game, &testGame);

  if(failures == 0)
	   printf("\n >>>>> ALL TESTS PASS FOR adventurer <<<<<\n\n");
  else
     printf("\n >>>>> FAILED TESTS FOR adventurer <<<<<\n\n");

	return 0;
}
