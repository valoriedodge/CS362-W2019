/*
 * unittest1.c
 * "isGameOver"
 */



#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helper.h"



int main() {
    int seed = 23;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, treasure_map, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState game,testGame;
    int failures = 0;
    initializeGame(numPlayer, k, seed, &game);

    printf("----------------- Testing Unit: isGameOver ----------------\n");

    // copy the game state to a test case
    memcpy(&testGame, &game, sizeof(struct gameState));

    printf("\n***New Game State***\n");
    assertEqual(isGameOver(&testGame), 0, &failures);
    printf("new game not over\n");
    checkGameStateEqual(&game, &testGame, &failures);

    printf("\n***Provinces Gone***\n");
    testGame.supplyCount[province] = 0;
    assertEqual(isGameOver(&testGame), 1, &failures);
    printf("province count is 0 and game is over\n");

    printf("\n***3 Supply Piles Empty***\n");
    testGame.supplyCount[province] = 1;
    testGame.supplyCount[smithy] = 0;
    testGame.supplyCount[adventurer] = 0;
    testGame.supplyCount[treasure_map] = 0;
    assertEqual(isGameOver(&testGame), 1, &failures);
    printf("3 piles empty and game is over\n");

    if(failures == 0)
  	   printf("\n >>>>> ALL TESTS PASS FOR isGameOver <<<<<\n\n");
    else
       printf("\n >>>>> %d FAILED TESTS FOR isGameOver <<<<<\n\n", failures);

    return 0;
}
