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
        setStaticColor(255, 0, 0);
        break;
    case 1:
        colorWipe(0, 255, 0, 50);
        break;
    case 2:
        flash(0, 0, 255, 1000);
        break;
    case 3:
        colorWipe(180, 0, 180, 100);
        break;
    }
    delay(100);
}

// LED PATTERN FUNCTIONS
void setStaticColor(int r, int g, int b)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        strip.setPixelColor(i, strip.Color(r, g, b));
        strip.show();
    }
}

void flash(int r, int g, int b, int delayTime)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        strip.setPixelColor(i, strip.Color(r, g, b));
        strip.show();
    }
    delay(delayTime * 2);
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
        strip.show();
    }
    delay(delayTime);
}

void colorWipe(int r, int g, int b, int wait)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        strip.setPixelColor(i, strip.Color(r, g, b));
        strip.show();
        delay(wait);
    }
}