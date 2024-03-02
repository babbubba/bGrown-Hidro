#include "relay_channel.h"
#include <stdio.h>
#include <stdlib.h>
#include "Arduino.h"
RelayChannel::RelayChannel() 
{  
}
RelayChannel::RelayChannel(int channel, int pin) : RelayChannel(channel, pin, false)
{
}

RelayChannel::RelayChannel(int channel, int pin, bool reverse)
{
  _active = false;
  snprintf(_label, sizeof(_label), "%d", channel);
  _reverse = reverse;
  _channel = channel;
  _pin = pin;
}

void RelayChannel::Init()
{
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _reverse ? HIGH : LOW);
  Serial.print("GPIO ");
  Serial.print(_pin);
  Serial.print(" Init as relay (");
  Serial.print(_reverse ? "inverse" : "normal");
  Serial.print(") channel: ");
  Serial.println(_channel);
}

bool RelayChannel::Status()
{
  return _active;
}

void RelayChannel::PrintChangeStatus(bool demand)
{
  Serial.println("Channel '" + String(_channel) + "' (GPIO: " + String(_pin) + " - Prev.: " + String(_active ? "ON" : "OFF") + " - Reversed channel.: " + String(_reverse ? 'Y' : 'N') + ") " + String(demand == true ? "ON" : "OFF"));
}

void RelayChannel::TurnOn()
{
  digitalWrite(_pin, (_reverse) ? LOW : HIGH);
  PrintChangeStatus(true);
  _active = 1;
}
void RelayChannel::TurnOff()
{
  digitalWrite(_pin, (_reverse) ? HIGH : LOW);
  PrintChangeStatus(false);
  _active = 0;
}
void RelayChannel::Toggle()
{
  _active == 0 ? TurnOn() : TurnOff();
}
