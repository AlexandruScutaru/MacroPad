#ifndef IR_REMOTE_WRAPPER_H
#define IR_REMOTE_WRAPPER_H


namespace IrRemoteWrapper {

    enum class Keys {
        UNKNOWN = 0,
        PLAY_PAUSE,
        STOP,
        VOL_UP,
        VOL_DOWN,
        MUTE,
        PREV,
        NEXT
    };

    void init();
    Keys prcessIrInput();

}

#endif //IR_REMOTE_WRAPPER_H
