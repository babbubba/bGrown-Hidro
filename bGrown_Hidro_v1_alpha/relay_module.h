#ifndef relay_module_h
#define relay_module_h

#include "relay_channel.h"
#include <Arduino.h>

class RelayModule
{
private:
  static const int _relaysSize = 32;
  int _lastIndex;
  bool _initialized = false;
  RelayChannel *_relays[_relaysSize];

public:
  RelayModule();
  RelayModule(RelayChannel[]);
  bool AddRelay(RelayChannel);
  RelayChannel* GetRelay(int);
  bool GetRelayStatus(int);
  bool SetRelayStatus(int, bool);
  bool InitRelays();
};

#endif
