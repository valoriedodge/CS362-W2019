/*
 * cardtest2.c
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
  game.deckCount[1] = 0;
	printf("----------------- Testing Card: adventurer ----------------\n");

  // int coin_card_1 = silver, coin_card_2 = gold;
	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));
  testGame.deckCount[0] = 5;
  // testGame.handCount[0]
  for( i=0; i<5;i++){
    testGame.deck[0][i] = copper;
  }
  testGame.deck[0][3] = silver;
  testGame.deck[0][4] = gold;
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handpos, &bonus);

	int newCards = 2;
  int lastCard = testGame.hand[0][testGame.handCount[0]-1];
  int secondToLastCard = testGame.hand[0][testGame.handCount[0]-2];
  assertEqual(lastCard, silver, &failures);
  printf("last card =%d, expected = %d\n", lastCard, silver);
  assertEqual(secondToLastCard, gold, &failures);
  printf("last card =%d, expected = %d\n", secondToLastCard, gold);
	assertEqual(testGame.handCount[curr_player], game.handCount[curr_player] + newCards - 1, &failures);
  printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game.handCount[curr_player] + newCards - 1);
  assertEqual(testGame.numActions, game.numActions, &failures);
  printf("action count = %d, expected = %d\n", testGame.numActions, game.numActions);
  assertEqual(testGame.coins, game.coins, &failures);
  printf("coins = %d, expected = %d\n", testGame.coins, game.coins);
  assertEqual(testGame.numBuys, game.numBuys, &failures);
  printf("buys = %d, expected = %d\n", testGame.numBuys, game.numBuys);


  // copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));
  testGame.deckCount[0] = 5;
  // testGame.handCount[0]
  for( i=0; i<5;i++){
    testGame.deck[0][i] = copper;
  }
  testGame.deck[0][3] = adventurer;
  testGame.deck[0][4] = gold;
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handpos, &bonus);

	newCards = 2;
  lastCard = testGame.hand[0][testGame.handCount[0]-1];
  secondToLastCard = testGame.hand[0][testGame.handCount[0]-2];
  assertEqual(lastCard, copper, &failures);
  printf("last card =%d, expected = %d\n", lastCard, copper);
  assertEqual(secondToLastCard, gold, &failures);
  printf("last card =%d, expected = %d\n", secondToLastCard, gold);
	assertEqual(testGame.handCount[curr_player], game.handCount[curr_player] + newCards - 1, &failures);
  printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game.handCount[curr_player] + newCards - 1);
  assertEqual(testGame.numActions, game.numActions, &failures);
  printf("action count = %d, expected = %d\n", testGame.numActions, game.numActions);
  assertEqual(testGame.coins, game.coins, &failures);
  printf("coins = %d, expected = %d\n", testGame.coins, game.coins);
  assertEqual(testGame.numBuys, game.numBuys, &failures);
  printf("buys = %d, expected = %d\n", testGame.numBuys, game.numBuys);



  for(i=0; i<treasure_map+1;i++){
    curr_failure = checkCardPiles(i, &game, &testGame);
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
