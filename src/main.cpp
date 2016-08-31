
#include <Arduino.h>
#include <IRRecieve.cpp>
#include <LiquidCrystal.h>
#include <RGBRemote.h>
#include <Menu.cpp>
#include <Fish.cpp>

// Initialize LCD Display
LiquidCrystal Display(12, 11, 5, 4, 3, 2);
Menu MainMenu(&Display);

Fish Reddy(&Display);

// Internal variables
int RECV_PIN = 9;
bool IN_MENU = false;


IRRecieve Reciever(RECV_PIN);

void setup()
{
  Serial.begin(9600);
  Reciever.init(1000);

  Reddy.createSymbols();
  Display.begin(16, 2);

  Reddy.display();
}

void loop() {
  // Tick timers
  Reciever.update();
  MainMenu.update();
  Reddy.update();

  // Decode IR Signals to the main menu
  MainMenu.sendSignal(Reciever.getLastCommand());
  if(IN_MENU == true && MainMenu.isShown() == false) {
    Reddy.display();
    IN_MENU = false;
  } else {
    IN_MENU = MainMenu.isShown();
  }

  if(MainMenu.isShown()) {
    Reddy.hide();
  }

}
