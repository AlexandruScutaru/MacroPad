#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#include <stdint.h>


namespace PinConfig {

    extern const uint8_t MATRIX_COL_2;
    extern const uint8_t MATRIX_COL_1;
    extern const uint8_t MATRIX_ROW_1;
    extern const uint8_t MATRIX_ROW_2;
    extern const uint8_t MATRIX_ROW_3;
    extern const uint8_t SWITCH;
    extern const uint8_t IR_SENSOR;
    extern const uint8_t LED_LSB;
    extern const uint8_t LED_MSB;
    extern const uint8_t LED_MOUSE;
    extern const uint8_t BUTTON_LEFT;
    extern const uint8_t BUTTON_RIGHT;
    extern const uint8_t VOLUME_POT;
    extern const uint8_t JOY_X;
    extern const uint8_t JOY_Y;

    void initPins();

}

#endif //PIN_CONFIG_H
