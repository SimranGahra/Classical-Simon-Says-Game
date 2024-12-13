# Classical Simon Says Game

## Project Overview

The **Simon Memory Game** is an interactive project implemented on an **STM32F103RB** microcontroller. It challenges players to memorize and replicate sequences of LED flashes using buttons. As the game progresses, the sequences become longer and more challenging, testing the player’s memory and reflexes. This project showcases the use of GPIO programming, interactive feedback, and real-time delays in embedded systems.

---

## Features

- **Interactive Gameplay**: Players match LED sequences using buttons with immediate feedback on button presses.
- **Dynamic Difficulty**: Sequence length increases with each round.
- **Randomized LED Sequences**:
  - The game generates a random LED sequence at the start of each playthrough, ensuring unpredictability.
- **Feedback Mechanism**:
  - LEDs light up when a button is pressed, confirming user input.
- **Winning and Failure Indications**:
  - **Victory Sequence**: All LEDs flash, followed by a binary display of the winning round.
  - **Failure Sequence**: LEDs indicate the last completed round in binary.
- **Delays for Clarity**:
  - Delays after button presses and between rounds to ensure smooth gameplay and clear transitions.
- **Customizable Hardware**: Easily modify LED/button mappings and sequences.

---

## How to Play

1. **Startup**:
   - The game begins with a "Cylon Eye Scanner" sequence (LEDs cycling back and forth).
   - Press any button to initiate **Round 1**.

2. **Sequence Display**:
   - A random LED sequence is generated for each game and displayed to the player.
   - Memorize the sequence.

3. **Player Input**:
   - Press the corresponding buttons to replicate the LED sequence.
   - Each button corresponds to a specific LED:
     - **Black Button → LED1 (PA0)**
     - **Red Button → LED2 (PA1)**
     - **Green Button → LED3 (PA4)**
     - **Blue Button → LED4 (PB0)**

4. **Feedback During Input**:
   - LEDs light up to indicate the button pressed by the player.
   - Feedback is cleared before the next input step.

5. **Round Progression**:
   - Successfully completing a round adds an additional step to the sequence.
   - A delay between rounds provides clarity that a new sequence will begin.

6. **Game End**:
   - **Winning**: Complete all 10 rounds to trigger the **Victory Sequence**.
   - **Failure**: An incorrect button press or timeout triggers the **Failure Sequence**:
     - LEDs blink to indicate failure, then display the last completed round in binary.

7. **Restart**:
   - Press any button to restart after winning or losing.

---

## Hardware Configuration

### Components

- **STM32F103RB Microcontroller Board**
- **4 LEDs** (with current-limiting resistors)
- **4 Push Buttons** (with pull-up or pull-down resistors)
- Breadboard and jumper wires

### Schematic Diagram

The hardware setup for the Simon Memory Game is detailed in the provided **SimonSchematic.pdf**. This schematic outlines the connections and configurations required to build the circuit, including LED and button wiring.

**[`Click Here to View the Schematic`](./SimonSchematic.pdf)**

### Connections

#### LEDs (Outputs)

| LED  | Microcontroller Pin | GPIO Port | Pin Number |
|------|---------------------|-----------|------------|
| LED1 | PA0                 | GPIOA     | 0          |
| LED2 | PA1                 | GPIOA     | 1          |
| LED3 | PA4                 | GPIOA     | 4          |
| LED4 | PB0                 | GPIOB     | 0          |

#### Buttons (Inputs)

| Button  | Microcontroller Pin | GPIO Port | Pin Number |
|---------|---------------------|-----------|------------|
| Button1 | PB4                 | GPIOB     | 4          |
| Button2 | PB6                 | GPIOB     | 6          |
| Button3 | PB8                 | GPIOB     | 8          |
| Button4 | PB9                 | GPIOB     | 9          |

---

## Configuring Inputs and Outputs

The GPIO ports and pins for the LEDs and buttons must be configured as follows:

- **LEDs**: Configure as output pins to drive the LEDs. Use current-limiting resistors to prevent damage.
- **Buttons**: Configure as input pins with pull-up or pull-down resistors to ensure stable input signals.
- **Clock Configuration**: Ensure the correct clock setup for the GPIO module to manage real-time delays effectively.

---

## Code Details

### Core Files

1. **[`main.c`](./Files/main.c)**:
   - Initializes the system and manages game logic.
   - Implements a cyclic sequence loop and handles player interactions.

2. **[`main.h`](./Files/main.h)**:
   - Contains global declarations and function prototypes.

3. **[`functions.c`](./Files/functions.c)**:
   - Implements core game functionalities:
     - LED sequences.
     - Player input validation.
     - Feedback for button presses.
     - Randomized sequence generation.
     - Winning and failure sequences.

### STM32 Peripheral Header

The project uses the **stm32f10x.h** file included in the STM32 Standard Peripheral Library, which provides all necessary macros and function declarations for configuring the GPIO ports and handling hardware peripherals. Ensure that the **STM32 Standard Peripheral Library** is included in your project folder or IDE environment or use the copy provided in this repository (**[`stm32f10x.h`](./Files/stm32f10x.h)**).

---

## Development Environment

### Prerequisites

- **STM32 Development Tools**:
  - STM32CubeIDE or Keil MDK.
- **STM32 Standard Peripheral Library**.
- Familiarity with C programming and microcontroller development.

### Build and Flash Instructions

1. **Import Project**:
   - Add `main.c`, `main.h`, and `functions.c` to your IDE.
2. **Compile**:
   - Generate the binary file using your preferred IDE.
3. **Flash**:
   - Use a USB programmer or debugger to flash the binary to your STM32 board.
4. **Run**:
   - Power on the board and start the game.

---

## Enhancements

- **Adjustable Difficulty**:
  - Modify delay values to increase or decrease game speed.
- **Expanded Gameplay**:
  - Add more LEDs and buttons for a complex version of the game.
- **Custom Sequences**:
  - Update `led_sequence[]` for unique patterns.

---

## Additional Notes

- **Troubleshooting**:
  - If the LEDs or buttons do not respond as expected, double-check all connections against the schematic.
  - Ensure the STM32 board is correctly powered and the GPIO ports are properly configured.
- **Learning Opportunity**:
  - This project offers hands-on experience with GPIO programming, real-time feedback, and embedded system design.
  - It provides a strong foundation for understanding the interaction between hardware and software in microcontroller-based systems.

---

## License

This project is licensed under the [MIT License](./LICENSE). Feel free to use, modify, and distribute the code under the terms of the license.

---

## Credits & Acknowledgments

- **Developer**: Simran Gahra  
- Project developed as part of the **ENSE 352 Architecture Design Lab**.
- Special thanks to the **University of Regina ENSE Labs** for guidance and resources.

---

By combining interactive gameplay with real-time embedded system concepts, the Simon Memory Game serves as a practical and educational project for enthusiasts and students alike.

 