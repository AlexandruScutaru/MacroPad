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
    handleInputs();
    handleLEDs();
}

void MacroPad::handleInputs() {
    mInputManager.processInput();
    mIsMouseMode = mInputManager.isButtonPressed(InputManager::Buttons::SWITCH);

    handleButtons();
    handleIrRemote();
    handleMouse();
    handlePotWheel();
}

void MacroPad::handleMouse() {
    if (!mIsMouseMode)
        return;

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

void MacroPad::handleButtons() {
    // button matrix
    if (mInputManager.wasButtonPressedNow(InputManager::Buttons::MAT_11)) {
        mMacroActions.OnMatButton[0][0](MacroActions::ActionType::TAP);
    }
    if (mInputManager.wasButtonPressedNow(InputManager::Buttons::MAT_12)) {
        mMacroActions.OnMatButton[0][1](MacroActions::ActionType::TAP);
    }
    if (mInputManager.wasButtonPressedNow(InputManager::Buttons::MAT_21)) {
        mMacroActions.OnMatButton[1][0](MacroActions::ActionType::TAP);
    }
    if (mInputManager.wasButtonPressedNow(InputManager::Buttons::MAT_22)) {
        mMacroActions.OnMatButton[1][1](MacroActions::ActionType::TAP);
    }
    if (mInputManager.wasButtonPressedNow(InputManager::Buttons::MAT_31)) {
        mMacroActions.OnMatButton[2][0](MacroActions::ActionType::TAP);
    }
    if (mInputManager.wasButtonPressedNow(InputManager::Buttons::MAT_32)) {
        mMacroActions.OnMatButton[2][1](MacroActions::ActionType::TAP);
    }

    //the other buttons
    if (!mIsMouseMode) {
        if (mInputManager.wasButtonPressedNow(InputManager::Buttons::LEFT)) {
            //no op for now
        }

        if (mInputManager.wasButtonPressedNow(InputManager::Buttons::RIGHT)) {
            mMacroState = (mMacroState + 1) % 4;
        }
    }
}

void MacroPad::handleIrRemote() {
    if (mInputManager.wasButtonPressedNow(InputManager::Buttons::IR_PLAY_PAUSE)) {
        mMacroActions.OnIrRemoteButton[0](MacroActions::ActionType::TAP);
    }
    if (mInputManager.wasButtonPressedNow(InputManager::Buttons::IR_VOL_UP)) {
        mMacroActions.OnIrRemoteButton[1](MacroActions::ActionType::TAP);
    }
    if (mInputManager.wasButtonPressedNow(InputManager::Buttons::IR_VOL_DOWN)) {
        mMacroActions.OnIrRemoteButton[2](MacroActions::ActionType::TAP);
    }
    if (mInputManager.wasButtonPressedNow(InputManager::Buttons::IR_MUTE)) {
        mMacroActions.OnIrRemoteButton[3](MacroActions::ActionType::TAP);
    }
    if (mInputManager.wasButtonPressedNow(InputManager::Buttons::IR_PREV)) {
        mMacroActions.OnIrRemoteButton[4](MacroActions::ActionType::TAP);
    }
    if (mInputManager.wasButtonPressedNow(InputManager::Buttons::IR_NEXT)) {
        mMacroActions.OnIrRemoteButton[5](MacroActions::ActionType::TAP);
    }
}

void MacroPad::handlePotWheel() {
    uint8_t potValue = 0;
    if (mInputManager.getPotPercentage(potValue)) {
        mMacroActions.OnPotWheel(potValue);
    }
}

void MacroPad::handleLEDs() {
    digitalWrite(PinConfig::LED_MOUSE, mIsMouseMode);
    digitalWrite(PinConfig::LED_LSB, mMacroState & (1 << 0));
    digitalWrite(PinConfig::LED_MSB, mMacroState & (1 << 1));
}
