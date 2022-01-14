#include "PinConfig.h"

#include <Arduino.h>


namespace PinConfig {

    const uint8_t MATRIX_COL_2    =  0;
    const uint8_t MATRIX_COL_1    =  1;
    const uint8_t MATRIX_ROW_1    = 15;
    const uint8_t MATRIX_ROW_2    = 14;
    const uint8_t MATRIX_ROW_3    = 16;
    const uint8_t SWITCH          =  4;
    const uint8_t IR_SENSOR       =  5;
    const uint8_t LED_LSB         =  6;
    const uint8_t LED_MSB         =  7;
    const uint8_t LED_MOUSE       =  8;
    const uint8_t BUTTON_LEFT     =  9;
    const uint8_t BUTTON_RIGHT    = 10;
    const uint8_t VOLUME_POT      = A0;
    const uint8_t JOY_X           = A1;
    const uint8_t JOY_Y           = A2;

    void initPins() {

        //turn off RX and TX leds

        //option 1
        //TXLED0; //turn off TXLED
        //TXLED1; //turn on TXLED
        //RXLED0; //turn off RXLED
        //RXLED1; //turn on RXLED

        //option 2
        pinMode(LED_BUILTIN_TX, INPUT);
        pinMode(LED_BUILTIN_RX, INPUT);

        //option 3
        //bitClear(DDRD, 5);
        //bitClear(DDRB, 0);

        pinMode(MATRIX_COL_1, OUTPUT);
        pinMode(MATRIX_COL_2, OUTPUT);
        pinMode(MATRIX_ROW_1, INPUT_PULLUP);
        pinMode(MATRIX_ROW_2, INPUT_PULLUP);
        pinMode(MATRIX_ROW_3, INPUT_PULLUP);
        pinMode(SWITCH, INPUT_PULLUP);
        pinMode(LED_LSB, OUTPUT);
        pinMode(LED_MSB, OUTPUT);
        pinMode(LED_MOUSE, OUTPUT);
        pinMode(BUTTON_LEFT, INPUT_PULLUP);
        pinMode(BUTTON_RIGHT, INPUT_PULLUP);
        pinMode(VOLUME_POT, INPUT);
        pinMode(JOY_X, INPUT);
        pinMode(JOY_Y, INPUT);
        //pinMode(IR_SENSOR, INPUT);

        digitalWrite(LED_MOUSE, LOW);
    }

};
