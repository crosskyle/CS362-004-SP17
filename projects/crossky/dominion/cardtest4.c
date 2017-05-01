//
//  Testing Treasure Map card
//
//  Assignment-3
//
//  Created by Kyle Cross on 4/28/17.
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
  int numPlayers = 4;
  int p1 = 0;
  int nextPlayer = 1;
  int bonus = 0;
  int i;
  int flag = 0;
  struct gameState G, testG;
  int k[10] = {7, 8, 9, 10, 11, 12, 13, 14, 15, treasure_map};
  
  printf("\nTesting Treasure Map card\n");
  
  
  
  //Test 1: current player has 2 less cards in hand
  
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));
  
  for (i = 0; i < 2; i++) {
    testG.hand[p1][i] = treasure_map;
  }
  
  cardEffect(treasure_map, 0, 0, 0, &testG, 0, &bonus);
  
  if (testG.handCount[p1] == G.handCount[p1] - 2) {
    printf("Treasure Map card: PASS: current player has 2 less cards in hand\n");
  }
  else {
    printf("Treasure Map card: FAIL: current player has 2 less cards in hand\n");
  }
  
  
  //Test 2: current player has 4 gold cards on top of deck
  
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));
  
  for (i = 0; i < 2; i++) {
    testG.hand[p1][i] = treasure_map;
  }
  
  cardEffect(treasure_map, 0, 0, 0, &testG, 0, &bonus);
  
  for (i = testG.deckCount[p1]-1; i >= testG.deckCount[p1]-4; i--) {
    if (testG.deck[p1][i] != gold) {
      flag = 1;
    }
  }

  if (flag != 1) {
    printf("Treasure Map card: PASS: current player has 4 gold cards on top of deck\n");
  }
  else {
    printf("Treasure Map card: FAIL: current player has 4 gold cards on top of deck\n");
  }
  
  
  //Test 3: current player has 4 more cards on top of deck
  
  if (testG.deckCount[p1] == G.deckCount[p1] + 4) {
    printf("Treasure Map card: PASS: current player has 4 more cards on top of deck\n");
  }
  else {
    printf("Treasure Map card: FAIL: current player has 4 more cards on top of deck\n");
  }

  
  //Test 4: No state change should occur to the victory card piles and kingdom card piles.
  
  int prevSupplyCount = 0;
  int curSupplyCount = 0;
  
  for (i = 0; i < gold; i++) {
    prevSupplyCount += G.supplyCount[i];
    curSupplyCount += testG.supplyCount[i];
  }
  
  for (i = gold+1; i < 16; i++) {
    prevSupplyCount += G.supplyCount[i];
    curSupplyCount += testG.supplyCount[i];
  }
  
  if (prevSupplyCount == curSupplyCount) {
    printf("Treasure Map card: PASS: No state change should occur to the victory card piles and kingdom card piles.\n");
  }
  else {
    printf("Treasure Map card: FAIL: No state change should occur to the victory card piles and kingdom card piles.\n");
  }

  
  //Test 5: No state change should occur for other players.
  
  if ((testG.deckCount[nextPlayer] + testG.discardCount[nextPlayer] + testG.handCount[nextPlayer])
      == (G.deckCount[nextPlayer] + G.discardCount[nextPlayer] + G.handCount[nextPlayer])) {
    printf("Treasure Map : PASS: no state change occured for other players.\n");
  }
  else {
    printf("Treasure Map : FAIL: no state change occured for other players.\n");
  }
  
  return 0;
}
