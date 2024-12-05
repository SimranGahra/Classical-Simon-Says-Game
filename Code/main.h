#ifndef MAIN_H
#define MAIN_H

#include <stm32f10x.h>
#include <stdlib.h>

// Constants
extern const int MAX_ROUNDS;
extern const int NUMBER_OF_LEDS;

// Function declarations
int ranto4();
void genranseq();
void setup(void);
int btn_pressed(void);
int get_button(void);
void failure(int lastround);
void cyclone_led(void);
void game_won(void);
void play_seq(int round);
int play_round(int round);

#endif
