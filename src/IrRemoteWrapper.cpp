#include "IrRemoteWrapper.h"
#include "PinConfig.h"

#include <IRremote.hpp>


namespace IrRemoteWrapper {

    void init() {
        IrReceiver.begin(PinConfig::IR_SENSOR, DISABLE_LED_FEEDBACK);
    }

    Keys prcessIrInput() {
        if (IrReceiver.decode()) {
            IrReceiver.resume();
            switch (IrReceiver.decodedIRData.decodedRawData) {
                case 0x6D365E53: return Keys::PLAY_PAUSE;
                case 0xE3E30CBF: return Keys::VOL_UP;
                case 0x4D3AAC9A: return Keys::VOL_DOWN;
                case 0xF650770E: return Keys::MUTE;
                case 0xA8884316: return Keys::PREV;
                case 0x91827735: return Keys::NEXT;
                default: return Keys::UNKNOWN;
            }
        }
        return Keys::UNKNOWN;
    }

}
