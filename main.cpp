#include <Adafruit_NeoPixel.h>

// LED Setup
const int LED_PIN = 7;
const int NUM_PIXELS = 14;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Button Setup
const int BUTTON_PIN = 5;
int buttonState = 0;
int counter = 0;
int counterMax = 5;

// Mock web data setup
int bright = 90;

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
        delay(1000);
    }

    // Switch lights based on button
    switch (counter)
    {
    case 0:
        staticColor(255, 0, 0, bright);
        break;
    case 1:
        colorWipe(0, 255, 0, bright, 50);
        break;
    case 2:
        staticColor(0, 0, 255, bright);
        break;
    case 3:
        staticColor(180, 0, 180, bright);
        break;
    case 4:
        staticColor(0, 180, 180, bright);
        break;
    case 5:
        staticColor(180, 180, 0, bright);
        break;
    }
    delay(100);
}

// LED PATTERN FUNCTIONS
void setColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint16_t brightness)
{
    strip.setPixelColor(n, strip.Color((brightness * r / 255), (brightness * g / 255), (brightness * b / 255)));
}

void staticColor(int r, int g, int b, int bright)
{
    strip.begin();
    strip.show();
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        setColor(i, r, g, b, bright);
        strip.show();
    }
}

void colorWipe(int r, int g, int b, int bright, int wait)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        setColor(i, r, g, b, bright);
        strip.show();
        delay(wait);
    }
}

void flash(int r, int g, int b, int bright, int wait)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        setColor(i, r, g, b, bright);
    }
    strip.show();
    delay(wait * 2);
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        setColor(i, 0, 0, 0, bright);
    }
    strip.show();
    delay(wait);
}
