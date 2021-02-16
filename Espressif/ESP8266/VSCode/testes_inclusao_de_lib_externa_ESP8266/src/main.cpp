#include <Arduino.h>
#include <PiscaLed.h>

PiscaLed p(2, 100);

void setup() {

}

void loop() {
  p.acende_led();
}