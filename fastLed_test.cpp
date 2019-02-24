#include <FastLED.h>

#define LED_PIN 7
#define NUM_LEDS 14
#define BRIGHTNESS 200
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

// SETUP ///////////////////////////////////////////////
void setup()
{
    delay(3000); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
}

// LOOP ///////////////////////////////////////////////
void loop()
{
    // Breathe(0xff, 0x00, 0x00);
    //Static(94, 209, 94);
    // Sparkle3(0, 180, 255);
    // Stripe(0, 180, 230);
    // Wave(100, 0, 100);
    // Wave2(100, 0, 100);
    Rainbow();
}

void showStrip()
{
    FastLED.show();
}

// UTILITY FUNCTIONS ///////////////////////////////////////////////
void setPixel(int Pixel, byte red, byte green, byte blue)
{
    leds[Pixel].r = red;
    leds[Pixel].g = green;
    leds[Pixel].b = blue;
}

void setAll(byte red, byte green, byte blue)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        setPixel(i, red, green, blue);
    }
    showStrip();
}

// PATTERN FUNCTIONS ///////////////////////////////////////////////
void Static(byte red, byte green, byte blue)
{
    setAll(red, green, blue);
}

void Breathe(byte red, byte green, byte blue)
{
    float r, g, b;

    for (int k = 0; k < 256; k = k + 1)
    {
        r = (k / 256.0) * red;
        g = (k / 256.0) * green;
        b = (k / 256.0) * blue;

        setAll(r, g, b);
        showStrip();
        if (k < 50)
        {
            delay(30);
        }
        if (k > 50 && k < 150)
        {
            delay(7);
        }
        if (k > 150)
        {
            delay(3);
        }
    }

    for (int k = 255; k > 0; k--)
    {
        r = (k / 256.0) * red;
        g = (k / 256.0) * green;
        b = (k / 256.0) * blue;

        setAll(r, g, b);
        showStrip();
        if (k < 50)
        {
            delay(30);
        }
        if (k > 50 && k < 150)
        {
            delay(7);
        }
        if (k > 150)
        {
            delay(3);
        }
    }
}

void Sparkle1(byte red, byte green, byte blue)
{
    int Pixel = random(NUM_LEDS);
    setPixel(Pixel, red, green, blue);
    showStrip();
    delay(75);
    setPixel(Pixel, 0, 0, 0);
}

void Sparkle3(byte red, byte green, byte blue)
{
    int Pixel1 = random(NUM_LEDS);
    int Pixel2 = random(NUM_LEDS);
    int Pixel3 = random(NUM_LEDS);

    setPixel(Pixel1, red, green, blue);
    setPixel(Pixel2, red, green, blue);
    setPixel(Pixel3, red, green, blue);
    showStrip();
    delay(100);
    setPixel(Pixel1, 0, 0, 0);
    setPixel(Pixel2, 0, 0, 0);
    setPixel(Pixel3, 0, 0, 0);
}

void Sparkle5(byte red, byte green, byte blue)
{
    int Pixel1 = random(NUM_LEDS);
    int Pixel2 = random(NUM_LEDS);
    int Pixel3 = random(NUM_LEDS);
    int Pixel4 = random(NUM_LEDS);
    int Pixel5 = random(NUM_LEDS);

    setPixel(Pixel1, red, green, blue);
    setPixel(Pixel2, red, green, blue);
    setPixel(Pixel3, red, green, blue);
    setPixel(Pixel4, red, green, blue);
    setPixel(Pixel5, red, green, blue);
    showStrip();
    delay(150);
    setPixel(Pixel1, 0, 0, 0);
    setPixel(Pixel2, 0, 0, 0);
    setPixel(Pixel3, 0, 0, 0);
    setPixel(Pixel4, 0, 0, 0);
    setPixel(Pixel5, 0, 0, 0);
}

void Stripe(byte red, byte green, byte blue)
{
    for (int i = 0; i <= NUM_LEDS; i++)
    {
        setPixel(i, red, green, blue);
        setPixel(NUM_LEDS - i, red, green, blue);

        showStrip();
        delay(75);
        setPixel(i, 0, 0, 0);
        setPixel(NUM_LEDS - i, 0, 0, 0);
    }
}

void Wave(byte red, byte green, byte blue)
{
    for (int i = 0; i <= NUM_LEDS; i++)
    {
        setPixel(i, red, green, blue);
        showStrip();
        delay(150);
    }
    setAll(0, 0, 0);
    for (int i = 0; i <= NUM_LEDS; i++)
    {
        setPixel(NUM_LEDS - i, red, green, blue);
        showStrip();
        delay(150);
    }
    setAll(0, 0, 0);
}

void Wave2(byte red, byte green, byte blue)
{
    for (int i = 0; i <= NUM_LEDS; i++)
    {
        setPixel(i, red, green, blue);
        showStrip();
        delay(150);
    }
    for (int i = 0; i <= NUM_LEDS; i++)
    {
        setPixel(NUM_LEDS - i, 0, 0, 0);
        showStrip();
        delay(150);
    }
}

void Rainbow()
{
    byte *c;
    uint16_t i, j;

    for (j = 0; j < 256 * 5; j++)
    { // 5 cycles of all colors on wheel
        for (i = 0; i < NUM_LEDS; i++)
        {
            c = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
            setPixel(i, *c, *(c + 1), *(c + 2));
        }
        showStrip();
        delay(20);
    }
}

byte *Wheel(byte WheelPos)
{
    static byte c[3];

    if (WheelPos < 85)
    {
        c[0] = WheelPos * 3;
        c[1] = 255 - WheelPos * 3;
        c[2] = 0;
    }
    else if (WheelPos < 170)
    {
        WheelPos -= 85;
        c[0] = 255 - WheelPos * 3;
        c[1] = 0;
        c[2] = WheelPos * 3;
    }
    else
    {
        WheelPos -= 170;
        c[0] = 0;
        c[1] = WheelPos * 3;
        c[2] = 255 - WheelPos * 3;
    }

    return c;
}
