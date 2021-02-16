
#include <meuPWM.h>

int pino_;
long tempo_;


meupwm::meupwm(int pino, long tempo){
pinMode(pino, OUTPUT);
pino_ = pino;
tempo_ = tempo;
}

void meupwm::variacao(){
int i = 0;
while(i < 1000){
  analogWrite(pino_, i);
  delay(tempo_);
    i=i+1;
    if(i==1000){
    break;
    }
}
if(i==1000){
while(i>0){
  analogWrite(pino_, i);
  delay(tempo_);
    i=i-1;
    if(i==0){
    break;
    }
}
}

i=0;

}
