#include <hypno_eye.h>


HypnoEye::HypnoEye(uint8_t pin, uint8_t brightness) {
	strip = Adafruit_NeoPixel(19, pin, NEO_GRB + NEO_KHZ800);
	rotation = 0;
	for(uint8_t i = 0; i < OUTER_LEDS; ++i)
	{
		outerLeds[i] = strip.Color(0,0,0);
	}
	for(size_t i = 0; i < INNER_LEDS; ++i)
	{
		innerLeds[i] = strip.Color(0,0,0);
	}
	centerLed = HypnoEye::strip.Color(0,0,0);
	strip.begin();
	strip.setBrightness(brightness);
}

HypnoEye::~HypnoEye() {
	
}

void HypnoEye::setOuterLeds(uint32_t *leds) {
	for(size_t i = 0; i < OUTER_LEDS; ++i)
	{
		outerLeds[i] = leds[i];
	}
}

void HypnoEye::setInnerLeds(uint32_t *leds) {
	for(size_t i = 0; i < INNER_LEDS; ++i)
	{
		innerLeds[i] = leds[i];
	}
}

void HypnoEye::setCenterLed(uint32_t led) {
	centerLed = led;
}

void HypnoEye::show() {
	for(size_t i = 0; i < OUTER_LEDS; ++i)
	{
		strip.setPixelColor(i, outerLeds[(i + 11 + rotation) % OUTER_LEDS]); 
	}
	for(size_t i = 0; i < INNER_LEDS; ++i)
	{
		strip.setPixelColor((i+OUTER_LEDS+1), innerLeds[(i + 1 + (rotation/2)) % INNER_LEDS]);
	}
	strip.setPixelColor(OUTER_LEDS, centerLed);
	strip.show();
}

void HypnoEye::rotateCW() {
	rotation = (rotation + 1) % OUTER_LEDS;
}

void HypnoEye::rotateCW(uint8_t steps) {
	rotation = (rotation + steps) % OUTER_LEDS;
}

void HypnoEye::rotateCCW() {
	if (rotation == 0) {
		rotation = OUTER_LEDS - 1;
	} else {
		rotation -= 1;
	}
}

void HypnoEye::rotateCCW(uint8_t steps) {
	if (rotation < steps) {
		steps -= rotation;
		rotation = OUTER_LEDS - (steps % OUTER_LEDS);
	} else {
		rotation -= steps;
	}
}

void HypnoEye::clear() {
	uint32_t off = 0;
	this->setAll(off);
}

void HypnoEye::setAll(uint32_t color) {
	centerLed = color;
	for(size_t i = 0; i < INNER_LEDS; ++i)
	{
		innerLeds[i] = color;
	}
	for(size_t i = 0; i < OUTER_LEDS; ++i)
	{
		outerLeds[i] = color;
	}
}
