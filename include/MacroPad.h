#ifndef MACRO_PAD_H
#define MACRO_PAD_H

#include "InputManager.h"
#include "MacroActions.h"


class MacroPad {
public:
    void start();

private:
    void init();
    void registerActions();
    void loop();
    void update();
    void handleInputs();
    void handleMouse();
    void handleButtons();
    void handleIrRemote();
    void handlePotWheel();
    void handleLEDs();

    InputManager mInputManager;
    MacroActions mMacroActions;

    bool mIsMouseMode = false;
    uint8_t mMacroState = 0;
    uint32_t mPrevTicks = 0;
    uint32_t mNewTicks = 0;
    uint32_t mTicks = 0;

};

#endif // MACRO_PAD_H
