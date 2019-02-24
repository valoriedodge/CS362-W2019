#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

// initialize a random game
int create_random_game(int salt, struct gameState * game){
  // time_t t;
  // srand(((unsigned) time(&t) + salt) % 10000);
  // srand(salt%1000);
  int i, j, curIdx = 0, curVal;
  int k[10] = {0,0,0,0,0,0,0,0,0,0};

  // Randomize the number of players and the current player
  int numPlayers = 2 + (rand() % 2);
  int curPlayer = rand() % numPlayers;

  // Randomize the cards in play for the game
  while(curIdx < 10){
    curVal = adventurer + (rand() %(treasure_map-adventurer));
    int present = 0;
    for(i = 0; i<10; i++){
      if(k[i] == curVal){
        present = 1;
        break;
      }
    }
    if (present == 0){
      k[curIdx] = curVal;
      curIdx++;
    }
  }
  initializeGame(numPlayers, k, rand() % 100, game);
  game->whoseTurn = curPlayer;
  // randomize the deck of the current player
  // For each supply pile, add a random number of cards to the players deck
  for(i =0; i<=treasure_map; i++){
    if (game->supplyCount[i] > 0){
      int deckcount = rand() % game->supplyCount[i];
      for (j =game->deckCount[curPlayer]; j < game->deckCount[curPlayer] + deckcount; j++){
        game->deck[curPlayer][j] = i;
      }
      game->supplyCount[i] -= deckcount;
      game->deckCount[curPlayer] += deckcount;
    }
  }

  // Shuffle the player's deck
  shuffle(curPlayer, game);

  // put a random number of cards from the deck into the discard pile
  int discardcount = rand() % game->deckCount[curPlayer];
  for (j =game->discardCount[curPlayer]; j < game->discardCount[curPlayer] + discardcount; j++){
    game->discard[curPlayer][j] = i;
  }
  game->discardCount[curPlayer] += discardcount;
  game->deckCount[curPlayer] -= discardcount;

  // Put a random number of cards from the deck into the player's hand (5 or less)
  int handcount = (rand() % game->deckCount[curPlayer]) % 5;
  for (j =game->handCount[curPlayer]; j < game->handCount[curPlayer] + handcount; j++){
    game->hand[curPlayer][j] = i;
  }
  game->handCount[curPlayer] += handcount;
  game->deckCount[curPlayer] -= handcount;

  return curPlayer;
}
