
#include <LiquidCrystal.h>
#include <RGBRemote.h>
#include <Timer.h>

class Menu {
private:
  int CURRENT_ITEM = 0;
  int MENU_ITEMS = 5;
  int MENU_SHOW = false;

  LiquidCrystal *_Display;
  Timer *_TimerInstance;

  char* MENU[5] = {
    "1. Current Time ",
    "2. Feeding Time ",
    "3. Food Amount  ",
    "4. Cleaning Time",
    "5. Clean Perform"
  };

public:
  Menu(LiquidCrystal *Display) {
    _Display = Display;

    this->_TimerInstance = new Timer(20000);
  }

  void displayCurrentMenu() {
    MENU_SHOW = true;

    _Display->clear();
    _Display->setCursor(0,0);
    _Display->print(MENU[CURRENT_ITEM]);
  }

  void next() {
    CURRENT_ITEM++;

    if(CURRENT_ITEM >= MENU_ITEMS) {
      CURRENT_ITEM = 0;
    }

    this->displayCurrentMenu();
  }

  void prev() {
    CURRENT_ITEM--;

    if(CURRENT_ITEM < 0) {
      CURRENT_ITEM = MENU_ITEMS-1;
    }

    this->displayCurrentMenu();
  }

  void close() {
    if (!this->isShown()) return;

    CURRENT_ITEM = 0;
    MENU_SHOW = false;

    _Display->clear();
    _Display->setCursor(0,0);
  }

  void sendSignal(int signal) {
    switch (signal) {
      case IR_BTN_MENU:
        this->displayCurrentMenu();
        _TimerInstance->reset();
        break;
      case IR_BTN_MENU_ABORT:
        this->close();
        _TimerInstance->reset();
        break;
      case IR_BTN_MENU_RIGHT:
        this->next();
        _TimerInstance->reset();
        break;
      case IR_BTN_MENU_LEFT:
        this->prev();
        _TimerInstance->reset();
        break;
    }
  }

  bool isShown() {
    return MENU_SHOW;
  }

  void update() {
    if(_TimerInstance->tick()) {
      this->close();
    }
  }
};
