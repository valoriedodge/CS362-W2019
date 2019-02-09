/*
 * comparePlayerState.c
 *
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

void printFail(){
  printf("TEST FAILED: ");
}
void printSuccess(){
  printf("TEST PASSED: ");
}

int checkCardPiles(int card, struct gameState* g, struct gameState* g2){
  int errors = 0;
  if(g->supplyCount[card] != g2->supplyCount[card]){
    errors++;
    printFail();
    printf("card pile %d, count = %d, expected = %d\n", card, g->supplyCount[card], g2->supplyCount[card]);
  }
  return errors;
}

int checkEmbargoTokens(int card, struct gameState* g, struct gameState* g2){
  int errors = 0;
  if(g->embargoTokens[card] != g2->embargoTokens[card]){
    errors++;
    printFail();
    printf("embargo tokens %d, count = %d, expected = %d\n", card, g->embargoTokens[card], g2->embargoTokens[card]);
  }
  return errors;
}


void assertEqual(int val1, int val2, int * errors){
  if(val1 != val2){
    printFail();
    (*errors)++;
  }else{
    printSuccess();
  }
}

void assertNotEqual(int val1, int val2, int * errors){
  if(val1 == val2){
    printFail();
    (*errors)++;
  }else{
    printSuccess();
  }
}

int comparePlayerState(int player, struct gameState* g, struct gameState* g2){
  int i, errors = 0;
  printf("Checking Player %d State\n", player);
  for(i=0; i<g2->handCount[player];i++){
    if(g->hand[player][i] != g2->hand[player][i]){
      errors++;
      printFail();
      printf("card in hand = %d, expected = %d\n", g->hand[player][i], g2->hand[player][i]);
    }
  }
  if(g->handCount[player] != g2->handCount[player]){
    errors++;
    printFail();
    printf("hand count = %d, expected = %d\n", g->handCount[player], g2->handCount[player]);
  }
  for(i=0; i<g2->deckCount[player];i++){
    if(g->deck[player][i] != g2->deck[player][i]){
      errors++;
      printFail();
      printf("card in deck = %d, expected = %d\n", g->deck[player][i], g2->deck[player][i]);
    }

  }
  if(g->deckCount[player] != g2->deckCount[player]){
    errors++;
    printFail();
    printf("deck count = %d, expected = %d\n", g->deckCount[player], g2->deckCount[player]);
  }
  for(i=0; i<g2->discardCount[player];i++){
    if(g->discard[player][i] != g2->discard[player][i]){
      errors++;
      printFail();
      printf("card in discard = %d, expected = %d\n", g->discard[player][i], g2->discard[player][i]);
    }
  }
  if(g->discardCount[player] != g2->discardCount[player]){
    errors++;
    printFail();
    printf("discard count = %d, expected = %d\n", g->discardCount[player], g2->discardCount[player]);
  }
  if(errors == 0){
    printSuccess();
    printf("player state for player %d the same\n", player);
  }
  return errors;
}

void checkGameStateEqual(struct gameState* game, struct gameState* testGame,int *failures){
  int curr_failure, j;
  for(j=0; j<treasure_map+1;j++){
    curr_failure = checkCardPiles(j, game, testGame);
  }
  if(curr_failure == 0){
    printSuccess();
    printf("all card supply piles unaltered\n");
  }
  (*failures) += curr_failure;
  curr_failure = 0;
  for(j=0; j<treasure_map+1;j++){
    curr_failure = checkEmbargoTokens(j, game, testGame);
  }
  if(curr_failure == 0){
    printSuccess();
    printf("all embargo tokens unaltered\n");
  }
  (*failures) += curr_failure;
  for(j=0;j<game->numPlayers;j++){
    (*failures) += comparePlayerState(j, game, testGame);
  }
}
