//  Adventurer card test
//  cardtest2.c
//  Assignment-3
//
//  Created by Kyle Cross on 4/28/17.
//
//

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  int nextPlayer = 1;
  int i;
  struct gameState G, testG;
  int k[10] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  
  printf("\nTesting Adventurer card\n");

  //variables added for refactoring of tests
  int handpos = 0;
  int tempHand[MAX_HAND];

  //Test 1: reveal cards from correct player's deck
  
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));
  playAdventurer(&testG, thisPlayer, handpos, tempHand);
  
  if ((testG.deckCount[thisPlayer]) < (G.deckCount[thisPlayer])) {
    printf("Adventurer card: PASS: cards revealed from this player's deck.\n");
  }
  else {
    printf("Adventurer card: FAIL: cards revealed from this player's deck.\n");
  }
  
  
  
  //Test 2: hand gains two treasure cards if they are in deck
  
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));
  playAdventurer(&testG, thisPlayer, handpos, tempHand);

  
  if (testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] >= copper
       && testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] <= gold) {
    if (testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] >= copper
        && testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] <= gold) {
      printf("Adventurer card: PASS: two treasure cards added to hand\n");
    }
    else {
      printf("Adventurer card: FAIL: only one treasure card added to hand, two expected\n");
    }
  }
  else {
    printf("Adventurer card: FAIL: no treasure cards added to hand, two expected\n");
  }
  
  
  //Test 3: all other revealed cards are discarded
  
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));
  
  testG.deck[thisPlayer][testG.deckCount[thisPlayer]-1] = 20;
  testG.deck[thisPlayer][testG.deckCount[thisPlayer]-2] = 20;
  testG.deck[thisPlayer][testG.deckCount[thisPlayer]-3] = gold;
  testG.deck[thisPlayer][testG.deckCount[thisPlayer]-4] = gold;
  
  playAdventurer(&testG, thisPlayer, handpos, tempHand);
  
  if (testG.discard[thisPlayer][testG.discardCount[thisPlayer]-1] == 20
      && testG.discard[thisPlayer][testG.discardCount[thisPlayer]-2] == 20) {
    printf("Adventurer card: PASS: revealed cards that aren't treasure cards were discarded\n");
  }
  else {
    printf("Adventurer card: FAIL: revealed cards that aren't treasure cards were discarded\n");
  }
  
  
  
  //Test 4: no state change to other player's decks
  
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));
  playAdventurer(&testG, thisPlayer, handpos, tempHand);
  
  if ((testG.deckCount[nextPlayer] + testG.discardCount[nextPlayer] + testG.handCount[nextPlayer])
      == (G.deckCount[nextPlayer] + G.discardCount[nextPlayer] + G.handCount[nextPlayer])) {
    printf("Adventurer card: PASS: no state change occured for other players.\n");
  }
  else {
    printf("Adventurer card: FAIL: no state change occured for other players.\n");
  }

  
  
  //Test 5: no state change to supply piles
  
  int prevSupplyCount = 0;
  int curSupplyCount = 0;
  
  for (i = 0; i < 17; i++) {
    prevSupplyCount += G.supplyCount[i];
    curSupplyCount += testG.supplyCount[i];
  }
  
  if (prevSupplyCount == curSupplyCount) {
    printf("Adventurer card: PASS: No state change should occur to the victory card piles and kingdom card piles.\n");
  }
  else {
    printf("Adventurer card: FAIL: No state change should occur to the victory card piles and kingdom card piles.\n");
  }

  
  
  //Test 6: no treasure added to hand if deck and discard piles are empty
  
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));
  
  testG.discardCount[thisPlayer] = 0;
  testG.deckCount[thisPlayer] = 0;
  
  playAdventurer(&testG, thisPlayer, handpos, tempHand);
  
  if (testG.handCount[thisPlayer] == G.handCount[thisPlayer]) {
    printf("Adventurer card: PASS no treasure added to hand if deck and discard are empty");
  }
  else {
    printf("Adventurer card: FAIL no treasure added to hand if deck and discard are empty");
  }
  

  return 0;
}
