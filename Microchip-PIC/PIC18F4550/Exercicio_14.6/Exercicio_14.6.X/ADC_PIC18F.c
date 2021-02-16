#include "ADC_PIC18F.h"
#include "Padrao_ArduinoIDE.h"
#include "Bits_PIC18F.h"
#include <pic18f4550.h>

void IniciaADC(void) {    
    //AN0-A0, AN1-A1 e AN2-A2 são analógicos e entradas
    
    //ModoDoPino(PINO_A0, ENTRADA);
    ModoDoPino(PINO_A1, ENTRADA);

    LigaBit(ADCON0, 0); //liga ADC
    //config an0-2 como analógico
    //ADCON1 = 0b00001100; //apenas AN0 é analogico, a referencia é baseada na fonte
    ADCON2 = 0b10101010; //FOSC /32, 12 TAD, Alinhamento à direita e tempo de conv = 12 TAD    
}

int LerConversorAD(unsigned int canal) {    
    unsigned int ADvalor;

    ADCON0 &= 0b11000011; //zera os bits do canal
    
    if (canal < 3) {
        ADCON0 |= canal << 2;
    }

    ADCON0 |= 0b00000010; //inicia conversao

    while(LerBit(ADCON0, 1)); // espera terminar a conversão;

    ADvalor = ADRESH; // le o resultado
    ADvalor <<= 8;
    ADvalor += ADRESL;

    return ADvalor;
}