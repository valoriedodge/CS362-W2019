/*
 * cardtest3.c
 * "council_room"
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
  int k[10] = {adventurer, smithy, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, council_room};
  int i, handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, curr_player = 0;
  int curr_failure = 0, failures = 0;
  initializeGame(2, k, 23, &game);

	printf("----------------- Testing Card: council room ----------------\n");

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testGame, handpos, &bonus);

	int newCards = 4;
  for (i = 0; i < game.numPlayers; i++)
  {
    if ( i != curr_player )
    {
      drawCard(i, &game);
    }
  }
	assertEqual(testGame.handCount[curr_player], game.handCount[curr_player] + newCards - 1, &failures);
  printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game.handCount[curr_player] + newCards - 1);
  assertEqual(testGame.deckCount[curr_player], game.deckCount[curr_player] - newCards, &failures);
  printf("deck count = %d, expected = %d\n", testGame.deckCount[curr_player], game.deckCount[curr_player] -newCards);
  assertEqual(testGame.discardCount[curr_player], game.discardCount[curr_player] + 1, &failures);
  printf("discard count = %d, expected = %d\n", testGame.discardCount[curr_player], game.discardCount[curr_player] + 1);
  assertEqual(testGame.numActions, game.numActions - 1, &failures);
  printf("action count = %d, expected = %d\n", testGame.numActions, game.numActions - 1);
  assertEqual(testGame.coins, game.coins, &failures);
  printf("coins = %d, expected = %d\n", testGame.coins, game.coins);
  assertEqual(testGame.numBuys, game.numBuys, &failures);
  printf("buys = %d, expected = %d\n", testGame.numBuys, game.numBuys);

  for(i=0; i<treasure_map+1;i++){
    if(i != council_room){
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
	   printf("\n >>>>> ALL TESTS PASS FOR council room <<<<<\n\n");
  else
     printf("\n >>>>> FAILED TESTS FOR council room <<<<<\n\n");

	return 0;
}
