//
//  unittest1.c
//  Assignment-3
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
  int i;
  int seed = 2;
  int numPlayer = 2;
  int p, r, handCount, deckCount, discardCount;
  int k[10] = {adventurer, council_room, feast, gardens, mine
    , remodel, smithy, village, baron, great_hall};
  struct gameState G;
  int maxHandCount = 5;
  int maxDeckCount = 10;
  int maxDiscardCount = 10;
  
  int estate[MAX_HAND];
  int coppers[MAX_HAND];
  int silvers[MAX_HAND];
  int golds[MAX_HAND];
  int adventurers[MAX_HAND];
  
  for (i = 0; i < MAX_HAND; i++)
  {
    coppers[i] = copper;
    silvers[i] = silver;
    golds[i] = gold;
    adventurers[i] = adventurer;
    
  }
  
  printf ("TESTING fullDeckCount():\n");
  
  
  for (p = 0; p < numPlayer; p++) {
    for (handCount = 0; handCount <= maxHandCount; handCount++) {
      for (deckCount = 0; deckCount <= maxDeckCount; deckCount++) {
        for (discardCount = 0; discardCount <= maxDiscardCount; discardCount++) {
          r = initializeGame(numPlayer, k, seed, &G);
          G.handCount[p] = handCount;
          G.deckCount[p] = deckCount;
          G.discardCount[p] = discardCount;
          memcpy(G.hand[p], coppers, sizeof(int) * handCount);
          memcpy(G.discard[p], golds, sizeof(int) * discardCount);
          memcpy(G.deck[p], silvers, sizeof(int) * deckCount);
          
          printf("Testing for player %d with handCount %d, deckcount %d, and discardcount %d\n",
                 p,handCount,deckCount,discardCount);
        
          //check if deckCount is counted correctly
          if (fullDeckCount(p, silver, &G) == deckCount) {
            printf("fullDeckCount() test: PASS \n");
          }
          else {
            printf("fullDeckCount() test: FAIL \n");
          }
          
          //check if handCount is counted correctly
          if (fullDeckCount(p, copper, &G) == handCount) {
            printf("fullDeckCount() test: PASS \n");
          }
          else {
            printf("fullDeckCount() test: FAIL \n");
          }
          
          //check if discardCount is counted correctly
          if (fullDeckCount(p, gold, &G) == discardCount) {
            printf("fullDeckCount() test: PASS \n");
          }
          else {
            printf("fullDeckCount() test: FAIL \n");
          }
          
          //check if all decks are added correctly
          if ((G.handCount[p] + G.deckCount[p] + G.discardCount[p]) ==
              (handCount + deckCount + discardCount)) {
            printf("fullDeckCount() test: PASS \n");
          }
          else {
            printf("fullDeckCount() test: FAIL \n");
          }

          //check if count is accurate for card that does not exist
          if (fullDeckCount(p, -1, &G) == 0) {
            printf("fullDeckCount() test: PASS \n");
          }
          else {
            printf("fullDeckCount() test: FAIL \n");
          }
          
          //check if count is accurate for card that exists but is not in deck
          if (fullDeckCount(p, adventurer, &G) == 0) {
            printf("fullDeckCount() test: PASS \n");
          }
          else {
            printf("fullDeckCount() test: FAIL \n");
          }
          
          //check to make sure that different player does not have a count
          if (fullDeckCount(p+1, gold, &G) == 0) {
            printf("fullDeckCount() test: PASS \n");
          }
          else {
            printf("fullDeckCount() test: FAIL \n");
          }
        
          
          memcpy(G.hand[p], coppers, sizeof(int) * handCount);
          memcpy(G.discard[p], coppers, sizeof(int) * discardCount);
          memcpy(G.deck[p], coppers, sizeof(int) * deckCount);
          
          //checks if one card makes up every card in deck
          if (fullDeckCount(p, copper, &G) == (handCount+discardCount+deckCount)) {
            printf("fullDeckCount() test: PASS \n");
          }
          else {
            printf("fullDeckCount() test: FAIL \n");
          }
        }
      }
    }
  }
  
  return 0;
}
