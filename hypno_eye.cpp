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
	rotation = (rotation + 1) % 12;
}

void HypnoEye::rotateCCW() {
	if (rotation == 0) {
		rotation = 11;
	} else {
		rotation = (rotation - 1) % 12;
	}
}

void HypnoEye::clear() {
	strip.clear();
}

void HypnoEye::setAll(uint32_t color) {
	for(size_t i = 0; i < OUTER_LEDS + INNER_LEDS + 1; ++i)
	{
		strip.setPixelColor(i, color);
	}
}
