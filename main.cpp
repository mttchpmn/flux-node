#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>

// JSON parsing setup
const int capacity = JSON_OBJECT_SIZE(10); // 8 refers to number of properties on object

// LED Setup
const int LED_PIN = 7;
const int NUM_PIXELS = 14;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Button Setup
const int BUTTON_PIN = 5;
int buttonState = 0;
int counter = 0;
int counterMax = 5;

void setup()
{
    Serial.begin(9600);
    Serial.println("Initialising...");

    // Set up pushbutton pin
    pinMode(BUTTON_PIN, INPUT);

    // Instantiate LED strip
    strip.begin();
    strip.show();
}

void loop()
{
    // Check connection to API - THIS IS WHERE HTTP GET LOGIC WILL GO
    bool apiConnected = true;

    // CONNECTED TO API - USE DATA FROM API //////////////////////////////////////////////////////////////////////////////////////////////////
    while (apiConnected)
    {
        // Compute bytes required for JSON buffer based on number of properties in object
        StaticJsonBuffer<capacity> jb;

        // Example string that would be recieved from API
        char input[] = "{\"id\":\"KIT888\",\"state\":\"1\",\"name\":\"Dining\",\"r0\":\"180\",\"g0\":30,\"b0\":200,\"pattern\":\"breathe\",\"brightness\":\"200\",\"delay\":\"1000\"}";

        // Parse JSON input string into JsonObject called obj
        JsonObject &obj = jb.parseObject(input);

        // Check result of JSON parsing
        if (obj.success())
        {
            Serial.println("JSONParsing successful");
        }
        else
        {
            Serial.println("Parsing failed");
        }

        // Extract values from JSON object
        const char *id = obj["id"];
        int state = obj["state"];
        const char *name = obj["name"];
        int r0 = obj["r0"];
        int g0 = obj["g0"];
        int b0 = obj["b0"];
        const char *pattern = obj["pattern"];
        int bright = obj["brightness"];
        int delayTime = obj["delay"];

        // Print values to serial monitor
        Serial.println("#########################\nDECODED DATA: \n");
        Serial.print("ID: ");
        Serial.println(id);
        Serial.print("State: ");
        Serial.println(state);
        Serial.print("Name: ");
        Serial.println(name);
        Serial.print("R0: ");
        Serial.println(r0);
        Serial.print("G0: ");
        Serial.println(g0);
        Serial.print("B0: ");
        Serial.println(b0);
        Serial.print("Pattern: ");
        Serial.println(pattern);
        Serial.print("Brightness: ");
        Serial.println(bright);
        Serial.print("Delay: ");
        Serial.println(delayTime);
        Serial.println("#########################\n");

        // Check if strip should be powered on.  0 = off, 1 = on
        if (state == 1)
        {
            staticColor(r0, g0, b0, bright);
        }

        // Wait for 3 sec
        delay(3000);
    }

    // NOT CONNECTED TO API - USE BUTTON /////////////////////////////////////////////////////////////////////////////////////////////////////

    // Set logical value for brightness
    int bright = 180;

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
    delay(3000);
} // END OF LOOP FUNCTION

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
    }
    strip.show();
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
