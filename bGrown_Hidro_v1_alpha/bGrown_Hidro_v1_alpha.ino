// #include "relay_module.h"
#include "relay_channel.h"
#include "ph_sensor.h"
#include "tds_sensor.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"


// 4 Relay 10A Module (used for 12V peristaltic pumps)
#define Relay_01_c01_Pin 23 // [ch_PhPMinus]    Define the Relay Module 1 Channel 1 pin (10A)
#define Relay_01_c02_Pin 21 // [ch_PhPlus]      Define the Relay Module 1 Channel 2 pin (10A)
#define Relay_01_c03_Pin 19 //                  Define the Relay Module 1 Channel 3 pin (10A)
#define Relay_01_c04_Pin 18 //                  Define the Relay Module 1 Channel 4 pin (10A)

// 1 Relay 30A Module used for high voltage inductive load (like a thermo ventilator)
#define Relay_02_c01_Pin 22 // Define the Relay Module 2 Channel 1 pin (30A)

// 2 Relay 30A Module used for high voltage inductive load (like a thermo ventilator)
#define Relay_03_c01_Pin 14 // Define the Relay Module 3 Channel 1 pin (30A)
#define Relay_03_c02_Pin 13 // Define the Relay Module 3 Channel 2 pin (30A)

// PH Sensor Analog Data In
#define PhSensor_analog_data_pin 34
#define TDSSensor_analog_data_pin 35
//const static int PhSensor_analog_data_pin = 34;

// RelayModule RelaysIntance; //= RelayModule(channels);
RelayChannel ch_PhMinus = RelayChannel(1, Relay_01_c01_Pin, true);
RelayChannel ch_PhPlus = RelayChannel(2, Relay_01_c02_Pin, true);

PhSensor PhSensorInstance = PhSensor(PhSensor_analog_data_pin);

TDSSensor TDSSensorInstance = TDSSensor();

AsyncWebServer server(80);
const char *ssid = "bHome.Wifi";
const char *password = "0EvItyr6mSIFP1FpIDMuwWqb";
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "application/json", "{\"message\":\"Not found\"}");
}

// The PH average
void setup()
{
  Serial.begin(115200);
  // RelayChannel channels[] = {
  //   RelayChannel(3, Relay_01_c03_Pin, true),
  //   RelayChannel(4, Relay_01_c04_Pin, true),
  //   RelayChannel(5, Relay_02_c01_Pin),
  //   RelayChannel(6, Relay_03_c01_Pin),
  //   RelayChannel(7, Relay_03_c02_Pin)};
  // RelaysIntance = RelayModule(channels);
  ch_PhPlus.Init();
  ch_PhMinus.Init();
  // PhSensorInstance = PhSensor(PhSensor_analog_data_pin);
  PhSensorInstance.Init();
  TDSSensorInstance.Init(TDSSensor_analog_data_pin);

  // Set WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.printf("WiFi Failed!\n");
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { 
    // response->addHeader("Access-Control-Allow-Origin", "http://localhost:4200");
    request->send(200, "application/json", "{\"message\":\"Welcome\"}"); });
  server.on("/ph", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    float currentPh = PhSensorInstance.GetPH();
    float currentPhAvg = PhSensorInstance.GetPHAverage();
    StaticJsonDocument<100> data;
    data["ph"] = currentPh;
    data["phAvg"] = currentPhAvg;
    String response;
    serializeJson(data, response);
    // request->addHeader("Access-Control-Allow-Origin", "http://localhost:4200");
    request->send(200, "application/json", response); });
  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    StaticJsonDocument<100> data;
    float currentPh = PhSensorInstance.GetPH();
    float currentPhAvg = PhSensorInstance.GetPHAverage();
    data["ph"] = currentPh;
    data["phAvg"] = currentPhAvg;
    JsonArray channels = data.createNestedArray("channels");
    JsonObject nested = channels.createNestedObject();
    nested["active"] = ch_PhMinus.Status();
    nested["label"] = "ch_PhMinus";
    nested["gpio"] = Relay_01_c02_Pin;
    nested["channel"] = ch_PhMinus._channel;
    JsonObject nested2 = channels.createNestedObject();
    nested2["active"] = ch_PhPlus.Status();
    nested2["label"] = "ch_PhPlus";
    nested2["gpio"] = Relay_01_c01_Pin;
    nested2["channel"] = ch_PhPlus._channel;

    String response;
    serializeJson(data, response);
    // request->addHeader("Access-Control-Allow-Origin", "http://localhost:4200");
    request->send(200, "application/json", response); });
  server.on("/get-message", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    StaticJsonDocument<100> data;
    if (request->hasParam("message"))
    {
      data["message"] = request->getParam("message")->value();
    }
    else
    {
      data["message"] = "No message parameter";
    }
    String response;
    serializeJson(data, response);
    request->send(200, "application/json", response); });
  AsyncCallbackJsonWebHandler *handler = new AsyncCallbackJsonWebHandler("/post-message", [](AsyncWebServerRequest *request, JsonVariant &json)
                                                                         {
    StaticJsonDocument<200> data;
    if (json.is<JsonArray>())
    {
      data = json.as<JsonArray>();
    }
    else if (json.is<JsonObject>())
    {
      data = json.as<JsonObject>();
    }
    String response;
    serializeJson(data, response);
    request->send(200, "application/json", response);
    Serial.println(response); });
  server.addHandler(handler);
  server.onNotFound(notFound);
  server.begin();
}

void loop()
{

  float currentPh = PhSensorInstance.GetPH();
  if (currentPh > 6.4)
  {
    ch_PhMinus.TurnOn();
  }
  else
  {
    ch_PhMinus.TurnOff();
  }

  if (currentPh < 5.0)
  {
    ch_PhPlus.TurnOn();
  }
  else
  {
    ch_PhPlus.TurnOff();
  }

  delay(2000);
}
