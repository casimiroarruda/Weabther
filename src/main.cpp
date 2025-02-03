#include <Arduino.h>
#include <heltec.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>

#define DHTPIN 45
#define DHTTYPE DHT22 // DHT 22 (AM2302)
DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

static SSD1306Wire display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED); // addr , freq , i2c group , resolution , rst

void DHTSetup()
{
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
}

void OLEDSetup()
{
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.setBrightness(100);
}

void setup()
{
  Serial.begin(115200);
  DHTSetup();
  OLEDSetup();
}

void displayWeather(float temperature, float relative_humidity)
{
  char display_temperature[16];
  char display_humidity[16];
  sprintf(display_temperature,"Temp.: %.1f °C", temperature);
  sprintf(display_humidity,"HumR.: %.1f %%",relative_humidity);
  display.clear();
  display.drawString(0, 0, display_temperature);
  display.drawString(0, 18, display_humidity);
  display.display();
}

void displayError()
{
  display.clear();
  display.drawStringMaxWidth(0, 0, 128, "Error reading sensor.");
  display.display();
}

void loop()
{
  delay(delayMS);
  sensors_event_t event;
  int threshould = 0;
  float temperature = 0;
  float humidity = 0;
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature))
  {
    temperature = event.temperature;
    threshould++;
  }

  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity))
  {
    humidity = event.relative_humidity;
    threshould++;
  }

  (threshould == 0) ? displayError() : displayWeather(temperature, humidity);
}