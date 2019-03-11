#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helper.h"

int create_random_game(int salt, struct gameState * game);

// main function to test the functionality of council room kingdom card
int checkCouncilRoom(int curr_player, struct gameState *game){
  int curr_failure = 0, failures = 0;
  // int coin_card_1 = silver, coin_card_2 = gold;
  int i, handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

  // copy the game state to a test case
  struct gameState testGame;
  memcpy(&testGame, game, sizeof(struct gameState));

  // call the function to execute the card effect
  cardEffect(council_room, choice1, choice2, choice3, &testGame, handpos, &bonus);

  int newCards = 4;
  for (i = 0; i < game->numPlayers; i++)
  {
    if ( i != curr_player )
    {
      drawCard(i, game);
    }
  }

  if(game->deckCount[curr_player] >= 4){
    assertEqual(testGame.handCount[curr_player], game->handCount[curr_player] + newCards -1, &failures);
    printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game->handCount[curr_player] + newCards-1);
    assertEqual(testGame.deckCount[curr_player], game->deckCount[curr_player] -newCards, &failures);
    printf("deck count = %d, expected = %d\n", testGame.deckCount[curr_player], game->deckCount[curr_player] -newCards);
  }
  else if(game->deckCount[curr_player] + game->discardCount[curr_player] >= 4){
    assertEqual(testGame.handCount[curr_player], game->handCount[curr_player] + newCards-1, &failures);
    printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game->handCount[curr_player] + newCards-1);
  }
  else{
    newCards = game->deckCount[curr_player] + game->discardCount[curr_player];
    assertEqual(testGame.handCount[curr_player], game->handCount[curr_player] + newCards-1, &failures);
    printf("hand count = %d, expected = %d\n", testGame.handCount[curr_player], game->handCount[curr_player] + newCards-1);
  }

  assertEqual(testGame.numActions, game->numActions, &failures);
  printf("action count = %d, expected = %d\n", testGame.numActions, game->numActions);
  assertEqual(testGame.coins, game->coins, &failures);
  printf("coins = %d, expected = %d\n", testGame.coins, game->coins);
  assertEqual(testGame.numBuys, game->numBuys + 1, &failures);
  printf("buys = %d, expected = %d\n", testGame.numBuys, game->numBuys + 1);

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
  SelectStream(1);
  PutSeed((long)13);

  // Number of times to create a random game to test council room
  for( n = 0 ; n < 100 ; n++ ) {
      printf("\n----------------- Testing Card: council room %d ----------------\n", n);
      struct gameState game;
      int player = create_random_game(n, &game);
      failures += checkCouncilRoom(player, &game);
      printf("Failures: %d", failures);
   }
   if(failures == 0)
  	   printf("\n >>>>> ALL TESTS PASS FOR council room <<<<<\n\n");
   else
      printf("\n >>>>> %d FAILED TESTS FOR council room <<<<<\n\n", failures);

   return 0;
 }
