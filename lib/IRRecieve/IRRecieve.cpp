
#include <IRremote.h>
#include <Timer.h>
#include <RGBRemote.h>

class IRRecieve
{
  int RECV_PIN;
  decode_results results;
  IRrecv *Reciever;
  Timer *_TimerInstance;
  long LAST_COMMAND = 0x00;

  int RECV_DELAY = 0;

  unsigned long previousMillis;  	// will store last time of recieving

  public:

    IRRecieve(int pin) {
      RECV_PIN = pin;
    }

    void init(long _delay) {
      RECV_DELAY = _delay;

      this->_TimerInstance = new Timer(RECV_DELAY);
      IRrecv *Reciever = new IRrecv(RECV_PIN);
      Reciever->enableIRIn();
    }

    void update() {
      if(_TimerInstance->tick()) {
        if (Reciever->decode(&results)) {
          if(RGBRemote::decode(results.value)) {
            Serial.print("DECODED:  ");
            Serial.println(results.value, HEX);
            LAST_COMMAND = results.value;
          } else {
             Serial.println(results.value, HEX);
          }
          Reciever->resume(); // Receive the next value
        }
      }
    }

    int getLastCommand() {
      long _cmd = LAST_COMMAND;
      LAST_COMMAND = 0x00;

      return _cmd;
    }
};
