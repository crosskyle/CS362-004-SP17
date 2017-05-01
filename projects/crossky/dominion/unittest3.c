//
//  unittest3.c
//  Assignment-3
//
//  Testing isGameOver()
//
//  Created by Kyle Cross on 4/27/17.
//
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
  int k[10] = {adventurer, council_room, feast, gardens, mine
    , remodel, smithy, village, baron, great_hall};
  struct gameState G;
  
  
  printf ("TESTING isGameOver():\n");
  
  initializeGame(numPlayer, k, seed, &G);
  
  if (!isGameOver(&G)) {
    printf("isGameOver(): PASS: game is not over with no changes to initialized game\n");
  }
  else {
    printf("isGameOver(): FAIL: game is not over with no changes to initialized game\n");
  }
  
  G.supplyCount[0] = 0;
  
  if (!isGameOver(&G)) {
    printf("isGameOver(): PASS: game is not over with one supply pile drained\n");
  }
  else {
    printf("isGameOver(): FAIL: game is not over with one supply pile drained\n");
  }

  G.supplyCount[12] = 0;
  
  if (!isGameOver(&G)) {
    printf("isGameOver(): PASS: game is not over with two supply piles drained\n");
  }
  else {
    printf("isGameOver(): FAIL: game is not over with two supply piles drained\n");
  }
  
  G.supplyCount[8] = 0;
  
  if (isGameOver(&G)) {
    printf("isGameOver(): PASS: game is over with three supply piles drained\n");
  }
  else {
    printf("isGameOver(): FAIL: game is over with three supply piles drained\n");
  }
  
  initializeGame(numPlayer, k, seed, &G);
  
  G.supplyCount[12] = 0;
  G.supplyCount[13] = 0;
  G.supplyCount[20] = -1;
  
  if (isGameOver(&G)) {
    printf("isGameOver(): PASS: game is over with three supply piles drained including a supply set to a negative value\n");
  }
  else {
    printf("isGameOver(): FAIL: game is over with three supply piles drained including a supply set to a negative value\n");
  }
  
  G.supplyCount[26] = 0;
  
  if (isGameOver(&G)) {
    printf("isGameOver(): PASS: game is over with three supply piles drained including last index of supplyCount\n");
  }
  else {
    printf("isGameOver(): FAIL:  game is over with three supply piles drained including last index of supplyCount\n");
  }
  
  initializeGame(numPlayer, k, seed, &G);
  
  G.supplyCount[province] = 0;
  
  if (isGameOver(&G)) {
    printf("isGameOver(): PASS: game is over with province drained\n");
  }
  else {
    printf("isGameOver(): FAIL: game is over with province drained\n");
  }
  
  return 0;
}

