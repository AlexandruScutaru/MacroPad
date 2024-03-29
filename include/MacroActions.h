#ifndef MACRO_ACTIONS_H
#define MACRO_ACTIONS_H

#include <stdint.h>


// Tried to decouple the actual macro actions from the "controller"
// in order to define new actions easier.
// The idea didn't quite turn as I expected so this needs to be re-done in a smarter way.

struct MacroActions {

    enum class ActionType {
        PRESS,
        RELEASE,
        TAP
    };

    MacroActions();

    using ButtonFunc = void (*)(ActionType action);
    using RotEncoderFunc = void (*)();
    using JoystickFunc = void (*)(int8_t dtX, int8_t dtY);

    ButtonFunc OnMatButton[3][2];
    ButtonFunc OnLeftButton;
    ButtonFunc OnRightButton;
    ButtonFunc OnIrRemoteButton[7];
    RotEncoderFunc OnScrollUp;
    RotEncoderFunc OnScrollDown;
    RotEncoderFunc OnVolumeUp;
    RotEncoderFunc OnVolumeDown;
    JoystickFunc OnJoy;

};

#endif // MACRO_ACTIONS_H
