#include <Adafruit_NeoPixel.h>

// LED Setup
const int LED_PIN = 7;
const int NUM_PIXELS = 12;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Button Setup
const int BUTTON_PIN = 5;
int buttonState = 0;
int counter = 0;
int counterMax = 3;

// Mock web data setup
int brightnessFactor = 90;

void setup()
{
    Serial.begin(9600);
    Serial.println("Initialising...");
    Serial.print("Counter: ");
    Serial.println(counter);

    pinMode(BUTTON_PIN, INPUT);

    strip.begin();
    strip.show();
}

void loop()
{
    // Catch button press
    buttonState = digitalRead(BUTTON_PIN);
    if (buttonState == HIGH)
    {
        Serial.println("Button Pressed");
        if (counter != counterMax)
        {
            counter++;
        }
        else
        {
            counter = 0;
        }
        Serial.print("Counter is now: ");
        Serial.println(counter);
    }

    // Switch lights based on button
    switch (counter)
    {
    case 0:
        staticColor(255, 0, 0, brightnessFactor);
        break;
    case 1:
        colorWipe(0, 255, 0, brightnessFactor, 50);
        break;
    case 2:
        flash(0, 0, 255, brightnessFactor, 1000);
        break;
    case 3:
        colorWipe(180, 0, 180, brightnessFactor, 100);
        break;
    }
    delay(100);
}

// LED PATTERN FUNCTIONS
void setColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint16_t brightness)
{
    strip.setPixelColor(n, strip.Color((brightness * r / 255), (brightness * g / 255), (brightness * b / 255)));
}

void staticColor(int r, int g, int b, int brightnessFactor)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        setColor(i, r, g, b, brightnessFactor);
        strip.show();
    }
}

void flash(int r, int g, int b, int brightnessFactor, int wait)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        setColor(i, r, g, b, brightnessFactor);
        strip.show();
    }
    delay(wait * 2);
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        setColor(i, 0, 0, 0, brightnessFactor);
        strip.show();
    }
    delay(wait);
}

void colorWipe(int r, int g, int b, int brightnessFactor, int wait)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        setColor(i, r, g, b, brightnessFactor);
        strip.show();
        delay(wait);
    }
}