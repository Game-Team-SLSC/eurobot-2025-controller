#ifndef __REMOTE_DATA_H__
#define __REMOTE_DATA_H__

#include <Arduino.h>
#include <JoystickData.h>

enum SWITCH_3_POS {UP, DOWN, MIDDLE};

struct RemoteData
{
    JoystickData joystickLeft;
    JoystickData joystickRight;

    bool buttons[16] = {
        false, false, false, false, false, false, false, false, false, false, false, false, false, false
    };
    // for each button true if pressed
    byte slider; // 0 to 255
    byte score; // 0 to 255
  
};

#endif