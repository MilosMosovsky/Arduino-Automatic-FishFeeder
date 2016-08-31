#ifndef TIMER_H
#define TIMER_H

class Timer {

private:
  long TIMER_DELAY = 100;
  long TIMER_PREVIOUS = 0;

public:
  int getDelay();
  Timer(int delay);
  bool tick();
  void reset();

};

#endif
