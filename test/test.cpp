#include <unity.h>
#include <weabther.h>

#define DHTPIN 45
#define DHTTYPE DHT22

sensors_event_t event;

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_function_should_readTemperature(void)
{
    float temperature = readTemperature(&event);
    TEST_ASSERT_FLOAT_WITHIN(20.0, 20.0, temperature);
}

void test_function_should_readHumidity(void)
{
    float humidity = readHumidity(&event);
    TEST_ASSERT_FLOAT_WITHIN(30.0, 70.0, humidity);
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_function_should_readTemperature);
    RUN_TEST(test_function_should_readHumidity);
    return UNITY_END();
}

void setup()
{
    delay(2000);
    Serial.begin(115200);
    DHTSetup();;
    runUnityTests();
}

void loop()
{
}