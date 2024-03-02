#include "relay_module.h"
#include "relay_channel.h"
#include <Arduino.h>
RelayModule::RelayModule()
{
}
RelayModule::RelayModule(RelayChannel channels[])
{
    Serial.println("RelayModule ctor ");

    int channelsLenght = sizeof(channels) / sizeof(channels[0]);
    Serial.print("Addding ");
    Serial.print(channelsLenght);
    Serial.println(" channels...");
    for (int i = 0; i < channelsLenght; i++)
    {
        AddRelay(channels[i]);
    }
}

bool RelayModule::AddRelay(RelayChannel channel)
{
    Serial.println("AddRelay ");

    if (_lastIndex >= _relaysSize)
        return false;

    _lastIndex += 1;
    *_relays[_lastIndex] = channel;
    return true;
}

RelayChannel *RelayModule::GetRelay(int channel)
{
    Serial.println("Get Relay ");
    
    if (!_initialized)
        return NULL;

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
    Serial.print("GetStatusChannel");
    Serial.println(channel);
    return GetRelay(channel)->Status();
}

bool RelayModule::SetRelayStatus(int channel, bool newStatus)
{
    if (!_initialized)
        return false;

    RelayChannel *ch = GetRelay(channel);
    if (ch = NULL)
        return false;
    newStatus ? ch->TurnOn() : ch->TurnOff();
    return true;
}

bool RelayModule::Init()
{
    if (_initialized)
    {
        Serial.print("Relays already initialized!!!");
        return false;
    }
    Serial.print("Initializing relays[");
    Serial.print(_lastIndex);
    Serial.println("] ...");
    for (int i = 0; i < _lastIndex; i++)
    {
        if(*_relays != NULL) 
            _relays[i]->Init();
    }
    _initialized = true;
    return true;
}
