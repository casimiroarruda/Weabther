#include <weabther.h>

void setup()
{
  Serial.begin(115200);
  DHTSetup();
  OLEDSetup();
}

void loop()
{
  delay(delayMS);
  sensors_event_t event;
  int threshould = 0;
  float temperature = 0;
  float humidity = 0;
  temperature = readTemperature(&event);
  humidity = readHumidity(&event);
  (temperature + humidity == 0) ? displayError() : displayWeather(temperature, humidity);
}