#include "relays.h";

#define Relay_01_c01_Pin    23             // Define the Relay Module 1 Channel 1 pin (10A)
#define Relay_01_c02_Pin    21             // Define the Relay Module 1 Channel 2 pin (10A)
#define Relay_01_c03_Pin    0              // Define the Relay Module 1 Channel 3 pin (10A)
#define Relay_01_c04_Pin    0              // Define the Relay Module 1 Channel 4 pin (10A)

#define Relay_02_c01_Pin    22             // Define the Relay Module 2 Channle 1 pin (30A)

#define Relay_03_c01_Pin    0              // Define the Relay Module 3 Channle 1 pin (30A)
#define Relay_03_c01_Pin    0              // Define the Relay Module 3 Channle 2 pin (30A)

RelayChannel channel_01 = RelayChannel(1, Relay_01_c01_Pin, true);
RelayChannel channel_02 = RelayChannel(2, Relay_01_c02_Pin, true);
RelayChannel channel_05 = RelayChannel(5, Relay_02_c01_Pin);

void setup() {
  Serial.begin(115200);
  channel_01.Init();
  channel_02.Init();
  channel_05.Init();
}

void loop() {
  channel_01.TurnOn();
  delay(2500);
  channel_02.TurnOn();
  delay(1000);
  channel_05.TurnOn();
  delay(10000);
  channel_01.TurnOff();
  delay(2500);
  channel_02.TurnOff();
  delay(1000);
  channel_05.TurnOff();
  delay(10000);
}
