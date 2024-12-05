#ifndef MAIN_H
#define MAIN_H

#include <stm32f10x.h>

// Function declarations
void setup(void);
int btn_pressed(void);
int get_button(void);
void failure(int lastround);
void cyclone_led(void);
void game_won(void);
void play_seq(int round);
int play_round(int round);

#endif // MAIN_H
