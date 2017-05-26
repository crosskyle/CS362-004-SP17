//
//  unittest4.c
//  Assignment-3
//
//  Created by Kyle Cross on 4/27/17.
//  Testing drawCard()
//

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
  int maxHandCount = 5;
  int maxDeckCount = 10;
  int maxDiscardCount = 15;
  int handCount, deckCount, discardCount;
  int p, i;
  int k[10] = {adventurer, council_room, feast, gardens, mine
    , remodel, smithy, village, baron, great_hall};
  struct gameState G;
  int coppers[MAX_DECK], remodels[MAX_DECK],provinces[MAX_HAND];
  for (i = 0; i < MAX_DECK; i++) {
    coppers[i] = copper;
    remodels[i] = remodel;
  }
  for (i = 0; i < MAX_HAND; i++) {
    provinces[i] = province;
  }
  
  printf ("TESTING drawCard():\n");
  
  initializeGame(numPlayer, k, seed, &G);
  
  for (p = 0; p < numPlayer; p++) {
    for (handCount = 0; handCount < maxHandCount; handCount++) {
      for (deckCount = 0; deckCount < maxDeckCount; deckCount+=3) {
        for (discardCount = 1; discardCount < maxDiscardCount; discardCount += 5) {
          
          initializeGame(numPlayer, k, seed, &G);
          
          G.deckCount[p] = deckCount;
          G.handCount[p] = handCount;
          G.discardCount[p] = discardCount;
          
          
          memcpy(G.discard[p], remodels, sizeof(int) * discardCount);
          memcpy(G.deck[p], coppers, sizeof(int) * deckCount);
          memcpy(G.hand[p], provinces, sizeof(int) * handCount);
          
          drawCard(p, &G);
          
          if (deckCount == 0) {
            if (G.hand[p][G.handCount[p]-1] == remodel) {
              printf("PASS: Testing draw copper: Player %d drew card %d, with handCount %d, deckCount %d, and discardCount %d\n",
                     p, G.hand[p][G.handCount[p]-1], handCount, deckCount, discardCount);
            }
            else {
              printf("FAIL: Testing draw copper: Player %d drew card %d, with handCount %d, deckCount %d, and discardCount %d\n",
                     p, G.hand[p][G.handCount[p]-1], handCount, deckCount, discardCount);
            }
          }
          else {
            if (G.hand[p][G.handCount[p]-1] == copper) {
              printf("PASS: Testing draw copper: Player %d drew card %d, with handCount %d, deckCount %d, and discardCount %d\n",
                     p, G.hand[p][G.handCount[p]-1], handCount, deckCount, discardCount);
            }
            else {
              printf("FAIL: Testing draw copper: Player %d drew card %d, with handCount %d, deckCount %d, and discardCount %d\n",
                     p, G.hand[p][G.handCount[p]-1], handCount, deckCount, discardCount);
            }
          }
          
          
          G.deckCount[p] = deckCount;
          G.handCount[p] = handCount;
          G.discardCount[p] = discardCount;
          
          memcpy(G.deck[p], remodels, sizeof(int) * deckCount);
          memcpy(G.discard[p], coppers, sizeof(int) * discardCount);
          memcpy(G.hand[p], provinces, sizeof(int) * handCount);
          
          drawCard(p, &G);
          
          if (deckCount == 0) {
            if (G.hand[p][G.handCount[p]-1] == copper) {
              printf("PASS: Testing draw remodel: Player %d drew card %d, with handCount %d, deckCount %d, and discardCount %d\n",
                     p, G.hand[p][G.handCount[p]-1], handCount, deckCount, discardCount);
            }
            else {
              printf("FAIL: Testing draw remodel: Player %d drew card %d, with handCount %d, deckCount %d, and discardCount %d\n",
                     p, G.hand[p][G.handCount[p]-1], handCount, deckCount, discardCount);
            }
          }
          else {
            if (G.hand[p][G.handCount[p]-1] == remodel) {
              printf("PASS: Testing draw remodel: Player %d drew card %d, with handCount %d, deckCount %d, and discardCount %d\n",
                     p, G.hand[p][G.handCount[p]-1], handCount, deckCount, discardCount);
              
            }
            else {
              printf("FAIL: Player %d drew card %d, with handCount %d, deckCount %d, and discardCount %d\n",
                     p, G.hand[p][G.handCount[p]-1], handCount, deckCount, discardCount);
            }
          }
          
          
          
          
          if (G.deckCount[p] == (deckCount-1) || deckCount == 0) {
            printf("PASS: Testing deck count: Player %d drew card %d, with handCount %d and deckCount %d\n",
                   p, G.hand[p][G.handCount[p]-1], handCount, deckCount);
          }
          else {
            printf("FAIL: Testing deck count: Player %d drew card %d, with handCount %d and deckCount %d\n",
                   p, G.hand[p][G.handCount[p]-1], handCount, deckCount);
          }
          
          
          
          if (G.handCount[p] == (handCount+1)) {
            printf("PASS: Testing hand count: Player %d drew card %d, with handCount %d and deckCount %d\n",
                   p, G.hand[p][G.handCount[p]-1], handCount, deckCount);
          }
          else {
            printf("FAIL: Testing hand count: Player %d drew card %d, with handCount %d and deckCount %d\n",
                   p, G.hand[p][G.handCount[p]-1], handCount, deckCount);
          }
        }
      }
    }
  }

  return 0;
}


