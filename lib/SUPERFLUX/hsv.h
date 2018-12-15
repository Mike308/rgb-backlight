#ifndef HSV_H 
#define HSV_H 
#include <Arduino.h>
class HSV{
    public:
        HSV();
        HSV(uint16_t hue, uint8_t saturation, uint8_t value);
        void setHue(uint16_t hue);
        void setSaturation(uint8_t saturation);
        void setValue(uint8_t value);
        uint16_t getHue();
        uint8_t getSaturation();
        uint8_t getValue();
    private:
        uint16_t hue;
        uint8_t saturation;
        uint8_t value;
};
#endif