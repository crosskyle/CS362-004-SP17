//  testing sea_hag card
//
//  cardtest3.c
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
  int bonus = 0;
  int i;
  int flag = 0;
  struct gameState G, testG;
  int k[10] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  
  printf("\nTesting Sea Hag card\n");
  
  
  
  //Test 1: current player's deck, hand, and discard piles are unchanged
  
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(sea_hag, 0, 0, 0, &testG, 0, &bonus);
  
  flag = 0;
  
  if ((testG.deckCount[p1] + testG.handCount[p1] + testG.discardCount[p1])
      == (G.deckCount[p1] + G.handCount[p1] + G.discardCount[p1])) {
    
    for (i = 0; i < G.handCount[p1]; i++) {
      if (G.hand[p1][i] != testG.hand[p1][i]) {
        flag = 1;
      }
    }
    for (i = 0; i < G.deckCount[p1]; i++) {
      if (G.deck[p1][i] != testG.deck[p1][i]) {
        flag = 1;
      }
    }
    for (i = 0; i < G.discardCount[p1]; i++) {
      if (G.discard[p1][i] != testG.discard[p1][i]) {
        flag = 1;
      }
    }
    if (flag != 1) {
      printf("Sea Hag card: PASS: current player's deck, hand, and discard piles are unchanged\n");
    }
    else {
      printf("Sea Hag card: FAIL: current player's deck, hand, and discard piles have same count but different cards\n");
    }
  }
  else {
    printf("Sea Hag card: FAIL: current player's deck, hand, and discard piles have wrong count\n");
  }
  
  
  //Test 2: Each other player has one more card in discard pile
  
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(sea_hag, 0, 0, 0, &testG, 0, &bonus);
  flag = 0;
  
  for (i = 1; i < numPlayers; i++) {
    if (G.discardCount[i] != testG.discardCount[i] - 1) {
      flag = 1;
    }
  }
  
  if (flag == 0) {
    printf("Sea Hag card: PASS: Each other player has one more card in discard pile\n");
  }
  else {
    printf("Sea Hag card: FAIL: Each other player has one more card in discard pile\n");
  }
  
  //Test 3: Each other player has the same number of cards in deck pile before and after sea hag is played
  
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(sea_hag, 0, 0, 0, &testG, 0, &bonus);
  flag = 0;
  
  for (i = 1; i < numPlayers; i++) {
    if (testG.deckCount[i] != G.deckCount[i]) {
      flag = 1;
    }
  }
  
  if (flag == 0) {
    printf("Sea Hag card: PASS: Each other player has the same number of cards in deck pile before and after sea hag is played\n");
  }
  else {
    printf("Sea Hag card: FAIL: Each other player has the same number of cards in deck pile before and after sea hag is played\n");
  }
  
  
  //Test 4: Each other player gains a curse card on top of deck
  
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(sea_hag, 0, 0, 0, &testG, 0, &bonus);
  flag = 0;
  
  for (i = 1; i < numPlayers; i++) {
    if (testG.deck[i][testG.deckCount[i]-1] != curse) {
      flag = 1;
    }
  }
  
  if (flag == 0) {
    printf("Sea Hag card: PASS: Each other player has curse added to top of their deck\n");
  }
  else {
    printf("Sea Hag card: FAIL: Each other player has curse added to top of their deck\n");
  }

  
  //Test 5: Supply piles besides curse card stay the same
  
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(sea_hag, 0, 0, 0, &testG, 0, &bonus);
  flag = 0;
  
  
  int prevSupplyCount = 0;
  int curSupplyCount = 0;
  
  for (i = 1; i < 17; i++) {
    prevSupplyCount += G.supplyCount[i];
    curSupplyCount += testG.supplyCount[i];
  }
  
  if (prevSupplyCount == curSupplyCount) {
    printf("Sea Hag card: PASS: No state change should occur to the victory card piles and kingdom card piles.\n");
  }
  else {
    printf("Se Hag card: FAIL: No state change should occur to the victory card piles and kingdom card piles.\n");
  }

  
  //Test 6: curse card supply pile should have a count of cards equal to previous count minus number of players besides the current player.
  
  if (G.supplyCount[curse] == (testG.supplyCount[curse] + numPlayers-1)) {
    printf("Sea Hag card: PASS: correct curse card supply count\n");
  }
  else {
    printf("Sea Hag card: PASS: correct curse card supply count\n");
  }
  
  
  
  
  return 0;
}
