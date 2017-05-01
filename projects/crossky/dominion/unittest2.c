//
//  unittest2.c
//  Assignment-3
//
//  Testing gainCard();
//
//  Created by Kyle Cross on 4/26/17.



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
  int seed = 2;
  int numPlayer = 2;
  int p, handCount, deckCount, discardCount;
  int k[10] = {adventurer, council_room, feast, gardens, mine
    , remodel, smithy, village, baron, great_hall};
  struct gameState G;
  int maxHandCount = 5;
  int maxDeckCount = 10;
  int maxDiscardCount = 10;
  
  
  printf ("TESTING gainCard():\n");
  
  for (p = 1; p < numPlayer; p++) {
    for (handCount = 0; handCount <= maxHandCount; handCount++) {
      for (deckCount = 0; deckCount <= maxDeckCount; deckCount+=5) {
        for (discardCount = 0; discardCount <= maxDiscardCount; discardCount+=5) {
          
          initializeGame(numPlayer, k, seed, &G);
          G.handCount[p] = handCount;
          G.deckCount[p] = deckCount;
          G.discardCount[p] = discardCount;
          
          
          
          if (gainCard(100, &G, 2, p) < 0) {
            printf("gainCard(): PASS check to make sure supply count is empty\n");
          }
          else {
            printf("gainCard(): FAIL check to make sure supply count is empty\n");
          }
          
          if (gainCard(adventurer, &G, 0, p) == 0) {
            printf("gainCard(): PASS check to make sure supply count is accurate\n");
          }
          else {
            printf("gainCard(): FAIL check to make sure supply count is accurate\n");
          }
          
          int copperSupplyCount = G.supplyCount[copper];
          
          gainCard(copper, &G, 1, p);
          if (G.deckCount[p] == (deckCount+1) && G.deck[p][deckCount] == copper) {
            printf("gainCard(): PASS: deckCount incremented correctly and card is added to deck\n");
          }
          else {
            printf("gainCard(): FAIL: deckCount incremented correctly and card is added to deck\n");
          }
          
          gainCard(adventurer, &G, 0, p);
          if (G.discardCount[p] == (discardCount+2) && G.discard[p][discardCount+1] == adventurer) {
            printf("gainCard(): PASS: discardCount incremented correctly and card is added to deck\n");
          }
          else {
            printf("gainCard(): FAIL: discardCount incremented correctly and card is added to deck\n");
          }
          
          gainCard(silver, &G, 2, p);
          if (G.handCount[p] == (handCount+1) && G.hand[p][handCount] == silver) {
            printf("gainCard(): PASS: deckCount incremented correctly and card is added to deck\n");
          }
          else {
            printf("gainCard(): FAIL: deckCount incremented correctly and card is added to deck\n");
          }
          
          if (G.supplyCount[copper] == (copperSupplyCount - 1)) {
            printf("gainCard(): PASS: card supplyCount decremented\n");
          }
          else {
            printf("gainCard(): FAIL: card supplyCount decremented\n");
          }
        }
      }
    }
  }
  
  
  
  
  
  
  return 0;
}

