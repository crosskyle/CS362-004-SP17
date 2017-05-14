//  Testing Village Card
//  randomtestcard3.c
//  Assignment-4
//
//  Created by Kyle Cross on 5/11/17.
//  Copyright © 2017 Kyle Cross. All rights reserved.
//

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>


int checkPlayVillage(struct gameState *post, int handPos, int p) {
  int i;
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  
  printf ("playVillageCard PRE: p %d HC %d DeC %d DiC %d HP %d\n", p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], handPos);
  
  playVillage(post, handPos, p);
  
  printf ("playVillageCard POST: p %d HC %d DeC %d DiC %d HP %d\n", p, post->handCount[p], post->deckCount[p], post->discardCount[p], handPos);
  
  
  //Test 1: Current player should receive exactly 1 card.
  
  if (post->handCount[p] == (pre.handCount[p]) &&
      post->playedCardCount == (pre.playedCardCount + 1)) {
    printf("Village card: PASS: one card added to hand\n");
  }
  else {
    printf("Village card: FAIL: one card added to hand\n");
  }
  
  //Test 2: 1 card should come from his own pile.
  
  if ((post->deckCount[p] + post->discardCount[p])
      < (pre.deckCount[p] + pre.discardCount[p])) {
    printf("Village card: PASS: card came from correct player's pile\n");
  }
  else {
    printf("Village card: FAIL: card came from correct player's pile\n");
  }
  
  //Test 3: No state change should occur for other players.
  
  if ((post->deckCount[p+1] + post->discardCount[p+1] + post->handCount[p+1])
      == (pre.deckCount[p+1] + pre.discardCount[p+1] + pre.handCount[p+1])) {
    printf("Village card: PASS: no state change occured for other players.\n");
  }
  else {
    printf("Village card: FAIL: no state change occured for other players.\n");
  }
  
  //Test 4: No state change should occur to the victory card piles and kingdom card piles.
  
  int prevSupplyCount = 0;
  int curSupplyCount = 0;
  
  for (i = 0; i < 25; i++) {
    prevSupplyCount += pre.supplyCount[i];
    curSupplyCount += post->supplyCount[i];
  }
  
  if (prevSupplyCount == curSupplyCount) {
    printf("Village card: PASS: No state change should occur to the victory card piles and kingdom card piles.\n");
  }
  else {
    printf("Village card: FAIL: No state change should occur to the victory card piles and kingdom card piles.\n");
  }
  
  //Test 5: current player should have two more actions available
  
  if (post->numActions == pre.numActions + 2) {
    printf("Village card: PASS: current player should have two more actions available.\n");
  }
  else {
    printf("Village card: FAIL: current player should have two more actions available.\n");
  }
  
  
  return 0;
}

int main () {
  
  int i, n, p, handPos;
  
  struct gameState G;
  
  printf ("Testing Village Card.\n");
  
  printf ("RANDOM TESTS.\n");
  
  SelectStream(2);
  PutSeed(3);
  
  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * (MAX_DECK - 2)) + 2;
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * (MAX_HAND - 1)) + 1;
    G.playedCardCount = floor(Random() * G.handCount[p]);
    handPos = floor(Random() * G.handCount[p]);
    
    for (i = 0; i < G.deckCount[p]; i++) {
      G.deck[p][i] = floor(Random() * 27);
    }
    
    for (i = 0; i < G.discardCount[p]; i++) {
      G.discard[p][i] = floor(Random() * 27);
    }
    
    for (i = 0; i < G.handCount[p]; i++) {
      G.hand[p][i] = floor(Random() * 27);
    }
    
    
    // Testing Village card
    G.hand[p][handPos] = village;
    
    
    checkPlayVillage(&G, handPos, p);
  }
  
  return 0;
}

