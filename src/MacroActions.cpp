#include "MacroActions.h"

//this must to be included before HID itself
#include <Arduino.h> 
#include <HID-Project.h>

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
    Consumer.write(CONSUMER_EXPLORER);
}

static void mat_12(ActionType action) {
    Consumer.write(CONSUMER_BROWSER_HOME);
}

static void mat_21(ActionType action) {
    Keyboard.write(KEY_LEFT_GUI);
}

static void mat_22(ActionType action) {
    Mouse.move(0, 0, 2);
}

static void mat_31(ActionType action) {
    
}

static void mat_32(ActionType action) {
    Mouse.move(0, 0, -2);
}

static void left(ActionType action) {
    handleMouseClick(action, MOUSE_LEFT);
}

static void right(ActionType action) {
    handleMouseClick(action, MOUSE_RIGHT);
}

static void irPlayPause(ActionType action) {
    Consumer.write(MEDIA_PLAY_PAUSE);
}

static void irStop(ActionType action) {
    Consumer.write(MEDIA_STOP);
}

static void irVolUp(ActionType action) {
    Consumer.write(MEDIA_VOL_UP);
}

static void irVolDown(ActionType action) {
    Consumer.write(MEDIA_VOLUME_DOWN);
}

static void irMute(ActionType action) {
    Consumer.write(MEDIA_VOLUME_MUTE);
}

static void irNext(ActionType action) {
    Consumer.write(MEDIA_NEXT);
}

static void irPrev(ActionType action) {
    Consumer.write(MEDIA_PREV);
}

static void scrollUp() {
    Mouse.move(0, 0, 2);
}

static void scrollDown() {
    Mouse.move(0, 0, -2);
}

static void volumeUp() {
    Consumer.write(MEDIA_VOL_UP);
}

static void volumeDown() {
    Consumer.write(MEDIA_VOLUME_DOWN);
}

static void joystick(int8_t dtX, int8_t dtY) {
    Mouse.move(dtX, dtY, 0);
}


MacroActions::MacroActions()
    : OnMatButton{ {mat_11, mat_12}, {mat_21, mat_22}, {mat_31, mat_32} }
    , OnLeftButton(left)
    , OnRightButton(right)
    , OnIrRemoteButton({ irPlayPause, irStop, irVolUp, irVolDown, irMute, irPrev, irNext })
    , OnScrollUp(scrollUp)
    , OnScrollDown(scrollDown)
    , OnVolumeUp(volumeUp)
    , OnVolumeDown(volumeDown)
    , OnJoy(joystick)
{
    Consumer.begin();
    Keyboard.begin();
    Mouse.begin();
}
