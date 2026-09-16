#ifdef DEVICE_CUSTOM

#include "Boards/Custom/CustomInput.h"
#include "Data/InputKeys.h"
#include <Arduino.h>
#define STR2(x) #x
#define STR(x) STR2(x)
#pragma message("CONFIG REELLE : DOWN=" STR(CUSTOM_INPUT_DOWN_PIN) " UP=" STR(CUSTOM_INPUT_UP_PIN) " OK=" STR(CUSTOM_INPUT_OK_PIN) " ACTIVE_LOW=" STR(CUSTOM_INPUT_BUTTON_ACTIVE_LOW) " PULLUP=" STR(CUSTOM_INPUT_BUTTON_PULLUP))

CustomInput::CustomInput() {
#if CUSTOM_INPUT_UP_PIN >= 0
  #if CUSTOM_INPUT_BUTTON_PULLUP
    pinMode(CUSTOM_INPUT_UP_PIN, INPUT_PULLUP);
  #else
    pinMode(CUSTOM_INPUT_UP_PIN, INPUT);
  #endif
#endif
#if CUSTOM_INPUT_DOWN_PIN >= 0
  #if CUSTOM_INPUT_BUTTON_PULLUP
    pinMode(CUSTOM_INPUT_DOWN_PIN, INPUT_PULLUP);
  #else
    pinMode(CUSTOM_INPUT_DOWN_PIN, INPUT);
  #endif
#endif
#if CUSTOM_INPUT_OK_PIN >= 0
  #if CUSTOM_INPUT_BUTTON_PULLUP
    pinMode(CUSTOM_INPUT_OK_PIN, INPUT_PULLUP);
  #else
    pinMode(CUSTOM_INPUT_OK_PIN, INPUT);
  #endif
#endif
}

bool CustomInput::isPressed(int pin) {
    if (pin < 0) return false;
#if CUSTOM_INPUT_BUTTON_ACTIVE_LOW
    return digitalRead(pin) == LOW;
#else
    return digitalRead(pin) == HIGH;
#endif
}

char CustomInput::scanButtons() {
    bool up = isPressed(CUSTOM_INPUT_UP_PIN);
    bool down = isPressed(CUSTOM_INPUT_DOWN_PIN);
    bool ok = isPressed(CUSTOM_INPUT_OK_PIN);

    char key = KEY_NONE;
    uint32_t now = millis();

    if (now - lastEvent >= 120) {   // anti double-declenchement
        if (up && !lastUp)           key = KEY_ARROW_LEFT;   // option precedente (meme cle que l'encodeur T-Embed)
        else if (down && !lastDown)  key = KEY_ARROW_RIGHT;  // option suivante
        else if (ok && !lastOk)      key = KEY_OK;
        if (key != KEY_NONE) lastEvent = now;
    }

    lastUp = up;
    lastDown = down;
    lastOk = ok;
    return key;
}

char CustomInput::readChar() {
    return scanButtons();
}

char CustomInput::handler() {
#if CUSTOM_INPUT_UP_PIN < 0 && CUSTOM_INPUT_DOWN_PIN < 0 && CUSTOM_INPUT_OK_PIN < 0
    return KEY_OK;   // aucun bouton configure : auto-validation (comportement d'origine)
#else
    char c = KEY_NONE;
    while ((c = scanButtons()) == KEY_NONE) {
        delay(5);
    }
    return c;
#endif
}

void CustomInput::waitPress(uint32_t timeoutMs) {
#if CUSTOM_INPUT_UP_PIN < 0 && CUSTOM_INPUT_DOWN_PIN < 0 && CUSTOM_INPUT_OK_PIN < 0
    (void)timeoutMs;
#else
    const uint32_t start = millis();
    while (scanButtons() == KEY_NONE) {
        if (timeoutMs > 0 && (millis() - start) >= timeoutMs) return;
        delay(5);
    }
#endif
}

#endif