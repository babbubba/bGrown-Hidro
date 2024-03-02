// #include "relay_module.h"
#include "ph_sensor.h"

// 4 Relay 10A Module (used for 12V peristaltic pumps)
#define Relay_01_c01_Pin 23 // Define the Relay Module 1 Channel 1 pin (10A)
#define Relay_01_c02_Pin 21 // Define the Relay Module 1 Channel 2 pin (10A)
#define Relay_01_c03_Pin 19 // Define the Relay Module 1 Channel 3 pin (10A)
#define Relay_01_c04_Pin 18 // Define the Relay Module 1 Channel 4 pin (10A)

// 1 Relay 30A Module used for high voltage inductive load (like a thermo ventilator)
#define Relay_02_c01_Pin 22 // Define the Relay Module 2 Channel 1 pin (30A)

// 2 Relay 30A Module used for high voltage inductive load (like a thermo ventilator)
#define Relay_03_c01_Pin 14 // Define the Relay Module 3 Channel 1 pin (30A)
#define Relay_03_c02_Pin 13 // Define the Relay Module 3 Channel 2 pin (30A)

// PH Sensor Analog Data In
#define PhSensor_analog_data_pin 34

// RelayChannel channels[] = {
//     RelayChannel(1, Relay_01_c01_Pin, true),
//     RelayChannel(2, Relay_01_c02_Pin, true),
//     RelayChannel(3, Relay_01_c03_Pin, true),
//     RelayChannel(4, Relay_01_c04_Pin, true),
//     RelayChannel(5, Relay_02_c01_Pin),
//     RelayChannel(6, Relay_03_c01_Pin),
//     RelayChannel(7, Relay_03_c02_Pin)};

// RelayModule Relays = RelayModule(channels);

float calibration_value = 22.34 - 0.3;
float phval = 0;
unsigned long int valuesSum;
int buffer_arr[10], temp;
float convert_ratio;

int pH_Value;
float Voltage;

float interpolate(float voltTointerpolate, float releavedVolt, float voltLimit, float releavedPH, float beginPH)
{
  return releavedPH + (beginPH - releavedPH) * ((voltTointerpolate - releavedVolt) / (voltLimit - releavedVolt));
}

float GetPhInterpolated(float volt)
{
  // ESP32 Analog input is not linear... so to be more realistic I will use the next rilevations
  if (volt >= 3.25)
  {
    // case measured: PH 4.8 -> raw value 4030 -> 3.25V (linear computed) -> Effective lecture 3.09V
    return interpolate(volt, 3.25, 3.3, 4.8, 0);
  }
  else if (volt >= 3.09)
  {
    return interpolate(volt, 3.09, 3.25, 5.2, 4.8);
  }
  else if (volt >= 2.69)
  {
    return interpolate(volt, 2.69, 3.09, 6.5, 5.2);
  }
  else if (volt >= 2.35)
  {
    return interpolate(volt, 2.35, 2.69, 8.5, 6.5);
  }
  else // if (volt >= 2.32)
  {
    return interpolate(volt, 2.32, 2.35, 8.7, 8.5);
  }
  // else
  // {
  //   return 14; // Gestione degli altri casi, se necessario
  // }
}

PhSensor phSensor = PhSensor(PhSensor_analog_data_pin);
void setup()
{
  Serial.begin(115200);
  phSensor.Init();
  // pinMode(PhSensor_analog_data_pin, INPUT);
  // analogSetWidth(12);                           // 10Bit resolution
  // analogSetAttenuation((adc_attenuation_t)PhSensor_analog_data_pin);   // -6dB range

  // analogSetPinAttenuation(PhSensor_analog_data_pin, ADC_0db);

  // Serial.print("Initializing relays... ");
  // Serial.println(Relays.InitRelays());
}

void loop()
{
  Serial.print("PH: ");
  Serial.println(phSensor.GetPH());
  delay(2000);

  // pH_Value = analogRead(PhSensor_analog_data_pin);
  // Serial.println(pH_Value);
  // Voltage = pH_Value * (3.3 / 1023.0);
  // Serial.println(Voltage);
  // //Serial.println("c");
  // delay(1500);
  // Relays.SetRelayStatus(1,true);
  // delay(2000);
  // Relays.SetRelayStatus(2,true);
  // delay(1000);
  // Relays.SetRelayStatus(5,true);
  // delay(10000);
  // Relays.SetRelayStatus(1,false);
  // delay(2000);
  // Relays.SetRelayStatus(2,false);
  // delay(1000);
  // Relays.SetRelayStatus(5,false);
  // delay(10000);
}
