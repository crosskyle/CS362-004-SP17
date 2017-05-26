//  Testing Adventurer
//  randomtestcard2.c
//  Assignment-4
//
//  Created by Kyle Cross on 5/11/17.
//
//

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>


int checkPlayAdventurer(struct gameState *post, int p) {
  int i;
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  
  //printf ("playAdventurerCard PRE: p %d HC %d DeC %d DiC %d \n", p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
  
  int handpos = 0;
  int tempHand[MAX_HAND];
  
  playAdventurer(post, p, handpos, tempHand);
  
  //printf ("playSmithyCard POST: p %d HC %d DeC %d DiC %d HP %d\n", p, post->handCount[p], post->deckCount[p], post->discardCount[p], handPos);
  
  
  //Test 1: reveal cards from correct player's deck
  
  
  if ((post->deckCount[p]) < (pre.deckCount[p])) {
   // printf("Adventurer card: PASS: cards revealed from this player's deck.\n");
  }
  else {
    printf("Adventurer card: FAIL: cards revealed from this player's deck.\n");
  }
  
  //Test 2: hand gains two treasure cards if they are in deck
  
  
  if (post->hand[p][post->handCount[p]-1] >= copper
      && post->hand[p][post->handCount[p]-1] <= gold) {
    if (post->hand[p][post->handCount[p]-2] >= copper
        && post->hand[p][post->handCount[p]-2] <= gold) {
      //printf("Adventurer card: PASS: two treasure cards added to hand\n");
    }
    else {
      printf("Adventurer card: FAIL: only one treasure card added to hand, two expected\n");
    }
  }
  else {
    printf("Adventurer card: FAIL: no treasure cards added to hand, two expected\n");
  }

  //Test 3: all other revealed cards are discarded
  
  memcpy(post, &pre, sizeof(struct gameState));
  
  post->deck[p][post->deckCount[p]-1] = 20;
  post->deck[p][post->deckCount[p]-2] = 20;
  post->deck[p][post->deckCount[p]-3] = gold;
  post->deck[p][post->deckCount[p]-4] = gold;
  
  playAdventurer(post, p, handpos, tempHand);
  
  if (post->discard[p][post->discardCount[p]-1] == 20
      && post->discard[p][post->discardCount[p]-2] == 20) {
    //printf("Adventurer card: PASS: revealed cards that aren't treasure cards were discarded\n");
  }
  else {
    printf("Adventurer card: FAIL: revealed cards that aren't treasure cards were discarded\n");
  }

  
  //Test 4: no state change to other player's decks
  
  
  if ((post->deckCount[p+1] + post->discardCount[p+1] + post->handCount[p+1])
      == (pre.deckCount[p+1] + pre.discardCount[p+1] + pre.handCount[p+1])) {
    //printf("Adventurer card: PASS: no state change occured for other players.\n");
  }
  else {
    printf("Adventurer card: FAIL: no state change occured for other players.\n");
  }

  //Test 5: no state change to supply piles
  
  int prevSupplyCount = 0;
  int curSupplyCount = 0;
  
  for (i = 0; i < 27; i++) {
    prevSupplyCount += pre.supplyCount[i];
    curSupplyCount += post->supplyCount[i];
  }
  
  if (prevSupplyCount == curSupplyCount) {
    //printf("Adventurer card: PASS: No state change should occur to the victory card piles and kingdom card piles.\n");
  }
  else {
    printf("Adventurer card: FAIL: No state change should occur to the victory card piles and kingdom card piles.\n");
  }
  
  printf("Adventurer card: Test 6 not ran. Produces segfault\n");
  //Test 6: hand count should not change if deck and discard piles are empty
  // PRODUCED SEGFAULT
  /*
  memcpy(post, &pre, sizeof(struct gameState));
  
  post->discardCount[p] = 0;
  post->deckCount[p] = 0;
  
  playAdventurer(post, p, handpos, tempHand);
  
  if (post->handCount[p] == pre.handCount[p]) {
    //printf("Adventurer card: PASS no treasure added to hand if deck and discard are empty");
  }
  else {
    printf("Adventurer card: FAIL no treasure added to hand if deck and discard are empty");
  }

  */
  
  //Test 7: Checks that copper is added to hand
  
  memcpy (post, &pre, sizeof(struct gameState));
  
  post->deckCount[p] = 4;
  post->deck[p][0] = gold;
  post->deck[p][1] = gold;
  post->deck[p][2] = copper;
  post->deck[p][3] = copper;
  playAdventurer(post, p, handpos, tempHand);
  
  if (post->hand[p][post->handCount[p]-1] == copper) {
    if (post->hand[p][post->handCount[p]-2] >= copper) {
      //printf("Adventurer card: PASS: two copper cards added to hand\n");
    }
    else {
      printf("Adventurer card: FAIL: only one copper card added to hand, two expected\n");
    }
  }
  else {
    printf("Adventurer card: FAIL: no copper cards added to hand, two expected\n");
  }

  
  
  return 0;
}

int main () {
  
  int i, n, p, handPos;
  
  struct gameState G;
  
  printf ("Testing Adventurer Card.\n");
  
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
    
    
    // Testing Smithy card
    G.hand[p][handPos] = adventurer;
    
    // Two treasure cards are added to deck to avoid a segfault
    G.deck[p][0] = gold;
    G.deck[p][1] = gold;
    
    checkPlayAdventurer(&G, p);
  }
  
  return 0;
}


