#include "IrRemoteWrapper.h"
#include "PinConfig.h"

#include <Arduino.h>
#include <IRremote.hpp>


namespace IrRemoteWrapper {

    void init() {
        IrReceiver.begin(PinConfig::IR_SENSOR, DISABLE_LED_FEEDBACK);
    }

    Keys prcessIrInput() {
        if (IrReceiver.decode()) {
            //IrReceiver.printIRResultShort(&Serial);
            IrReceiver.resume();

            if (IrReceiver.decodedIRData.address == 0xBF00) {
                switch (IrReceiver.decodedIRData.command) {
                    case 0x00: return Keys::PLAY_PAUSE;
                    case 0x01: return Keys::MUTE;
                    case 0x02: return Keys::STOP;
                    case 0x05: return Keys::VOL_DOWN;
                    case 0x06: return Keys::VOL_UP;
                    case 0x09: return Keys::PREV;
                    case 0x0A: return Keys::NEXT;
                    default: return Keys::UNKNOWN;
                }
            }
        }

        return Keys::UNKNOWN;

        // some nice remote but kinda bad because it uses an unknown protocol
        // commands couldn't be decoded so I switch on IrReceiver.decodedIRData.decodedRawData
        // which sadly goes all over the place, these being the most common results per button
        //case 0x6D365E53: return Keys::PLAY_PAUSE;
        //case 0xE3E30CBF: return Keys::VOL_UP;
        //case 0x4D3AAC9A: return Keys::VOL_DOWN;
        //case 0xF650770E: return Keys::MUTE;
        //case 0xA8884316: return Keys::PREV;
        //case 0x91827735: return Keys::NEXT;
    }

}
