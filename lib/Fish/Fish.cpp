#include <LiquidCrystal.h>
#include <Arduino.h>
#include <Timer.h>

class Fish {
private:
  String NAME = "#Reddy";
  int SWIM_POS = 0;
  int SWIM_SPEED = 250;
  bool SHOW = true;

  LiquidCrystal *_Display;
  Timer *_TimerSwim;

public:
  Fish(LiquidCrystal *Display) {
    _Display = Display;

    this->_TimerSwim = new Timer(SWIM_SPEED);
  }

  void displayName() {
    if (!SHOW) return;

    int cursorPos = (16 - NAME.length())/2;
    _Display->setCursor(cursorPos, 0);
    _Display->print(NAME);
  }

  void displayFish(int x) {
    if (!SHOW) return;

    if(x > 0) {
      for (int pos = 0; pos < x; pos += 1) {
        _Display->setCursor(pos, 1);
          _Display->write(" ");
      }
    }
    _Display->setCursor(x, 1);

    if(x == 0) {
      _Display->write((uint8_t)2);
    }
    if(x == 1) {
      _Display->setCursor(0, 1);
      _Display->write((uint8_t)1);
      _Display->write((uint8_t)2);
    }
    if(x >= 2) {
      _Display->setCursor(x-2, 1);
      _Display->write((uint8_t)0);
      _Display->write((uint8_t)1);
      _Display->write((uint8_t)2);
    }
  }

  void display() {
    SHOW = true;
    _Display->clear();

    this->displayName();
    this->displayFish(SWIM_POS);
  }

  void hide() {
    SHOW = false;
  }

  void swim() {
    if (!SHOW) return;

    SWIM_POS++;

    if(SWIM_POS > 18) {
      SWIM_POS = 0;
    }
    this->displayFish(SWIM_POS);
  }

  void createSymbols(){
    byte head[8] = {
      0b11000,
      0b11100,
      0b11110,
      0b11011,
      0b11111,
      0b11110,
      0b11100,
      0b11000
    };

    byte body[8] = {
      0b00001,
      0b00011,
      0b00111,
      0b11111,
      0b11111,
      0b00111,
      0b00011,
      0b00001
    };

    byte tail[8] = {
      0b00000,
      0b00100,
      0b00110,
      0b00111,
      0b00111,
      0b00110,
      0b00100,
      0b00000
    };

    _Display->createChar(0, tail);
    _Display->createChar(1, body);
    _Display->createChar(2, head);
  }

  void update() {
    if(_TimerSwim->tick()) {
      this->swim();
    }
  }
};
