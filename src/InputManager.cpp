#include "InputManager.h"
#include "PinConfig.h"
#include "IrRemoteWrapper.h"
#include "MacroPad.h"

#include <Arduino.h>


InputManager::InputManager()
    : mRotEncoder(RotaryEncoder(PinConfig::ROT_ENCODER_A, PinConfig::ROT_ENCODER_B, RotaryEncoder::LatchMode::TWO03))
{}

void InputManager::init(MacroPad* macroPad) {
    mMacroPad = macroPad;

    mNeutralX = analogRead(PinConfig::JOY_X);
    mNeutralY = analogRead(PinConfig::JOY_Y);
}

void InputManager::processInput() {
    mPrevButtonMask = mButtonMask;
    mButtonMask = 0;

    mRotEncoder.tick();

    processPushBUttons();
    processMatrixButtons();
    processIrRemote();
    processAnalogInputs();
    processRotaryEncoder();
}

bool InputManager::isButtonPressed(Buttons button) {
    return (bool)(mButtonMask & button);
}

bool InputManager::isButtonHeldDown(Buttons button) {
    return (mPrevButtonMask & button) && (mButtonMask & button);
}

bool InputManager::isButtonReleased(Buttons button) {
    return (mPrevButtonMask & button) && !(mButtonMask & button);
}

bool InputManager::wasButtonPressedNow(Buttons button) {
    return (mButtonMask & button) && !(mPrevButtonMask & button);
}

int16_t InputManager::getJoyXDelta() {
    return mJoyXValue - mNeutralX;
}

int16_t InputManager::getJoyYDelta() {
    return mJoyYValue - mNeutralY;
}

uint16_t InputManager::getMask() {
    return mButtonMask;
}

void InputManager::processPushBUttons() {
    if (!digitalRead(PinConfig::SWITCH)) {
        mButtonMask |= Buttons::SWITCH;
    }

    if (!digitalRead(PinConfig::BUTTON_LEFT)) {
        mButtonMask |= Buttons::LEFT;
    }

    if (!digitalRead(PinConfig::BUTTON_RIGHT)) {
        mButtonMask |= Buttons::RIGHT;
    }
}

void InputManager::processMatrixButtons() {
    digitalWrite(PinConfig::MATRIX_COL_2, HIGH);
    digitalWrite(PinConfig::MATRIX_COL_1, LOW);
    if (!digitalRead(PinConfig::MATRIX_ROW_1)) {
        mButtonMask |= Buttons::MAT_11; 
    } else if (!digitalRead(PinConfig::MATRIX_ROW_2)) {
        mButtonMask |= Buttons::MAT_21;
    } else if (!digitalRead(PinConfig::MATRIX_ROW_3)) {
        mButtonMask |= Buttons::MAT_31;
    }

    digitalWrite(PinConfig::MATRIX_COL_1, HIGH);
    digitalWrite(PinConfig::MATRIX_COL_2, LOW);
    if (!digitalRead(PinConfig::MATRIX_ROW_1)) {
        mButtonMask |= Buttons::MAT_12;
    } else if (!digitalRead(PinConfig::MATRIX_ROW_2)) {
        mButtonMask |= Buttons::MAT_22;
    } else if (!digitalRead(PinConfig::MATRIX_ROW_3)) {
        mButtonMask |= Buttons::MAT_32;
    }
    digitalWrite(PinConfig::MATRIX_COL_2, HIGH);
}

void InputManager::processIrRemote() {
    using namespace IrRemoteWrapper;
    switch (prcessIrInput()) {
        case Keys::PLAY_PAUSE:
            mButtonMask |= Buttons::IR_PLAY_PAUSE;
            break;
        case Keys::STOP:
            mButtonMask |= Buttons::IR_STOP;
            break;
        case Keys::VOL_UP:
            mButtonMask |= Buttons::IR_VOL_UP;
            break;
        case Keys::VOL_DOWN:
            mButtonMask |= Buttons::IR_VOL_DOWN;
            break;
        case Keys::MUTE:
            mButtonMask |= Buttons::IR_MUTE;
            break;
        case Keys::PREV:
            mButtonMask |= Buttons::IR_PREV;
            break;
        case Keys::NEXT:
            mButtonMask |= Buttons::IR_NEXT;
            break;
        case Keys::UNKNOWN:
        default:
            break;
    }
}

void InputManager::processAnalogInputs() {
    //joystick
    mOldJoyXValue = mJoyXValue;
    mJoyXValue = analogRead(PinConfig::JOY_X);
    mOldJoyYValue = mJoyYValue;
    mJoyYValue = analogRead(PinConfig::JOY_Y);
}

void InputManager::processRotaryEncoder() {
    RotEncoderState state = RotEncoderState::IDLE;

    switch (mRotEncoder.getDirection()) {
    case RotaryEncoder::Direction::CLOCKWISE:
        state = RotEncoderState::DOWN;
        break;
    case RotaryEncoder::Direction::COUNTERCLOCKWISE:
        state = RotEncoderState::UP;
        break;
    default:
        state = RotEncoderState::IDLE; // just so default is not alone :)
        break;
    }

    if (mMacroPad) {
        mMacroPad->handleRottaryEncoder(state);
    }
}
