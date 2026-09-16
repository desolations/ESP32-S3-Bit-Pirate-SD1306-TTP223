#pragma once

#ifdef DEVICE_CUSTOM

#include "Boards/Custom/CustomBoardConfig.h"
#include "Boards/Custom/CustomInput.h"
#include "Boards/Common/Serial/BoardHostSerial.h"

#if defined(CUSTOM_DISPLAY_DRIVER_ST7789_SPI)
  #include "Boards/Common/Views/St7789SpiDeviceView.h"
#elif defined(CUSTOM_DISPLAY_DRIVER_ST7789_PARALLEL)
  #include "Boards/Common/Views/St7789ParallelDeviceView.h"
#elif defined(CUSTOM_DISPLAY_DRIVER_SSD1306)
  #include "Boards/Common/Views/Ssd1306DeviceView.h"
#else
  #include "Boards/Common/Views/NoScreenDeviceView.h"
#endif

class CustomBoard final {
public:
    CustomBoard();

    void initialize();
    IDeviceView& getDeviceView();
    IInput& getDeviceInput();
    IHostSerial& getHostSerial();

private:
#if defined(CUSTOM_DISPLAY_DRIVER_ST7789_SPI)
    static St7789SpiConfig createDisplayConfig();
    St7789SpiConfig displayConfig;
    St7789SpiDeviceView deviceView;
#elif defined(CUSTOM_DISPLAY_DRIVER_ST7789_PARALLEL)
    static St7789ParallelConfig createDisplayConfig();
    St7789ParallelConfig displayConfig;
    St7789ParallelDeviceView deviceView;
#elif defined(CUSTOM_DISPLAY_DRIVER_SSD1306)
    static Ssd1306Config createDisplayConfig();
    Ssd1306Config displayConfig;
    Ssd1306DeviceView deviceView;
#else
    NoScreenDeviceView deviceView;
#endif

    BoardHostSerial hostSerial;
    CustomInput deviceInput;
};

#endif