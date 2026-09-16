#pragma once

#ifdef DEVICE_CUSTOM

#include "Interfaces/IInput.h"
#include "Boards/Custom/CustomBoardConfig.h"
#include <Arduino.h>

class CustomInput : public IInput {
public:
    CustomInput();

    char handler() override;
    char readChar() override;
    void waitPress(uint32_t timeoutMs) override;

private:
    static bool isPressed(int pin);
    char scanButtons();

    bool lastUp = false;
    bool lastDown = false;
    bool lastOk = false;
    uint32_t lastEvent = 0;
};

#endif