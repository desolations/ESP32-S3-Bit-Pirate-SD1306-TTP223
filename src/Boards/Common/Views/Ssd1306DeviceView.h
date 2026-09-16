#pragma once

#if defined(DEVICE_CUSTOM) && defined(CUSTOM_DISPLAY_DRIVER_SSD1306)

#include "Interfaces/IDeviceView.h"
#include "States/GlobalState.h"

#include <Arduino.h>
#include <SSD1306Wire.h>
#include <SPI.h> 

// Hardware description for an I2C-connected SSD1306 OLED panel.
struct Ssd1306Config {
    int8_t pinSda = 8;
    int8_t pinScl = 18;
    uint8_t address = 0x3C;
    bool flip = false;
};

class Ssd1306DeviceView : public IDeviceView {
public:
    explicit Ssd1306DeviceView(const Ssd1306Config& config);

    void initialize() override;
    SPIClass& getSharedSpiInstance() override;
    void* getScreen() override;
    void logo() override;
    void welcome(TerminalTypeEnum& terminalType, std::string& terminalInfos) override;
    void show(PinoutConfig& config) override;
    void loading() override;
    void adapterMode(const std::string& adapterName, const std::string& description, const std::vector<std::string>& details) override;
    void clear() override;
    void drawLogicTrace(uint8_t pin, const std::vector<uint8_t>& buffer, uint8_t step) override;
    void drawAnalogicTrace(uint8_t pin, const std::vector<uint8_t>& buffer, uint8_t step) override;
    void drawWaterfall(const std::string& title, float startValue, float endValue, const char* unit, int rowIndex, int rowCount, int level) override;
    void setRotation(uint8_t rotation) override;
    void setBrightness(uint8_t brightness) override;
    uint8_t getBrightness() override;
    void topBar(const std::string& title, bool submenu, bool searchBar) override;
    void horizontalSelection(
        const std::vector<std::string>& options,
        uint16_t selectedIndex,
        const std::string& description1,
        const std::string& description2
    ) override;

private:
    Ssd1306Config config;
    SSD1306Wire display;
    uint8_t brightnessPct = 100;
    SPIClass sharedSpi{HSPI};

    void welcomeWeb(const std::string& ip);
    void welcomeHotspot(const std::string& ip);
    void welcomeSerial(const std::string& baud);
};

#endif