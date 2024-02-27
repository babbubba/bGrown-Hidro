#ifndef relays_h
#define relays_h

class RelayChannel {
  private:
    byte _pin;
    byte _channel;
    bool _reverse;
    String _label;
    bool _active;
    void PrintChangeStatus(bool);

  public:
    RelayChannel(byte, byte);
    RelayChannel(byte, byte, bool);
    void Init();
    bool Status();
    void TurnOn();
    void TurnOff();
    void Toggle();
};

RelayChannel::RelayChannel(byte channel, byte pin): RelayChannel(channel, pin, false) {

}

RelayChannel::RelayChannel(byte channel, byte pin, bool reverse) {
  _active = false;
  _label = String(channel);
  _reverse = reverse;
  _channel = channel;
  _pin = pin;
}

void RelayChannel::Init() {
  pinMode(_pin, OUTPUT);
  if (_reverse) {
    digitalWrite(_pin, HIGH);
  }
}

bool RelayChannel::Status() {
  return _active;
}

void RelayChannel::PrintChangeStatus(bool demand) {
  Serial.println("Channel '" + String(_channel) + "' (GPIO: " + String(_pin) + " - Prev.: " + String(_active ? "ON" : "OFF") + " - Reversed channel.: " + String(_reverse ? 'Y' : 'N')  + ") " +   String(demand == true ? "ON" : "OFF"));
}

void RelayChannel::TurnOn() {
  digitalWrite(_pin, (_reverse) ? LOW : HIGH);
  PrintChangeStatus(true);
  _active = 1;
}
void RelayChannel::TurnOff() {
  digitalWrite(_pin, (_reverse) ? HIGH : LOW);
  PrintChangeStatus(false);
  _active = 0;
}
void RelayChannel::Toggle() {
  _active == 0 ? TurnOn() : TurnOff();
}
#endif
