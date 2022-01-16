#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <stdint.h>


class InputManager{
public:
    enum Buttons : uint32_t {
        MAT_11           = 1UL <<  0UL,
        MAT_12           = 1UL <<  1UL,
        MAT_21           = 1UL <<  2UL,
        MAT_22           = 1UL <<  3UL,
        MAT_31           = 1UL <<  4UL,
        MAT_32           = 1UL <<  5UL,
        LEFT             = 1UL <<  6UL,
        RIGHT            = 1UL <<  7UL,
        SWITCH           = 1UL <<  8UL,
        ROT_ENCODER_UP   = 1UL <<  9UL,
        ROT_ENCODER_DOWN = 1UL << 10UL,
        IR_PLAY_PAUSE    = 1UL << 11UL,
        IR_STOP          = 1UL << 12UL,
        IR_MUTE          = 1UL << 13UL,
        IR_VOL_UP        = 1UL << 14UL,
        IR_VOL_DOWN      = 1UL << 15UL,
        IR_PREV          = 1UL << 16UL,
        IR_NEXT          = 1UL << 17UL,
    };

    void init();
    void processInput();
    bool isButtonPressed(Buttons button);
    bool isButtonHeldDown(Buttons button);
    bool isButtonReleased(Buttons button);
    bool wasButtonPressedNow(Buttons button);

    int16_t getJoyXDelta();
    int16_t getJoyYDelta();

    uint16_t getMask();

private:
    void processMatrixButtons();
    void processIrRemote();
    void processAnalogInputs();
    void processPushBUttons();
    void processRotaryEncoder();

    uint8_t mEncoderA = 0;
    uint8_t mEncoderB = 0;
    uint8_t mEncoderAPrev = 0;

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
