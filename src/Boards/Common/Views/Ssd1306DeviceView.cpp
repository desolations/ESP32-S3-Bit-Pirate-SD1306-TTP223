#if defined(DEVICE_CUSTOM) && defined(CUSTOM_DISPLAY_DRIVER_SSD1306)

#include "Boards/Common/Views/Ssd1306DeviceView.h"

Ssd1306DeviceView::Ssd1306DeviceView(const Ssd1306Config& displayConfig)
    : config(displayConfig),
      display(displayConfig.address, displayConfig.pinSda, displayConfig.pinScl) {
}

SPIClass& Ssd1306DeviceView::getSharedSpiInstance() {
    return sharedSpi;
}

void* Ssd1306DeviceView::getScreen() {
    return &display;
}

void Ssd1306DeviceView::initialize() {
    display.init();
    if (config.flip) display.flipScreenVertically();
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setColor(WHITE);
    setBrightness(brightnessPct);
    display.display();
}

void Ssd1306DeviceView::logo() {
    clear();
    GlobalState& state = GlobalState::getInstance();
    std::string version = std::string("ESP32 Bit Pirate - ") + state.getVersion();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(64, 12, "BIT PIRATE");
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 36, version.c_str());
    display.drawString(64, 52, "CUSTOM / SSD1306");
    display.display();
}

void Ssd1306DeviceView::welcome(TerminalTypeEnum& terminalType, std::string& terminalInfos) {
    if (terminalType == TerminalTypeEnum::WiFiAp) welcomeHotspot(terminalInfos);
    else if (terminalType == TerminalTypeEnum::WiFiClient) welcomeWeb(terminalInfos);
    else welcomeSerial(terminalInfos);
}

void Ssd1306DeviceView::loading() {
    clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(64, 24, "Loading...");
    display.display();
}

void Ssd1306DeviceView::clear() {
    display.clear();
    display.display();
}

void Ssd1306DeviceView::drawLogicTrace(uint8_t pin, const std::vector<uint8_t>& buffer, uint8_t step) {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.setColor(WHITE);
    char hdr[16];
    snprintf(hdr, sizeof(hdr), "GPIO %u", pin);
    display.drawString(0, 0, hdr);

    const int highY = 18;
    const int lowY = 54;
    int x = 0;
    for (size_t i = 1; i < buffer.size(); ++i) {
        uint8_t prev = buffer[i - 1];
        uint8_t curr = buffer[i];
        int y1 = prev ? highY : lowY;
        int y2 = curr ? highY : lowY;
        if (curr != prev) {
            display.drawHorizontalLine(x, y1, step);
            display.drawVerticalLine(x + step, y1 < y2 ? y1 : y2, (y2 > y1 ? y2 - y1 : y1 - y2));
        } else {
            display.drawHorizontalLine(x, y1, step);
        }
        x += step;
        if (x > 128 - step) break;
    }
    display.display();
}

void Ssd1306DeviceView::drawAnalogicTrace(uint8_t pin, const std::vector<uint8_t>& buffer, uint8_t step) {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.setColor(WHITE);
    char hdr[16];
    snprintf(hdr, sizeof(hdr), "GPIO %u", pin);
    display.drawString(0, 0, hdr);

    if (buffer.empty()) { display.display(); return; }

    const int topY = 12;
    const int h = 64 - topY;
    int x = 0;
    int prevY = topY + h - 1 - ((buffer[0] >> 1) * (h - 1)) / 134;
    for (size_t i = 1; i < buffer.size(); ++i) {
        int y = topY + h - 1 - ((buffer[i] >> 1) * (h - 1)) / 134;
        display.drawLine(x, prevY, x + step, y);
        prevY = y;
        x += step;
        if (x > 128 - step) break;
    }
    display.display();
}

void Ssd1306DeviceView::drawWaterfall(
    const std::string& title,
    float startValue,
    float endValue,
    const char* unit,
    int rowIndex,
    int rowCount,
    int level
) {
    (void)startValue;
    (void)endValue;
    (void)unit;

    const int W = 128;
    const int headerH = 10;
    const int graphY = headerH;
    const int graphH = 64 - headerH;

    if (level < 0) level = 0;
    if (level > 100) level = 100;

    if (rowIndex == 0) {
        display.clear();
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.setFont(ArialMT_Plain_10);
        display.drawString(0, 0, title.c_str());
    }
    if (rowCount <= 1) { display.display(); return; }
    if (rowIndex < 0) rowIndex = 0;
    if (rowIndex > rowCount - 1) rowIndex = rowCount - 1;

    int y = graphY + (int)((int64_t)rowIndex * (graphH - 1) / (rowCount - 1));

    display.setColor(BLACK);
    display.drawHorizontalLine(0, y, W);
    display.setColor(WHITE);

    int barLen = (level * W) / 100;
    if (barLen > 0) display.drawHorizontalLine(0, y, barLen);
    display.display();
}

void Ssd1306DeviceView::setRotation(uint8_t rotation) {
    if (rotation == 1 || rotation == 2) display.flipScreenVertically();
    else display.resetOrientation();
}

void Ssd1306DeviceView::setBrightness(uint8_t brightness) {
    if (brightness > 100) brightness = 100;
    brightnessPct = brightness;
    display.setContrast((uint8_t)((brightnessPct * 255) / 100));
}

uint8_t Ssd1306DeviceView::getBrightness() {
    return brightnessPct;
}

void Ssd1306DeviceView::topBar(const std::string& title, bool submenu, bool searchBar) {
    (void)submenu;
    (void)searchBar;

    display.setColor(BLACK);
    display.fillRect(0, 0, 128, 12);
    display.setColor(WHITE);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 0, title.c_str());
    display.display();
}

void Ssd1306DeviceView::horizontalSelection(
    const std::vector<std::string>& options,
    uint16_t selectedIndex,
    const std::string& description1,
    const std::string& description2
) {
    display.clear();
    display.setColor(WHITE);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 0, description1.c_str());

    const int listTop = 14;
    const int rowH = 12;
    const int n = (int)options.size();
    for (int i = 0; i < n; ++i) {
        int y = listTop + i * rowH;
        bool selected = (i == (int)selectedIndex);
        if (selected) {
            display.setColor(WHITE);
            display.fillRect(8, y, 112, rowH);
            display.setColor(BLACK);
        }
        display.drawString(64, y + 1, options[i].c_str());
        display.setColor(WHITE);
    }

    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 63 - 10, description2.c_str());
    display.display();
}

void Ssd1306DeviceView::welcomeSerial(const std::string& baudStr) {
    clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 8, "Open Serial (USB COM)");
    display.setFont(ArialMT_Plain_16);
    std::string baud = "Baud: " + baudStr;
    display.drawString(64, 26, baud.c_str());
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 50, "Then press any key");
    display.display();
}

void Ssd1306DeviceView::welcomeWeb(const std::string& ipStr) {
    clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 10, "Open browser to connect");
    display.setFont(ArialMT_Plain_16);
    std::string ip = "http://" + ipStr;
    display.drawString(64, 30, ip.c_str());
    display.display();
}

void Ssd1306DeviceView::welcomeHotspot(const std::string& ipStr) {
    GlobalState& state = GlobalState::getInstance();
    PinoutConfig cfg;
    cfg.setMode("HOTSPOT");
    cfg.setMappings({
        state.getActiveApName(),
        std::string("PW ") + state.getApPassword(),
        std::string("IP ") + ipStr,
        "CONNECT TO AP"
    });
    show(cfg);
}

void Ssd1306DeviceView::adapterMode(const std::string& adapterName, const std::string& description, const std::vector<std::string>& details) {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(64, 0, adapterName.c_str());
    display.setFont(ArialMT_Plain_10);
    int y = 20;
    for (const auto& d : details) {
        if (y > 44) break;
        display.drawString(64, y, d.c_str());
        y += 11;
    }
    display.drawString(64, 54, description.c_str());
    display.display();
}

void Ssd1306DeviceView::show(PinoutConfig& pinoutConfig) {
    display.clear();
    const auto& mappings = pinoutConfig.getMappings();
    auto mode = pinoutConfig.getMode();

    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.setColor(WHITE);
    std::string modeStr = "MODE " + mode;
    display.drawString(64, 0, modeStr.c_str());
    display.drawHorizontalLine(0, 12, 128);

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    int y = 16;
    for (const auto& m : mappings) {
        if (y > 64 - 10) break;
        display.drawString(2, y, m.c_str());
        y += 11;
    }
    if (mappings.empty()) {
        display.drawString(10, 30, "Nothing to display");
    }
    display.display();
}

#endif