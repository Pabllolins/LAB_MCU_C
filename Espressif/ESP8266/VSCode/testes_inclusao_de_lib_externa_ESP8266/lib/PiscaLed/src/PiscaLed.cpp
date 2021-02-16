
#include <PiscaLed.h>

//globais 
int _pino;
long _time;

PiscaLed::PiscaLed(int pino, long time){
    //pino e time só podem ser acessados de dentro dessa função
    pinMode(pino, OUTPUT);
    _pino = pino;
    _time = time;
}
void PiscaLed::acende_led(){
  digitalWrite(_pino, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(_time);                       // wait for a second
  digitalWrite(_pino, LOW);    // turn the LED off by making the voltage LOW
  delay(_time);                       // wait for a second
}