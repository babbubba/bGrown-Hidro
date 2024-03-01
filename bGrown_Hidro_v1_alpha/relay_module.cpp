#include "relay_module.h"
#include "relay_channel.h"
#include <Arduino.h>
RelayModule::RelayModule()
{
    _lastIndex = 0;
}
RelayModule::RelayModule(RelayChannel channels[])
{
    _lastIndex = 0;
  for(int i=0;i<sizeof(channels);i++) {
    AddRelay(channels[i]);
    } 
  
}

bool RelayModule::AddRelay(RelayChannel channel)
{
    if (_lastIndex >= _relaysSize)
        return false;

    _lastIndex += 1;
    *_relays[_lastIndex] = channel;
    return true;
}

RelayChannel* RelayModule::GetRelay(int channel)
{
    if (!_initialized) return NULL;

    for (int i = 0; i < _lastIndex; i++)
    {
        if (channel = _relays[i]->_channel)
        {
            return _relays[i];
        }
    }
}

bool RelayModule::GetRelayStatus(int channel)
{
    return GetRelay(channel)->Status();
}

bool RelayModule::SetRelayStatus(int channel, bool newStatus)
{
    if (!_initialized)
        return false;

    RelayChannel *ch = GetRelay(channel);
    if(ch=NULL) return false;
    newStatus ? ch->TurnOn() : ch->TurnOff();
    return true;
}

bool RelayModule::InitRelays()
{
    if (_initialized)
        return false;
    for (int i = 0; i < _lastIndex; i++)
    {
        _relays[i]->Init();
    }
    _initialized = true;
    return true;
}
