#include "Conversor_74HC595_PIC18F.h"
#include "Padrao_ArduinoIDE.h"
#include <xc.h>
#include "Bits_PIC18F.h"


#define PinoEn_74HC595 PINO_C0
#define PinoClk_74HC595 PINO_C1
#define PinoData_74HC595 PINO_C2

void Inicia74HC595(void){       
	ModoDoPino(PinoEn_74HC595, SAIDA);
	ModoDoPino(PinoClk_74HC595, SAIDA);
	ModoDoPino(PinoData_74HC595, SAIDA);
}


void PulseEnClock(void){ //Pulso de clock para habilitar os dados na saida
	EscreveDigital(PinoEn_74HC595, ALTO);
	EscreveDigital(PinoEn_74HC595, BAIXO);
}

void PulseClockData(void){ //Pulso de clock para enviar um bit

	EscreveDigital(PinoClk_74HC595, ALTO);
	EscreveDigital(PinoClk_74HC595, BAIXO);
}


void Escreve74HC595(int valor){
	char i;
	EscreveDigital(PinoClk_74HC595, BAIXO);
	for(i = 0; i < 8; i++){
		EscreveDigital(PinoData_74HC595, valor & 0x80); //0x80 define o extremo binário como MSB (More Significative Bit) 
		PulseClockData();
		valor <<= 1;
	}
	PulseEnClock();
}

