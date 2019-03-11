/*
 * unittest1.c
 * "gainCard"
 */



#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helper.h"



int main() {
    int i, j;
    int seed = 23;
    int numPlayer = 2;
    // int maxBonus = 10;
    // int p, r, handCount;
    // int bonus;
    int curr_player = 0, card;
    int testCards[3] = {smithy, estate, silver};
    int notPresent[2] = {steward, embargo};
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState game,testGame;
    int curr_failure = 0, failures = 0;
    initializeGame(numPlayer, k, seed, &game);

    printf("----------------- Testing Unit: gainCard ----------------\n");

    for(i = 0; i<3;i++){
      // copy the game state to a test case
      memcpy(&testGame, &game, sizeof(struct gameState));
      card = testCards[i];

      printf("\n***Adding card %d to discard***\n", card);
      gainCard(card, &testGame, 0, curr_player);

      assertEqual(testGame.handCount[curr_player], game.handCount[curr_player], &failures);
      printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game.handCount[curr_player]);

      assertEqual(testGame.deckCount[curr_player], game.deckCount[curr_player], &failures);
      printf("deck count = %d, expected = %d\n", testGame.deckCount[curr_player], game.deckCount[curr_player]);

      assertEqual(testGame.discardCount[curr_player], game.discardCount[curr_player] + 1, &failures);
      printf("discard count = %d, expected = %d\n", testGame.discardCount[curr_player], game.discardCount[curr_player] + 1);

      assertEqual(testGame.supplyCount[card], game.supplyCount[card] - 1, &failures);
      printf("supply count = %d, expected = %d\n", testGame.supplyCount[card], game.supplyCount[card] - 1);

      for(j=0; j<treasure_map+1;j++){
        if(j != card){
          curr_failure = checkCardPiles(j, &game, &testGame);
        }
      }
      if(curr_failure == 0){
        printSuccess();
        printf("all other card supply piles unaltered\n");
      }

      failures += curr_failure;
      failures += comparePlayerState(1, &game, &testGame);
    }

    for(i = 0; i<3;i++){
      // copy the game state to a test case
      memcpy(&testGame, &game, sizeof(struct gameState));
      card = testCards[i];

      printf("\n***Adding card %d to deck***\n", card);
      gainCard(card, &testGame, 1, curr_player);

      assertEqual(testGame.handCount[curr_player], game.handCount[curr_player], &failures);
      printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game.handCount[curr_player]);

      assertEqual(testGame.deckCount[curr_player], game.deckCount[curr_player] + 1, &failures);
      printf("deck count = %d, expected = %d\n", testGame.deckCount[curr_player], game.deckCount[curr_player]+1);

      assertEqual(testGame.discardCount[curr_player], game.discardCount[curr_player], &failures);
      printf("discard count = %d, expected = %d\n", testGame.discardCount[curr_player], game.discardCount[curr_player]);

      assertEqual(testGame.supplyCount[card], game.supplyCount[card] - 1, &failures);
      printf("supply count = %d, expected = %d\n", testGame.supplyCount[card], game.supplyCount[card] - 1);

      for(j=0; j<treasure_map+1;j++){
        if(j != card){
          curr_failure = checkCardPiles(j, &game, &testGame);
        }
      }
      if(curr_failure == 0){
        printSuccess();
        printf("all other card supply piles unaltered\n");
      }

      failures += curr_failure;
      failures += comparePlayerState(1, &game, &testGame);
    }

    for(i = 0; i<3;i++){
      // copy the game state to a test case
      memcpy(&testGame, &game, sizeof(struct gameState));
      card = testCards[i];

      printf("\n***Adding card %d to hand***\n", card);
      gainCard(card, &testGame, 2, curr_player);

      assertEqual(testGame.handCount[curr_player], game.handCount[curr_player] + 1, &failures);
      printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game.handCount[curr_player]+1);

      assertEqual(testGame.hand[curr_player][testGame.handCount[curr_player] -1], card, &failures);
      printf("last card in hand = %d, expected = %d\n", testGame.hand[curr_player][testGame.handCount[curr_player]-1], card);

      assertEqual(testGame.deckCount[curr_player], game.deckCount[curr_player], &failures);
      printf("deck count = %d, expected = %d\n", testGame.deckCount[curr_player], game.deckCount[curr_player]);

      assertEqual(testGame.discardCount[curr_player], game.discardCount[curr_player], &failures);
      printf("discard count = %d, expected = %d\n", testGame.discardCount[curr_player], game.discardCount[curr_player]);

      assertEqual(testGame.supplyCount[card], game.supplyCount[card] - 1, &failures);
      printf("supply count = %d, expected = %d\n", testGame.supplyCount[card], game.supplyCount[card] - 1);

      for(j=0; j<treasure_map+1;j++){
        if(j != card){
          curr_failure = checkCardPiles(j, &game, &testGame);
        }
      }
      if(curr_failure == 0){
        printSuccess();
        printf("all other card supply piles unaltered\n");
      }

      failures += curr_failure;
      failures += comparePlayerState(1, &game, &testGame);
    }

    for(i = 0; i<2;i++){
      // copy the game state to a test case
      memcpy(&testGame, &game, sizeof(struct gameState));
      card = notPresent[i];

      printf("\n***Adding card %d to discard that is not in game***\n", card);
      gainCard(card, &testGame, 0, curr_player);

      assertEqual(testGame.handCount[curr_player], game.handCount[curr_player], &failures);
      printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game.handCount[curr_player]);

      assertEqual(testGame.deckCount[curr_player], game.deckCount[curr_player], &failures);
      printf("deck count = %d, expected = %d\n", testGame.deckCount[curr_player], game.deckCount[curr_player]);

      assertEqual(testGame.discardCount[curr_player], game.discardCount[curr_player], &failures);
      printf("discard count = %d, expected = %d\n", testGame.discardCount[curr_player], game.discardCount[curr_player]);

      assertEqual(testGame.supplyCount[card], game.supplyCount[card], &failures);
      printf("supply count = %d, expected = %d\n", testGame.supplyCount[card], game.supplyCount[card]);

      for(j=0; j<treasure_map+1;j++){
        curr_failure = checkCardPiles(j, &game, &testGame);
      }
      if(curr_failure == 0){
        printSuccess();
        printf("all other card supply piles unaltered\n");
      }

      failures += curr_failure;
      failures += comparePlayerState(1, &game, &testGame);
    }

    for(i = 0; i<2;i++){
      // copy the game state to a test case
      memcpy(&testGame, &game, sizeof(struct gameState));
      card = notPresent[i];

      printf("\n***Adding card %d to deck that is not in game***\n", card);
      gainCard(card, &testGame, 1, curr_player);

      assertEqual(testGame.handCount[curr_player], game.handCount[curr_player], &failures);
      printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game.handCount[curr_player]);

      assertEqual(testGame.deckCount[curr_player], game.deckCount[curr_player], &failures);
      printf("deck count = %d, expected = %d\n", testGame.deckCount[curr_player], game.deckCount[curr_player]);

      assertEqual(testGame.discardCount[curr_player], game.discardCount[curr_player], &failures);
      printf("discard count = %d, expected = %d\n", testGame.discardCount[curr_player], game.discardCount[curr_player]);

      assertEqual(testGame.supplyCount[card], game.supplyCount[card], &failures);
      printf("supply count = %d, expected = %d\n", testGame.supplyCount[card], game.supplyCount[card]);

      for(j=0; j<treasure_map+1;j++){
        curr_failure = checkCardPiles(j, &game, &testGame);
      }
      if(curr_failure == 0){
        printSuccess();
        printf("all other card supply piles unaltered\n");
      }

      failures += curr_failure;
      failures += comparePlayerState(1, &game, &testGame);
    }

    for(i = 0; i<2;i++){
      // copy the game state to a test case
      memcpy(&testGame, &game, sizeof(struct gameState));
      card = notPresent[i];

      printf("\n***Adding card %d to hand that is not in game***\n", card);
      gainCard(card, &testGame, 2, curr_player);

      assertEqual(testGame.handCount[curr_player], game.handCount[curr_player], &failures);
      printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game.handCount[curr_player]);

      assertEqual(testGame.deckCount[curr_player], game.deckCount[curr_player], &failures);
      printf("deck count = %d, expected = %d\n", testGame.deckCount[curr_player], game.deckCount[curr_player]);

      assertEqual(testGame.discardCount[curr_player], game.discardCount[curr_player], &failures);
      printf("discard count = %d, expected = %d\n", testGame.discardCount[curr_player], game.discardCount[curr_player]);

      assertEqual(testGame.supplyCount[card], game.supplyCount[card], &failures);
      printf("supply count = %d, expected = %d\n", testGame.supplyCount[card], game.supplyCount[card]);

      for(j=0; j<treasure_map+1;j++){
        curr_failure = checkCardPiles(j, &game, &testGame);
      }
      if(curr_failure == 0){
        printSuccess();
        printf("all other card supply piles unaltered\n");
      }

      failures += curr_failure;
      failures += comparePlayerState(1, &game, &testGame);
    }

    if(failures == 0)
  	   printf("\n >>>>> ALL TESTS PASS FOR GAINCARD <<<<<\n\n");
    else
       printf("\n >>>>> FAILED TESTS FOR GAINCARD <<<<<\n\n");

    return 0;
}
