#include <Arduino.h>

class MyRelay {
public:
  MyRelay(byte pin, bool state = false, bool isReverseState = false) {
    _pin = pin;
    _state = state;
    _isReverseState = isReverseState;
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

  bool getReverseState() {
    return (!_isReverseState) ? _state : !_state;
  }
};
