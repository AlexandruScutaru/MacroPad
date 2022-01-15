#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <stdint.h>


class InputManager{
public:
    enum Buttons {
        MAT_11          = 0x0001,
        MAT_12          = 0x0002,
        MAT_21          = 0x0004,
        MAT_22          = 0x0008,
        MAT_31          = 0x0010,
        MAT_32          = 0x0020,
        LEFT            = 0x0040,
        RIGHT           = 0x0080,
        SWITCH          = 0x0100,
        IR_PLAY_PAUSE   = 0x0200,
        IR_MUTE         = 0x0400,
        IR_VOL_UP       = 0x0800,
        IR_VOL_DOWN     = 0x1000,
        IR_PREV         = 0x2000,
        IR_NEXT         = 0x4000,
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
