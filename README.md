# MacroPad
Simple and compact (5x7 cm) Arduino Pro Micro based macro pad.

For wiring follow [these pins definitions](https://github.com/AlexandruScutaru/MacroPad/blob/master/src/PinConfig.cpp#L8-L22) and the cartoonish schematic below:\
<img src="https://github.com/AlexandruScutaru/MacroPad/blob/master/readme_resources/macro_kb_schemtic.png" alt="macro_kb_schemtic.png" width="40%"/>

The Slide Switch is used to put hte MacroPad in mouse mode, where the Joystick and the two smaller push buttons directly under the ProMicro board act as a mouse.

There are 3 LEDs. The orange one is an indicator that the MacroPad is in MouseMode. 
The 2 other green ones form a binary counter showing the _page_ the MacroPad 6-button matrix is in (resulting in 24 different actions). Of course this number of _pages_ can be increased, but even 4 is quite a lot.

Additionally there is an IR sensor that extends the amount of inputs even more.
