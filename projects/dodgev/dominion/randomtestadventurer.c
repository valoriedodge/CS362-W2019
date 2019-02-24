#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helper.h"

int create_random_game(int salt, struct gameState * game);

// main function to test the functionality of adventurer kingdom card
int checkAdventurer(int curr_player, struct gameState *game){
  int curr_failure = 0, failures = 0;
  // int coin_card_1 = silver, coin_card_2 = gold;
  int i, handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

  // copy the game state to a test case
  struct gameState testGame;
  memcpy(&testGame, game, sizeof(struct gameState));

  // call the function to execute the card effect
  cardEffect(adventurer, choice1, choice2, choice3, &testGame, handpos, &bonus);

  // Check to see if there are up to 2 trease cards that can be drawn and save them to compare
  int newCards = 0;
  int drawnCards[2];
  int drawn = 1;
  for(i = game->deckCount[curr_player]-1; i>=0;i--){
    int card = game->deck[curr_player][i];
    if(card == silver || card == copper || card == gold){
      drawnCards[newCards] = card;
      newCards++;
      if(newCards == 2) break;
    }
  }
  // If 2 treasure cards weren't in the deck, see if there are 2 cards in the discard. Because of the
  // randomness of shuffle() we can't determine the order of the treasure cards and which ones will be
  // drawn and placed in the hand
  if(newCards < 2){
    drawn = 0;
    for(i = game->discardCount[curr_player]-1; i>=0;i--){
      int card = game->discard[curr_player][i];
      if(card == silver || card == copper || card == gold){
        drawnCards[newCards] = card;
        newCards++;
        if(newCards == 2) break;
      }
    }
  }
  if (newCards == 2 && drawn == 1){
    int lastCard = testGame.hand[curr_player][testGame.handCount[curr_player]-1];
    int secondToLastCard = testGame.hand[curr_player][testGame.handCount[curr_player]-2];
    assertEqual(lastCard, drawnCards[1], &failures);
    printf("last card =%d, expected = %d\n", lastCard, drawnCards[1]);
    assertEqual(secondToLastCard, drawnCards[0], &failures);
    printf("secondToLastCard =%d, expected = %d\n", secondToLastCard, drawnCards[0]);
  }
  else if(newCards == 2){
    int lastCard = testGame.hand[curr_player][testGame.handCount[curr_player]-1];
    int secondToLastCard = testGame.hand[curr_player][testGame.handCount[curr_player]-2];
    assertEqual(1, (lastCard == silver || lastCard == gold || lastCard == copper), &failures);
    printf("last card =%d, expected = %d, or %d, or %d\n", lastCard, copper, silver, gold);
    assertEqual(1, (secondToLastCard == silver || secondToLastCard == gold || secondToLastCard == copper), &failures);
    printf("secondToLastCard =%d, expected = %d, or %d, or %d\n", secondToLastCard, copper, silver, gold);
  }
  else if(newCards == 1){
    int lastCard = testGame.hand[curr_player][testGame.handCount[curr_player]-1];
    assertEqual(1, (lastCard == silver || lastCard == gold || lastCard == copper), &failures);
    printf("last card =%d, expected = %d, or %d, or %d\n", lastCard, copper, silver, gold);
  }

  // Check that the hand count is as expected
  assertEqual(testGame.handCount[curr_player], game->handCount[curr_player] + newCards-1, &failures);
  printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game->handCount[curr_player] + newCards-1);

  // Check that the rest of the game remains unaffected
  assertEqual(testGame.numActions, game->numActions, &failures);
  printf("action count = %d, expected = %d\n", testGame.numActions, game->numActions);
  assertEqual(testGame.coins, game->coins, &failures);
  printf("coins = %d, expected = %d\n", testGame.coins, game->coins);
  assertEqual(testGame.numBuys, game->numBuys, &failures);
  printf("buys = %d, expected = %d\n", testGame.numBuys, game->numBuys);

  for(i=0; i<treasure_map+1;i++){
    curr_failure += checkCardPiles(i, game, &testGame);
  }
  if(curr_failure == 0){
    printSuccess();
    printf("all other card piles unaltered\n");
  }
  failures += curr_failure;
  for(i=0; i< game->numPlayers;i++){
    if(i != curr_player){
      failures += comparePlayerState(i, game, &testGame);
    }
  }

  return failures;
}


int main() {
  int n, failures = 0;
  // time_t t;
  srand(time(NULL));

  // Number of times to create a random game to test adventure
  for( n = 0 ; n < 100 ; n++ ) {
      printf("\n----------------- Testing Card: adventurer %d ----------------\n", n);
      struct gameState game;
      int player = create_random_game(n, &game);
      failures += checkAdventurer(player, &game);
      printf("Failures: %d", failures);
   }
   if(failures == 0)
  	   printf("\n >>>>> ALL TESTS PASS FOR adventurer <<<<<\n\n");
   else
      printf("\n >>>>> %d FAILED TESTS FOR adventurer <<<<<\n\n", failures);

   return 0;
 }
