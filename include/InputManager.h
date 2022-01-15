#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <stdint.h>


class InputManager{
public:
    enum Buttons {
        MAT_11          = 1 <<  0,
        MAT_12          = 1 <<  1,
        MAT_21          = 1 <<  2,
        MAT_22          = 1 <<  3,
        MAT_31          = 1 <<  4,
        MAT_32          = 1 <<  5,
        LEFT            = 1 <<  6,
        RIGHT           = 1 <<  7,
        SWITCH          = 1 <<  8,
        IR_PLAY_PAUSE   = 1 <<  9,
        IR_STOP         = 1 << 10,
        IR_MUTE         = 1 << 11,
        IR_VOL_UP       = 1 << 12,
        IR_VOL_DOWN     = 1 << 13,
        IR_PREV         = 1 << 14,
        IR_NEXT         = 1 << 15,
    };

    void init();
    void processInput();
    bool isButtonPressed(Buttons button);
    bool isButtonHeldDown(Buttons button);
    bool isButtonReleased(Buttons button);
    bool wasButtonPressedNow(Buttons button);

    bool getPotPercentage(uint8_t& outValue);
    int16_t getJoyXDelta();
    int16_t getJoyYDelta();

    uint16_t getMask();

private:
    void processMatrixButtons();
    void processIrRemote();
    void processAnalogInputs();
    void processPushBUttons();

    uint8_t mPotValue = 0;
    uint8_t mOldPotValue = 0;

    uint16_t mButtonMask = 0;
    uint16_t mPrevButtonMask = 0;

    uint16_t mJoyXValue = 0;
    uint16_t mOldJoyXValue = 0;
    uint16_t mJoyYValue = 0;
    uint16_t mOldJoyYValue = 0;
    uint16_t mNeutralX = 0;
    uint16_t mNeutralY = 0;

};

#endif // INPUT_MANAGER_H
