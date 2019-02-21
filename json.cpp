#include <ArduinoJson.h>

const int capacity = JSON_OBJECT_SIZE(8);

void setup()
{
    // Instantiate serial monitor
    Serial.begin(9600);
    Serial.println("Initializing...");
}

void loop()
{
    // Compute bytes required for JSON buffer based on number of properties in object
    StaticJsonBuffer<capacity> jb;

    // Example string that would be recieved from API
    char input[] = "{\"id\":\"KIT888\",\"name\":\"Dining\",\"color0\":\"#22ad40\",\"color1\":null,\"color2\":null,\"pattern\":\"breathe\",\"delay\":\"1000\"}";

    // Parse JSON input string into JsonObject called obj
    JsonObject &obj = jb.parseObject(input);

    // Check result of JSON parsing
    if (obj.success())
    {
        Serial.println("Parsing successful");
    }
    else
    {
        Serial.println("Parsing failed");
    }

    // Extract values from JSON object
    const char *id = obj["id"];
    const char *name = obj["name"];
    const char *color0 = obj["color0"];
    const char *color1 = obj["color1"];
    const char *color2 = obj["color2"];
    const char *pattern = obj["pattern"];
    int delayTime = obj["delay"];

    // Print values to serial monitor
    Serial.println(id);
    Serial.println(name);
    Serial.println(color0);
    Serial.println(color1);
    Serial.println(color2);
    Serial.println(pattern);
    Serial.println(delayTime);

    delay(3000);
    delete jb;
    delete obj;
}