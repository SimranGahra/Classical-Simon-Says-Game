#include "main.h"

// External led_sequence array
extern int led_sequence[];

void setup() {
    // State of the button (1 if unpressed, 0 if pressed).
    
    // Enable clocks for GPIOA and GPIOB
    RCC->APB2ENR |= (1u << 2) | (1u << 3) | (1u << 4);  // Enable GPIOA and GPIOB clocks

    // Configure PA0, PA1, PA4 as outputs (50 MHz, General-purpose output push-pull)
    GPIOA->CRL = 0x00030033; // Configure PA0, PA1, PA4 for output

    // Configure PB0 as output (50 MHz, General-purpose output push-pull)
    // Configure PB4 and PB6 as inputs with pull-up/pull-down
    GPIOB->CRL = 0x04040003; // Configure PB0 as output, PB4 and PB6 as input

    // Configure PB8 and PB9 as inputs with pull-up/pull-down
    GPIOB->CRH = 0x00000044; // Configure PB8 and PB9 as input
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
    return -1;  // No button
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
    // Cylon Eye Scanner sequence
    while (1) {
        GPIOA->ODR = (1 << 0);  // LED1 on
        for (int i = 0; i < 75000; i++) {
            if (btn_pressed()) return;  
        }
        GPIOA->ODR = 0;

        GPIOA->ODR = (1 << 1);  // LED2 on
        for (int i = 0; i < 150000; i++) {
            if (btn_pressed()) return;  
        }
        GPIOA->ODR = 0;

        GPIOA->ODR = (1 << 4);  // LED3 on
        for (int i = 0; i < 150000; i++) {
            if (btn_pressed()) return;  
        }
        GPIOA->ODR = 0;

        GPIOB->ODR = (1 << 0);  // LED4 on
        for (int i = 0; i < 150000; i++) {
            if (btn_pressed()) return;  
        }
        GPIOB->ODR = 0;

        GPIOA->ODR = (1 << 4);  // LED3 on
        for (int i = 0; i < 150000; i++) {
            if (btn_pressed()) return;  
        }
        GPIOA->ODR = 0;

        GPIOA->ODR = (1 << 1);  // LED2 on
        for (int i = 0; i < 150000; i++) {
            if (btn_pressed()) return;  
        }
        GPIOA->ODR = 0;

        GPIOA->ODR = (1 << 0);  // LED1 on
        for (int i = 0; i < 75000; i++) {
            if (btn_pressed()) return;  
        }
        GPIOA->ODR = 0;
    }
		
    GPIOA->ODR = 0;  // Turn off all LEDs
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
    // Play the LED sequence for the current round
    for (int i = 0; i <= round; i++) {
        int led = led_sequence[i];
        switch (led) {
            case 0: GPIOA->ODR = (1 << 0); break; // LED1
            case 1: GPIOA->ODR = (1 << 1); break; // LED2
            case 2: GPIOA->ODR = (1 << 4); break; // LED3
            case 3: GPIOB->ODR = (1 << 0); break; // LED4
        }
        for (int delay = 0; delay < 750000; delay++);
        GPIOA->ODR = 0;
        GPIOB->ODR = 0;
        for (int delay = 0; delay < 250000; delay++);
    }
}

int play_round(int round) {
    play_seq(round);

    for (int i = 0; i <= round; i++) {
        int expected_button = led_sequence[i];
        int timeout = 9000; 
        int button_pressed = -1;

        while (timeout-- > 0) {
            button_pressed = get_button();
            if (button_pressed >= 0) break;
            for (int delay = 0; delay < 1000; delay++);
        }

        if (button_pressed != expected_button) {
            failure(round); // Pass the last completed round
            return 0;
        }

        while (get_button() == button_pressed) {
            for (int delay = 0; delay < 50000; delay++);
        }
    }

    return 1;
}
