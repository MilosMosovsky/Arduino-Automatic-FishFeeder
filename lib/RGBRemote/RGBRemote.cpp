#include "RGBRemote.h"

int RGBRemote::decode(int value) {
  switch(value) {
    case IR_BTN_MENU:
      return value;
    case IR_BTN_MENU_ABORT:
      return value;
    case IR_BTN_MENU_LEFT:
      return value;
    case IR_BTN_MENU_RIGHT:
      return value;
  }

  return false;
}
