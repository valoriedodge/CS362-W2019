#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

// initialize a random game
int create_random_game(int salt, struct gameState * game){

  int i, j, curIdx = 0, curVal;
  int k[10] = {0,0,0,0,0,0,0,0,0,0};

  // Randomize the number of players and the current player
  int numPlayers = 2 + floor(Random() * 2);
  int curPlayer = floor(Random() * numPlayers);

  // Randomize the cards in play for the game
  while(curIdx < 10){
    curVal = adventurer + floor(Random() * (treasure_map-adventurer));
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
  // initializeGame(numPlayers, k, floor(Random() * 100), game);
  //set number of players
  game->numPlayers = numPlayers;
  game->whoseTurn = curPlayer;
  //initialize supply
  ///////////////////////////////

  //set number of Curse cards
  if (numPlayers == 2)
    {
      game->supplyCount[curse] = 10;
    }
  else if (numPlayers == 3)
    {
      game->supplyCount[curse] = 20;
    }
  else
    {
      game->supplyCount[curse] = 30;
    }

  //set number of Victory cards
  if (numPlayers == 2)
    {
      game->supplyCount[estate] = 14;
      game->supplyCount[duchy] = 8;
      game->supplyCount[province] = 8;
    }
  else
    {
      game->supplyCount[estate] = 18;
      game->supplyCount[duchy] = 12;
      game->supplyCount[province] = 12;
    }

  //set number of Treasure cards
  game->supplyCount[copper] = 60;
  game->supplyCount[silver] = 40;
  game->supplyCount[gold] = 30;

  //set number of Kingdom cards
  for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
    {
      for (j = 0; j < 10; j++)           		//loop chosen cards
    	{
    	  if (k[j] == i)
    	    {
    	      //check if card is a 'Victory' Kingdom card
    	      if (k[j] == great_hall || k[j] == gardens)
    		{
    		  if (numPlayers == 2){
    		    game->supplyCount[i] = 8;
    		  }
    		  else{ game->supplyCount[i] = 12; }
    		}
    	      else
    		{
    		  game->supplyCount[i] = 10;
    		}
    	      break;
    	    }
    	  else    //card is not in the set choosen for the game
    	    {
    	      game->supplyCount[i] = -1;
    	    }
    	}

    }

    for (i = 0; i < numPlayers; i++)
      {
        //initialize hand size to zero
        game->handCount[i] = 0;
        game->discardCount[i] = 0;
        game->deckCount[i] = 0;
      }

    //set embargo tokens to 0 for all supply piles
    for (i = 0; i <= treasure_map; i++)
      {
        game->embargoTokens[i] = 0;
      }

    //initialize first player's turn
    game->outpostPlayed = 0;
    game->phase = 0;
    game->numActions = 1;
    game->numBuys = 1;
    game->playedCardCount = 0;
    game->handCount[game->whoseTurn] = 0;
    game->coins = 0;


  // randomize the deck of the current player
  // For each supply pile, add a random number of cards to the players deck
  for(i =0; i<=treasure_map; i++){
    if (game->supplyCount[i] > 0){
      int deckcount = floor(Random() * game->supplyCount[i]);
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
  int discardcount = floor(Random() * game->deckCount[curPlayer]);
  for (j =game->discardCount[curPlayer]; j < game->discardCount[curPlayer] + discardcount; j++){
    game->discard[curPlayer][j] = i;
  }
  game->discardCount[curPlayer] += discardcount;
  game->deckCount[curPlayer] -= discardcount;

  // Put a random number of cards from the deck into the player's hand (7 or less)
  int handcount = (int)(floor(Random() * game->deckCount[curPlayer]) )% 7;
  for (j =game->handCount[curPlayer]; j < game->handCount[curPlayer] + handcount; j++){
    game->hand[curPlayer][j] = i;
  }
  game->handCount[curPlayer] += handcount;
  game->deckCount[curPlayer] -= handcount;

  return curPlayer;
}
