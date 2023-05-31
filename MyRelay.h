#include <Arduino.h>

class MyRelay {
public:
  MyRelay(byte pin, String name, bool state = false, bool isReverseState = false) {
    _pin = pin;
    _state = state;
    _isReverseState = isReverseState;
    _name = name;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, getReverseState());
  };

  void on() {
    if (_state) return;
    _state = true;
    digitalWrite(_pin, getReverseState());
  };

  void off() {
    if (!_state) return;
    _state = false;
    digitalWrite(_pin, getReverseState());
  };

  void toggle() {
    _state = !_state;
    digitalWrite(_pin, getReverseState());
    BOT_SEND(_name + " - " + ((_state) ? "вкл" : "выкл") );
  };

  bool getState() {
    return _state;
  };

  void onChangeState(bool state) {
    _state = state;
    digitalWrite(_pin, getReverseState());
  };

private:
  byte _pin;
  bool _state;
  bool _isReverseState;
  String _name;

  bool getReverseState() {
    return (!_isReverseState) ? _state : !_state;
  }
};
