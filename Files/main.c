#include "main.h"

// Constants
const int MAX_ROUNDS = 10;
const int NUMBER_OF_LEDS = 4;
int seed = 0;

int main() {
    setup();

    while (1) {
        cyclone_led();
        srand(seed);  // Seed the random number generator
        genranseq();  // Create a random sequence for the game

        for (int round = 0; round < MAX_ROUNDS; round++) {
            if (!play_round(round)) {
                break;
            }
						
						seed++;
						
            if (round == MAX_ROUNDS - 1) {
                game_won();
            }
        }
    }
}
