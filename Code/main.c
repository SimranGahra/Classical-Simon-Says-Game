#include "main.h"

#define MAX_ROUNDS 10
int led_sequence[MAX_ROUNDS] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1};

int main() {
    setup();

    while (1) {
        cyclone_led();
				
			
        for (int round = 0; round < MAX_ROUNDS; round++) {
            if (!play_round(round)) {
                break;
            }
            if (round == MAX_ROUNDS - 1) {
                game_won();
            }
        }
    }
}
