/*
 * unittest1.c
 * "buyCard"
 */



#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helper.h"



int main() {
    int j;
    int seed = 23;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, treasure_map, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState game,testGame;
    int curr_failure = 0, curr_player = 0,failures = 0, card;
    initializeGame(numPlayer, k, seed, &game);

    printf("----------------- Testing Unit: buyCard ----------------\n");

    // copy the game state to a test case
    memcpy(&testGame, &game, sizeof(struct gameState));

    assertEqual(buyCard(ambassador,&testGame), -1, &failures);
    printf("trying to buy card not available in game\n");
    checkGameStateEqual(&game, &testGame, &failures);

    card = smithy;

    testGame.supplyCount[card] = 0;
    game.supplyCount[card] = 0;
    assertEqual(buyCard(card,&testGame), -1, &failures);
    printf("trying to buy card with no supply left\n");
    // checkGameStateEqual(&game, &testGame, &failures)

    testGame.supplyCount[card] = 10;
    game.supplyCount[card] = 10;

    testGame.numBuys = 0;
    game.numBuys = 0;
    assertEqual(buyCard(card,&testGame), -1, &failures);
    printf("trying to buy card with no buys left\n");
    // checkGameStateEqual(&game, &testGame, &failures)

    testGame.numBuys = 1;
    game.numBuys = 1;

    testGame.coins = 0;
    game.coins = 0;
    assertEqual(buyCard(card,&testGame), -1, &failures);
    printf("trying to buy card with no coins left\n");
    // checkGameStateEqual(&game, &testGame, &failures)

    testGame.coins = getCost(card) - 1;
    game.coins = getCost(card) - 1;
    assertEqual(buyCard(card,&testGame), -1, &failures);
    printf("trying to buy card with not enough coins\n");
    // checkGameStateEqual(&game, &testGame, &failures)

    testGame.coins = getCost(card);
    game.coins = getCost(card);
    assertEqual(buyCard(card,&testGame), 0, &failures);
    printf("trying to buy card with just enough coins\n");

    assertEqual(testGame.handCount[curr_player], game.handCount[curr_player], &failures);
    printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game.handCount[curr_player]);

    assertEqual(testGame.deckCount[curr_player], game.deckCount[curr_player], &failures);
    printf("deck count = %d, expected = %d\n", testGame.deckCount[curr_player], game.deckCount[curr_player]);

    assertEqual(testGame.discardCount[curr_player], game.discardCount[curr_player] + 1, &failures);
    printf("discard count = %d, expected = %d\n", testGame.discardCount[curr_player], game.discardCount[curr_player] + 1);

    assertEqual(testGame.supplyCount[card], game.supplyCount[card] - 1, &failures);
    printf("supply count = %d, expected = %d\n", testGame.supplyCount[card], game.supplyCount[card] - 1);

    assertEqual(testGame.coins, game.coins - getCost(card), &failures);
    printf("coin count = %d, expected = %d\n", testGame.coins, game.coins - getCost(card));

    assertEqual(testGame.numBuys, game.numBuys - 1, &failures);
    printf("buys count = %d, expected = %d\n", testGame.numBuys, game.numBuys - 1);


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

    if(failures == 0)
  	   printf("\n >>>>> ALL TESTS PASS FOR buyCard <<<<<\n\n");
    else
       printf("\n >>>>> %d FAILED TESTS FOR buyCard <<<<<\n\n", failures);

    return 0;
}
