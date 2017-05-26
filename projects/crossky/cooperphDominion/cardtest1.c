//
//  cardtest1.c
//  Assignment-3
//
//  Created by Kyle Cross on 4/27/17.
//  Copyright © 2017 Kyle Cross. All rights reserved.
//

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
  int handpos = 0;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  int nextPlayer = 1;
  int i;
  struct gameState G, testG;
  int k[10] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  
  printf("\nTesting Smithy card\n");
  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  
  memcpy(&testG, &G, sizeof(struct gameState));
  
  
  //Test 1: Current player should receive exactly 3 cards.
  
  playSmithy(&testG, thisPlayer, handpos);
  
  if (testG.handCount[thisPlayer] == (G.handCount[thisPlayer] + 2) &&
      testG.playedCardCount == G.playedCardCount + 1) {
    printf("Smithy card: PASS: three cards added to hand\n");
  }
  else {
    printf("Smithy card: FAIL: three cards added to hand\n");
  }
  
  
  //Test 2: 3 cards should come from his own pile.
  //printf("%d, %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  
  if ((testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer])
       < (G.deckCount[thisPlayer] + G.discardCount[thisPlayer])) {
    printf("Smithy card: PASS: cards came from correct player's pile\n");
  }
  else {
    printf("Smithy card: FAIL: cards came from correct player's pile\n");
  }
  
  
  //Test 3: No state change should occur for other players.
  
  if ((testG.deckCount[nextPlayer] + testG.discardCount[nextPlayer] + testG.handCount[nextPlayer])
      == (G.deckCount[nextPlayer] + G.discardCount[nextPlayer] + G.handCount[nextPlayer])) {
    printf("Smithy card: PASS: no state change occured for other players.\n");
  }
  else {
    printf("Smithy card: FAIL: no state change occured for other players.\n");
  }
  
  
  //Test 4: No state change should occur to the victory card piles and kingdom card piles.
  
  int prevSupplyCount = 0;
  int curSupplyCount = 0;
  
  for (i = 0; i < 17; i++) {
    prevSupplyCount += G.supplyCount[i];
    curSupplyCount += testG.supplyCount[i];
  }
  
  if (prevSupplyCount == curSupplyCount) {
    printf("Smithy card: PASS: No state change should occur to the victory card piles and kingdom card piles.\n");
  }
  else {
    printf("Smithy card: FAIL: No state change should occur to the victory card piles and kingdom card piles.\n");
  }
  
  return 0;
}
