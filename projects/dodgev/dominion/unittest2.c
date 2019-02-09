/*
 * unittest1.c
 * "discardCard"
 */



#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helper.h"



int main() {
    int j, pos;
    int seed = 23;
    int numPlayer = 2;
    int curr_player = 0, card;
    int testCards[5] = {smithy, estate, silver,adventurer,village};
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState game,testGame;
    int curr_failure = 0, failures = 0;
    initializeGame(numPlayer, k, seed, &game);
    for(j = 0; j<5;j++){
      game.hand[curr_player][j] = testCards[j];
    }
    printf("----------------- Testing Unit: discardCard ----------------\n");

    for(pos = 0; pos<5;pos++){
      // copy the game state to a test case
      memcpy(&testGame, &game, sizeof(struct gameState));
      card = testCards[pos];

      printf("\n***Discarding card %d to trash***\n", card);
      discardCard(pos, curr_player, &testGame, 1);

      assertEqual(testGame.handCount[curr_player], game.handCount[curr_player] -1, &failures);
      printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game.handCount[curr_player]-1);

      assertNotEqual(testGame.hand[curr_player][pos], game.hand[curr_player][pos], &failures);
      printf("card at hand position should not be the same = %d, expected = %d\n", testGame.hand[curr_player][pos], game.hand[curr_player][pos]);

      assertEqual(testGame.deckCount[curr_player], game.deckCount[curr_player], &failures);
      printf("deck count = %d, expected = %d\n", testGame.deckCount[curr_player], game.deckCount[curr_player]);

      assertEqual(testGame.hand[curr_player][game.handCount[curr_player] - 1],-1,&failures);
      printf("hand value at last index = %d, expected = %d\n", testGame.hand[curr_player][game.handCount[curr_player] - 1],-1);

      assertEqual(testGame.discardCount[curr_player], game.discardCount[curr_player], &failures);
      printf("discard count = %d, expected = %d\n", testGame.discardCount[curr_player], game.discardCount[curr_player]);

      for(j=0; j<treasure_map+1;j++){
        curr_failure = checkCardPiles(j, &game, &testGame);
      }
      if(curr_failure == 0){
        printSuccess();
        printf("all card supply piles unaltered\n");
      }

      failures += curr_failure;
      failures += comparePlayerState(1, &game, &testGame);
    }

    for(pos = 0; pos<5;pos++){
      // copy the game state to a test case
      memcpy(&testGame, &game, sizeof(struct gameState));
      card = testCards[pos];

      printf("\n***Discarding card %d to discard***\n", card);
      discardCard(pos, curr_player, &testGame, 0);

      assertEqual(testGame.handCount[curr_player], game.handCount[curr_player] -1, &failures);
      printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game.handCount[curr_player]-1);

      assertNotEqual(testGame.hand[curr_player][pos], game.hand[curr_player][pos], &failures);
      printf("card at hand position should not be the same = %d, expected = %d\n", testGame.hand[curr_player][pos], game.hand[curr_player][pos]);

      assertEqual(testGame.deckCount[curr_player], game.deckCount[curr_player], &failures);
      printf("deck count = %d, expected = %d\n", testGame.deckCount[curr_player], game.deckCount[curr_player]);

      assertEqual(testGame.hand[curr_player][game.handCount[curr_player] - 1],-1,&failures);
      printf("hand value at last index = %d, expected = %d\n", testGame.hand[curr_player][game.handCount[curr_player] - 1],-1);

      assertEqual(testGame.discardCount[curr_player], game.discardCount[curr_player] + 1, &failures);
      printf("discard count = %d, expected = %d\n", testGame.discardCount[curr_player], game.discardCount[curr_player] + 1);

      for(j=0; j<treasure_map+1;j++){
        curr_failure = checkCardPiles(j, &game, &testGame);
      }
      if(curr_failure == 0){
        printSuccess();
        printf("all card supply piles unaltered\n");
      }

      failures += curr_failure;
      failures += comparePlayerState(1, &game, &testGame);
    }


    if(failures == 0)
  	   printf("\n >>>>> ALL TESTS PASS FOR DISCARDCARD <<<<<\n\n");
    else
       printf("\n >>>>> %d FAILED TESTS FOR DISCARDCARD <<<<<\n\n", failures);

    return 0;
}
