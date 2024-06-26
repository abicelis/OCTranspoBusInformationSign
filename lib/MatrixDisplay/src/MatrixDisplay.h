#ifndef MATRIX_DISPLAY_H
#define MATRIX_DISPLAY_H
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Model.h>
#include <WeatherData.h>
#include <RouteGroupData.h>
class MatrixDisplay {
    public:
        void begin(int8_t r1_pin,
               int8_t g1_pin,
               int8_t b1_pin,
               int8_t r2_pin,
               int8_t g2_pin,
               int8_t b2_pin,
               int8_t a_pin,
               int8_t b_pin,
               int8_t c_pin,
               int8_t d_pin,
               int8_t e_pin,
               int8_t lat_pin,
               int8_t oe_pin,
               int8_t clk_pin,
               uint16_t panel_res_x,
               uint16_t panel_res_y,
               int8_t panel_chain);

        void testDrawWeatherIcons();
        void drawInitializationPage(uint8_t loadingBarWidthPixels);
        void drawVickyCommutePage(RouteGroupData& data, WeatherData& weatherData, const char* currentTime);
        void drawBusSchedulePage(RouteGroupData& data, RouteGroupType tripsType, const char* currentTime);
        void drawWeatherPage(WeatherData& weatherData, const char* currentTime, const char* currentDateShort);
        void drawSleepingPage();

        void drawClock(const char* currentTime);
        void drawPageBar(float percentComplete);

        void setBrightness(uint8_t brightnessStep);
        void clearScreen();
    private:
        MatrixPanel_I2S_DMA *_dma_display = nullptr;
        uint16_t _colorBlack = _dma_display->color565(0, 0, 0);
        uint16_t _colorWhite = _dma_display->color565(255, 255, 255);
        uint16_t _colorRed = _dma_display->color565(COLOR_RED_R, COLOR_RED_G, COLOR_RED_B);
        uint16_t _colorGreen = _dma_display->color565(COLOR_GREEN_R, COLOR_GREEN_G, COLOR_GREEN_B);
        uint16_t _colorTextPrimary = _dma_display->color565(COLOR_TEXT_PRIMARY_R, COLOR_TEXT_PRIMARY_G, COLOR_TEXT_PRIMARY_B);
        uint16_t _colorTextSecondary = _dma_display->color565(COLOR_TEXT_SECONDARY_R, COLOR_TEXT_SECONDARY_G, COLOR_TEXT_SECONDARY_B);
        uint16_t _colorTextRoute = _dma_display->color565(COLOR_TEXT_ROUTE_R, COLOR_TEXT_ROUTE_G, COLOR_TEXT_ROUTE_B);
        uint16_t _colorRouteFrequent = _dma_display->color565(COLOR_ROUTE_FREQUENT_R, COLOR_ROUTE_FREQUENT_G, COLOR_ROUTE_FREQUENT_B);
        uint16_t _colorRouteLocal = _dma_display->color565(COLOR_ROUTE_LOCAL_R, COLOR_ROUTE_LOCAL_G, COLOR_ROUTE_LOCAL_B);

        uint16_t _colorLow = _dma_display->color565(152, 217, 47);
        uint16_t _colorModerate = _dma_display->color565(255, 207, 65);
        uint16_t _colorHigh = _dma_display->color565(233, 136, 25);
        uint16_t _colorVeryHigh = _dma_display->color565(222, 61, 43);
        uint16_t _colorExtreme = _dma_display->color565(146, 93, 198);
        uint16_t _colorHazardous = _dma_display->color565(102, 37, 28);
        
        std::vector<std::tuple<uint8_t, uint8_t, bool>> _trackingBusIndicatorPositions;
        TaskHandle_t trackingBusIndicatorTaskHandle = NULL;
        static void TrackingBusIndicatorTaskFunction(void *pvParameters);

        WeatherData _extraWeatherData;
        TaskHandle_t extraWeatherDataTaskHandle = NULL;
        static void ExtraWeatherDataTaskFunction(void *pvParameters);
        static void ExtraWeatherDataVickyCommuteTaskFunction(void *pvParameters);

        TaskHandle_t sleepingAnimationTaskHandle = NULL;
        static void SleepingAnimationTaskFunction(void *pvParameters);
        TaskHandle_t sleepingAnimationTaskHandle2 = NULL;
        static void SleepingAnimationTaskFunction2(void *pvParameters);

        uint8_t _panelBrightness = 20;
        uint8_t _targetBrightness = 20;
        TaskHandle_t brightnessTaskHandle = NULL;
        static void BrightnessTaskFunction(void *pvParameters);
        
        void drawPixel(uint8_t x, uint8_t y);
        void drawText(uint8_t x, uint8_t y, const char* text);
        void drawText(uint8_t x, uint8_t y, const char* text, uint16_t color, const GFXfont *f);
        uint8_t drawCenteredText(uint8_t x, uint8_t y, const char* text);
        uint8_t drawCenteredText(uint8_t x, uint8_t y, const char* text, uint16_t color, const GFXfont *f);
        uint8_t drawTextEnd(uint8_t x, uint8_t y, const char* text);
        uint8_t drawTextEnd(uint8_t x, uint8_t y, const char* text, uint16_t color, const GFXfont *f);
        void drawRouteSign(RouteType type, uint8_t x, uint8_t y, uint8_t width, const char* text);
        void drawMinuteSymbol(uint8_t x, uint8_t y);
        void drawVerticalBar(uint8_t x, uint8_t y, uint8_t width, uint8_t fullHeight, uint8_t barHeight, uint16_t colorBar);
        void drawASCWWImage(int x, int y, int width, int height, const char* imageArray); // ASCWW = ArduinoSmartClockWithWeather

        String shortenRouteDestination(const String& label);
        uint8_t getTextWidth(const char *str);
        uint8_t getTextWidth(const char *str, const GFXfont *f);
        uint8_t getRightAlignStartingPoint(const char* str, int8_t xPosition);
        void fadeOutScreen();
        void fadeInScreen();
        static uint16_t colorWithIntensity(MatrixPanel_I2S_DMA* dma_display, uint8_t r, uint8_t g, uint8_t b, float fraction);
        uint16_t colorForUVIndex(uint8_t UVIndex);
        uint8_t barHeightForUVIndex(uint8_t UVIndex);
        uint16_t colorForAQI(uint16_t AQI);
        uint8_t barHeightForAQI(uint16_t AQI);
};
#endif