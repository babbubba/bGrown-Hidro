#include "relay_module.h"

// 4 Relay 10A Module (used for 12V peristaltic pumps)
#define Relay_01_c01_Pin 23 // Define the Relay Module 1 Channel 1 pin (10A)
#define Relay_01_c02_Pin 21 // Define the Relay Module 1 Channel 2 pin (10A)
#define Relay_01_c03_Pin 19  // Define the Relay Module 1 Channel 3 pin (10A)
#define Relay_01_c04_Pin 18  // Define the Relay Module 1 Channel 4 pin (10A)

// 1 Relay 30A Module used for high voltage inductive load (like a thermo ventilator)
#define Relay_02_c01_Pin 22 // Define the Relay Module 2 Channel 1 pin (30A)

// 2 Relay 30A Module used for high voltage inductive load (like a thermo ventilator)
#define Relay_03_c01_Pin 14 // Define the Relay Module 3 Channel 1 pin (30A)
#define Relay_03_c01_Pin 13 // Define the Relay Module 3 Channel 2 pin (30A)

RelayChannel channels[] = {
    RelayChannel(1, Relay_01_c01_Pin, true),
    RelayChannel(2, Relay_01_c02_Pin, true),
    RelayChannel(3, Relay_01_c03_Pin, true),
    RelayChannel(4, Relay_01_c04_Pin, true),
    RelayChannel(5, Relay_02_c01_Pin),
    RelayChannel(6, Relay_03_c01_Pin),
    RelayChannel(7, Relay_03_c01_Pin)};

RelayModule Relays = RelayModule(channels);

void setup()
{
  Serial.begin(115200);
  Serial.print("Initializing relays... ");
  Serial.println(Relays.InitRelays());
}

void loop()
{
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
