#include "MacroPad.h"
#include "PinConfig.h"
#include "IrRemoteWrapper.h"

#include <Arduino.h>

#define UPDATES_PER_SECOND 20
#define TICKS_PER_UPDATE (1000.0 / float(UPDATES_PER_SECOND))

#define MOUSE_SENSITIVITY 30


void MacroPad::start() {
    init();

    mPrevTicks = millis();
    loop();
}

void MacroPad::init() {
    PinConfig::initPins();
    IrRemoteWrapper::init();
    mInputManager.init();
}

void MacroPad::registerActions() {

}

void MacroPad::loop() {
    for (;;) {
        mNewTicks = millis();
        mTicks = mNewTicks - mPrevTicks;
        mPrevTicks = mNewTicks;

        update();

        if(mTicks < TICKS_PER_UPDATE) {
            delay(TICKS_PER_UPDATE - mTicks);
        }
    }
}

void MacroPad::update() {
    handleInput();
    handleLEDs();
}

void MacroPad::handleInput() {
    mInputManager.processInput();

    mIsMouseMode = mInputManager.isButtonPressed(InputManager::Buttons::SWITCH);
    if (!mIsMouseMode) {
        if (mInputManager.wasButtonPressedNow(InputManager::Buttons::RIGHT)) {
            mMacroState = (mMacroState + 1) % 4;
        }
    }

    //TODO update this to better handle the actions, maybe a bit more genrically
    if (mInputManager.wasButtonPressedNow(InputManager::Buttons::MAT_11)) {
        mMacroActions.OnMatButton[0][0](MacroActions::ActionType::TAP);
    }

    if (mInputManager.wasButtonPressedNow(InputManager::Buttons::IR_PLAY_PAUSE)) {
        mMacroActions.OnIrRemoteButton[0](MacroActions::ActionType::TAP);
    }

    if (mInputManager.isButtonPressed(InputManager::Buttons::SWITCH)) {
        //move mouse
        auto deltaX = mInputManager.getJoyXDelta() / MOUSE_SENSITIVITY;
        auto deltaY = mInputManager.getJoyYDelta() / MOUSE_SENSITIVITY;
        if (deltaX || deltaY) {
            mMacroActions.OnJoy(deltaX, deltaY);
        }

        //mouse buttons
        if (mInputManager.isButtonPressed(InputManager::Buttons::LEFT)) {
            mMacroActions.OnLeftButton(MacroActions::ActionType::PRESS);
        } else if (mInputManager.isButtonReleased(InputManager::Buttons::LEFT)) {
            mMacroActions.OnLeftButton(MacroActions::ActionType::RELEASE);
        }

        if (mInputManager.isButtonPressed(InputManager::Buttons::RIGHT)) {
            mMacroActions.OnRightButton(MacroActions::ActionType::PRESS);
        } else if (mInputManager.isButtonReleased(InputManager::Buttons::RIGHT)) {
            mMacroActions.OnRightButton(MacroActions::ActionType::RELEASE);
        }
    }
}

void MacroPad::handleLEDs() {
    digitalWrite(PinConfig::LED_MOUSE, mIsMouseMode);
    digitalWrite(PinConfig::LED_LSB, mMacroState & (1 << 0));
    digitalWrite(PinConfig::LED_MSB, mMacroState & (1 << 1));
}
