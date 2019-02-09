/*
 * comparePlayerState.c
 *
 */
 #ifndef _COMPARE_STATE_HELPER_H
 #define _COMPARE_STATE_HELPER_H

void printFail();
void printSuccess();
void checkGameStateEqual(struct gameState* g, struct gameState* g2, int * f);
int checkCardPiles(int card, struct gameState* g, struct gameState* g2);
int comparePlayerState(int player, struct gameState* g, struct gameState* g2);
void assertEqual(int val1, int val2, int * errors);
void assertNotEqual(int val1, int val2, int * errors);

#endif
