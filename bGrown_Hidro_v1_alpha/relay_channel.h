#ifndef relay_channel_h
#define relay_channel_h

#include <Arduino.h>

class RelayChannel
{
private:
  int _pin;
  bool _reverse;
  char _label[12];
  bool _active;
  void PrintChangeStatus(bool);

public:
  int _channel;
  RelayChannel();
  RelayChannel(int, int);
  RelayChannel(int, int, bool);
  
  void Init();
  bool Status();
  void TurnOn();
  void TurnOff();
  void Toggle();
};

#endif
