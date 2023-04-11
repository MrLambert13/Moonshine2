#include "WString.h"
#include <Arduino.h>

class MyStepper {
public:
  MyStepper(byte dirPin, byte stepPin, byte enPin, int maxAngle, int speed, byte oneStepResolution = 1, bool state = false, bool isReverseState = false, bool enableDirInvert = false) {
    _dirPin = dirPin;
    _stepPin = stepPin;
    _enPin = enPin;
    _maxAngle = maxAngle;
    _speed = speed;
    _oneStepResolution = oneStepResolution;
    _enableDirInvert = enableDirInvert;
    _state = state;
    _isReverseState = isReverseState;

    pinMode(_dirPin, OUTPUT);
    pinMode(_stepPin, OUTPUT);
    pinMode(_enPin, OUTPUT);
    digitalWrite(_enPin, getReverseState());
  }

  bool rotate(int angle) {
    if ((_currentAngle + angle) > _maxAngle) return false;
    if ((_currentAngle + angle) < 0) angle = -_currentAngle;

    digitalWrite(_dirPin, getInvert(angle));
    bool state = digitalRead(_enPin);
    float steps = abs(angle) / _oneStepResolution;  //calc quantity step for angle
    digitalWrite(_enPin, !state);
    for (int x = 0; x < steps; x++) {
      digitalWrite(_stepPin, state);
      yield();
      digitalWrite(_stepPin, !state);
      delayMicroseconds(_speed);
    }
    digitalWrite(_enPin, state);
    _currentAngle += angle;
    return true;
  }

  bool setAngle(int angle) {
    if (angle == _currentAngle) return false;
    return rotate(angle - _currentAngle);
  }


  void off() {
    rotate(-_currentAngle);
  }

  void on() {
    rotate(int(_maxAngle / 2));
  }

  int getCurrentAngle() {
    return _currentAngle;
  }

  bool isOn() {
    return _currentAngle > 0;
  }

private:
  byte _dirPin;
  byte _stepPin;
  byte _enPin;
  bool _state;
  bool _isReverseState;
  int _maxAngle;
  int _speed;
  byte _oneStepResolution;
  bool _enableDirInvert;
  int _currentAngle;

  bool getReverseState() {
    return (!_isReverseState) ? _state : !_state;
  }

  bool getInvert(int angle) {
    return (_enableDirInvert) ? !(angle < 0) : (angle < 0);
  }
};