//  Testing Smithy
//  randomtestcard1.c
//  Assignment-4
//
//  Created by Kyle Cross on 5/10/17.
//
//

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int checkPlaySmithy(struct gameState *post, int handPos, int p) {
  int i;
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  
  printf ("playSmithyCard PRE: p %d HC %d DeC %d DiC %d HP %d\n", p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], handPos);
  
  playSmithy(post, handPos, p);
  
  printf ("playSmithyCard POST: p %d HC %d DeC %d DiC %d HP %d\n", p, post->handCount[p], post->deckCount[p], post->discardCount[p], handPos);
  
  
  //Test 1: Current player should receive exactly 3 cards.
  
  if (post->handCount[p] == (pre.handCount[p] + 2) &&
      post->playedCardCount == (pre.playedCardCount + 1)) {
    printf("Smithy card: PASS: three cards added to hand\n");
  }
  else {
    printf("Smithy card: FAIL: three cards added to hand\n");
  }
  
  //Test 2: 3 cards should come from his own pile.
  
  if ((post->deckCount[p] + post->discardCount[p])
      < (pre.deckCount[p] + pre.discardCount[p])) {
    printf("Smithy card: PASS: cards came from correct player's pile\n");
  }
  else {
    printf("Smithy card: FAIL: cards came from correct player's pile\n");
  }
  
  //Test 3: No state change should occur for other players.
  
  if ((post->deckCount[p+1] + post->discardCount[p+1] + post->handCount[p+1])
      == (pre.deckCount[p+1] + pre.discardCount[p+1] + pre.handCount[p+1])) {
    printf("Smithy card: PASS: no state change occured for other players.\n");
  }
  else {
    printf("Smithy card: FAIL: no state change occured for other players.\n");
  }

  //Test 4: No state change should occur to the victory card piles and kingdom card piles.
  
  int prevSupplyCount = 0;
  int curSupplyCount = 0;
  
  for (i = 0; i < 25; i++) {
    prevSupplyCount += pre.supplyCount[i];
    curSupplyCount += post->supplyCount[i];
  }
  
  if (prevSupplyCount == curSupplyCount) {
    printf("Smithy card: PASS: No state change should occur to the victory card piles and kingdom card piles.\n");
  }
  else {
    printf("Smithy card: FAIL: No state change should occur to the victory card piles and kingdom card piles.\n");
  }

  
  
  
  return 0;
}

int main () {
  
  int i, n, p, handPos;
  
  struct gameState G;
  
  printf ("Testing Smithy Card.\n");
  
  printf ("RANDOM TESTS.\n");
  
  SelectStream(2);
  PutSeed(3);
  
  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * (MAX_HAND - 1));
    G.handCount[p]++;
    G.playedCardCount = floor(Random() * G.handCount[p]);
    handPos = floor(Random() * G.handCount[p]);
    
    // Testing Smithy card
    G.hand[p][handPos] = smithy;
    
    
    checkPlaySmithy(&G, handPos, p);
  }
  
  return 0;
}

