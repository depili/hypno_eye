#ifndef hypno_eye_h
#define hypno_eye_h

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
  #include "pins_arduino.h"
#endif

#include <Adafruit_NeoPixel.h>

#define OUTER_LEDS 12
#define INNER_LEDS 6

class HypnoEye {
public:
	HypnoEye(uint8_t pin, uint8_t b);
	~HypnoEye();
	
	void setBrightness(uint8_t brighness);
	void setOuterLeds(uint32_t *leds);
	void setInnerLeds(uint32_t *leds);
	void setCenterLed(uint32_t led);
	void setAll(uint32_t color);
	void clear();
	
	void show();
	
	void rotateCW();
	void rotateCW(uint8_t steps);
	void rotateCCW();
	void rotateCCW(uint8_t steps);
	
private:
	Adafruit_NeoPixel strip;
	uint32_t outerLeds [OUTER_LEDS];
	uint32_t innerLeds [INNER_LEDS];
	uint32_t centerLed;
	uint8_t brightness;
	int8_t rotation;
};

#endif
