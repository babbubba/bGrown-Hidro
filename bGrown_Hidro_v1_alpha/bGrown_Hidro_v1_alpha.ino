#include "relay_module.h"
#include "ph_sensor.h"

// 4 Relay 10A Module (used for 12V peristaltic pumps)
#define Relay_01_c01_Pin 23 // [ch_PhPlus]    Define the Relay Module 1 Channel 1 pin (10A) 
#define Relay_01_c02_Pin 21 // [ch_PhPMinus]  Define the Relay Module 1 Channel 2 pin (10A)
#define Relay_01_c03_Pin 19 //                Define the Relay Module 1 Channel 3 pin (10A)
#define Relay_01_c04_Pin 18 //                Define the Relay Module 1 Channel 4 pin (10A)

// 1 Relay 30A Module used for high voltage inductive load (like a thermo ventilator)
#define Relay_02_c01_Pin 22 // Define the Relay Module 2 Channel 1 pin (30A)

// 2 Relay 30A Module used for high voltage inductive load (like a thermo ventilator)
#define Relay_03_c01_Pin 14 // Define the Relay Module 3 Channel 1 pin (30A)
#define Relay_03_c02_Pin 13 // Define the Relay Module 3 Channel 2 pin (30A)

// PH Sensor Analog Data In
#define PhSensor_analog_data_pin 34



//RelayModule RelaysIntance; //= RelayModule(channels);
RelayChannel ch_PhPlus = RelayChannel(1, Relay_01_c01_Pin, true);
RelayChannel ch_PhMinus = RelayChannel(2, Relay_01_c02_Pin, true);

PhSensor PhSensorInstance = PhSensor(PhSensor_analog_data_pin);
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
  PhSensorInstance = PhSensor(PhSensor_analog_data_pin);
  PhSensorInstance.Init();
}

void loop()
{

  float ph = PhSensorInstance.GetPH();
  if(ph > 6.4) {
    ch_PhMinus.TurnOn();
  } else {
    ch_PhMinus.TurnOff();
  }

 if(ph < 5.0) {
    ch_PhPlus.TurnOn();
  } else {
    ch_PhPlus.TurnOff();
  }


  delay(2000);
  // RelaysIntance.SetRelayStatus(1,true);
  // delay(2000);
  // RelaysIntance.SetRelayStatus(2,true);
  // delay(1000);
  // RelaysIntance.SetRelayStatus(5,true);
  // delay(10000);
  // RelaysIntance.SetRelayStatus(1,false);
  // delay(2000);
  // RelaysIntance.SetRelayStatus(2,false);
  // delay(1000);
  // RelaysIntance.SetRelayStatus(5,false);
  // delay(10000);
}
