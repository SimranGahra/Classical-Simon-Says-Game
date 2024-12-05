#include "main.h"

// Global array to hold the randomized LED sequence
int led_sequence[10];  // Use MAX_ROUNDS value from main.h

int ranto4() {
    int limit = RAND_MAX - (RAND_MAX % NUMBER_OF_LEDS);
    int r;
    while ((r = rand()) >= limit);
    return r % NUMBER_OF_LEDS;
}

void genranseq() {
    for (int i = 0; i < MAX_ROUNDS; i++) {
        led_sequence[i] = ranto4();
    }
}

void setup() {
    // Enable clocks for GPIOA and GPIOB
    RCC->APB2ENR |= (1u << 2) | (1u << 3) | (1u << 4);

    // Configure PA0, PA1, PA4 as outputs (50 MHz, General-purpose output push-pull)
    GPIOA->CRL = 0x00030033;

    // Configure PB0 as output, PB4 and PB6 as inputs with pull-up/pull-down
    GPIOB->CRL = 0x04040003;

    // Configure PB8 and PB9 as inputs with pull-up/pull-down
    GPIOB->CRH = 0x00000044;
}

int btn_pressed() {
    return (!(GPIOB->IDR & (1 << 4))) || (!(GPIOB->IDR & (1 << 6))) ||
           (!(GPIOB->IDR & (1 << 8))) || (!(GPIOB->IDR & (1 << 9)));
}

int get_button() {
    if (!(GPIOB->IDR & (1 << 4))) return 0;  // Button PB4
    if (!(GPIOB->IDR & (1 << 6))) return 1;  // Button PB6
    if (!(GPIOB->IDR & (1 << 8))) return 2;  // Button PB8
    if (!(GPIOB->IDR & (1 << 9))) return 3;  // Button PB9
    return -1;  // No button pressed
}

void failure(int lastround) {
    // Blink LED1 and LED4 four times to indicate failure
    for (int i = 0; i < 4; i++) {
        GPIOA->ODR = (1 << 0);      // Turn on LED1
        GPIOB->ODR = (1 << 0);      // Turn on LED4
        for (int delay = 0; delay < 750000; delay++);
        GPIOA->ODR = 0;             // Turn off LED1
        GPIOB->ODR = 0;             // Turn off LED4
        for (int delay = 0; delay < 750000; delay++);
    }

    // Indicate the last completed round using binary on LEDs
    // LED1 -> Bit 0, LED2 -> Bit 1, LED3 -> Bit 2, LED4 -> Bit 3
    GPIOA->ODR = 0; // Clear all GPIOA outputs
    GPIOB->ODR = 0; // Clear all GPIOB outputs

    if (lastround & 1) GPIOA->ODR |= (1 << 0); // LED1 (Bit 0)
    if (lastround & 2) GPIOA->ODR |= (1 << 1); // LED2 (Bit 1)
    if (lastround & 4) GPIOA->ODR |= (1 << 4); // LED3 (Bit 2)
    if (lastround & 8) GPIOB->ODR |= (1 << 0); // LED4 (Bit 3)

    // Wait for user input to restart
    while (!btn_pressed()) {
        // Wait until a button is pressed
    }

    // Debounce delay
    while (btn_pressed()) {
        for (int i = 0; i < 50000; i++);
    }

    // Turn off all LEDs and reset for the next game
    GPIOA->ODR = 0;
    GPIOB->ODR = 0;
}


void cyclone_led() {
    while (1) {
        GPIOA->ODR = (1 << 0);
        for (int i = 0; i < 75000; i++) {
            if (btn_pressed()) {
                GPIOA->ODR = 0;
                GPIOB->ODR = 0;
                for (int delay = 0; delay < 1000000; delay++);
                return;
            }
        }
        GPIOA->ODR = 0;

        GPIOA->ODR = (1 << 1);
        for (int i = 0; i < 150000; i++) {
            if (btn_pressed()) {
                GPIOA->ODR = 0;
                GPIOB->ODR = 0;
                for (int delay = 0; delay < 1000000; delay++);
                return;
            }
        }
        GPIOA->ODR = 0;

        GPIOA->ODR = (1 << 4);
        for (int i = 0; i < 150000; i++) {
            if (btn_pressed()) {
                GPIOA->ODR = 0;
                GPIOB->ODR = 0;
                for (int delay = 0; delay < 1000000; delay++);
                return;
            }
        }
        GPIOA->ODR = 0;

        GPIOB->ODR = (1 << 0);
        for (int i = 0; i < 150000; i++) {
            if (btn_pressed()) {
                GPIOA->ODR = 0;
                GPIOB->ODR = 0;
                for (int delay = 0; delay < 1000000; delay++);
                return;
            }
        }
        GPIOB->ODR = 0;

        GPIOA->ODR = (1 << 4);
        for (int i = 0; i < 150000; i++) {
            if (btn_pressed()) {
                GPIOA->ODR = 0;
                GPIOB->ODR = 0;
                for (int delay = 0; delay < 1000000; delay++);
                return;
            }
        }
        GPIOA->ODR = 0;

        GPIOA->ODR = (1 << 1);
        for (int i = 0; i < 150000; i++) {
            if (btn_pressed()) {
                GPIOA->ODR = 0;
                GPIOB->ODR = 0;
                for (int delay = 0; delay < 1000000; delay++);
                return;
            }
        }
        GPIOA->ODR = 0;

        GPIOA->ODR = (1 << 0);
        for (int i = 0; i < 75000; i++) {
            if (btn_pressed()) {
                GPIOA->ODR = 0;
                GPIOB->ODR = 0;
                for (int delay = 0; delay < 1000000; delay++);
                return;
            }
        }
        GPIOA->ODR = 0;
    }
    GPIOA->ODR = 0;
    GPIOB->ODR = 0;
}

void game_won() {
    // Blink all LEDs 4 times
    for (int i = 0; i < 4; i++) {
        GPIOA->ODR = (1 << 0) | (1 << 1) | (1 << 4);  // Turn on LED1, LED2, LED3
        GPIOB->ODR = (1 << 0);  // Turn on LED4
        for (int delay = 0; delay < 750000; delay++);
        GPIOA->ODR = 0;
        GPIOB->ODR = 0;
        for (int delay = 0; delay < 750000; delay++);
    }

    // Indicate the maximum level completed (10 -> 1010)
    GPIOA->ODR = (1 << 1);       // Turn on LED2
    GPIOB->ODR = (1 << 0);       // Turn on LED4

    // Wait for restart
    while (!btn_pressed()) {}

    // Debounce delay
    while (btn_pressed()) {
        for (int i = 0; i < 50000; i++);
    }

    // Reset all LEDs
    GPIOA->ODR = 0;
    GPIOB->ODR = 0;
}

void play_seq(int round) {
    // Loop through the LED sequence up to the current round
    for (int i = 0; i <= round; i++) {
        int led = led_sequence[i]; // Get the LED number for the current step
        switch (led) {
            case 0:
                GPIOA->ODR = (1 << 0); // Turn on LED1
                break;
            case 1:
                GPIOA->ODR = (1 << 1); // Turn on LED2
                break;
            case 2:
                GPIOA->ODR = (1 << 4); // Turn on LED3
                break;
            case 3:
                GPIOB->ODR = (1 << 0); // Turn on LED4
                break;
        }
        for (int delay = 0; delay < 900000; delay++); // Delay for LED visibility

        // Turn off all LEDs after the delay
        GPIOA->ODR = 0;
        GPIOB->ODR = 0;

        for (int delay = 0; delay < 500000; delay++); // Delay before the next LED
    }
}




int play_round(int round) {
    play_seq(round);

    for (int i = 0; i <= round; i++) {
        int expected_button = led_sequence[i];
        int timeout = 1700; 
        int button_pressed = -1;

        while (timeout-- > 0) {
            button_pressed = get_button();
            if (button_pressed >= 0) {
                // Provide feedback: light up corresponding LED
                switch (button_pressed) {
                    case 0: GPIOA->ODR = (1 << 0); break; // LED1 for Button PB4
                    case 1: GPIOA->ODR = (1 << 1); break; // LED2 for Button PB6
                    case 2: GPIOA->ODR = (1 << 4); break; // LED3 for Button PB8
                    case 3: GPIOB->ODR = (1 << 0); break; // LED4 for Button PB9
                }

                // Check if button matches the expected input
                if (button_pressed != expected_button) {
                    failure(round); // Indicate failure
                    return 0;
                }

                while (get_button() == button_pressed);

                // Turn off all LEDs 
                GPIOA->ODR = 0;
                GPIOB->ODR = 0;

                // delay before next input
                for (int delay = 0; delay < 500000; delay++);

                break;
            }

            for (int delay = 0; delay < 10000; delay++);
        }

        if (button_pressed == -1) {
            failure(round); 
            return 0;
        }
    }

    for (int delay = 0; delay < 1000000; delay++);

    return 1;
}

