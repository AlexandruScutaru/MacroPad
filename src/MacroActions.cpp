#include "MacroActions.h"

#include <Mouse.h>
#include <Keyboard.h>

using ActionType = MacroActions::ActionType;


static void handleMouseClick(ActionType action, uint8_t button) {
    switch (action)
    {
        case ActionType::PRESS:
            Mouse.press(button);
            break;
        case ActionType::RELEASE:
            Mouse.release(button);
            break;
        case ActionType::TAP:
            Mouse.press(button);
            Mouse.release(button);
            break;
        default:
            break;
    }
}

static void mat_11(ActionType action) {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.release(KEY_LEFT_GUI);
}

static void mat_12(ActionType action) {
    
}

static void mat_21(ActionType action) {
    
}

static void mat_22(ActionType action) {
    
}

static void mat_31(ActionType action) {
    
}

static void mat_32(ActionType action) {
    
}

static void left(ActionType action) {
    handleMouseClick(action, MOUSE_LEFT);
}

static void right(ActionType action) {
    handleMouseClick(action, MOUSE_RIGHT);
}

static void irPlay(ActionType action) {
    Keyboard.press('e');
    Keyboard.release('e');
}

static void irVolUp(ActionType action) {
    
}

static void irVolDown(ActionType action) {
    
}

static void irMute(ActionType action) {
    
}

static void irNext(ActionType action) {
    
}

static void irPrev(ActionType action) {
    
}

static void pot(int8_t dt) {
    
}

static void joystick(int8_t dtX, int8_t dtY) {
    Mouse.move(dtX, dtY, 0);
}


MacroActions::MacroActions() 
    : OnMatButton{ {mat_11, mat_12}, {mat_21, mat_22}, {mat_31, mat_32} }
    , OnLeftButton(left)
    , OnRightButton(right)
    , OnIrRemoteButton({ irPlay, irVolUp, irVolDown, irMute, irPrev, irNext })
    , OnPotWheel(pot)
    , OnJoy(joystick)
{}
