/*
 * Author: Pabllo Lins
 *
 * Created on 4 de Agosto de 2020, 21:39
 */

#include <xc.h>
#include "Bits_PIC18F.h"
#include "Padrao_ArduinoIDE.h"
//PORTB e PORTD apenas para demonstrar o funcionamento

void EscreveDigital(int pino, int valor){
    //porta
    if(pino <8){
        if (valor){  LigaBit(PORTA,pino);}
        else{        ZeraBit(PORTA,pino);}
    }else if(pino<16){
        pino -=8;
        if (valor){  LigaBit(PORTB,pino);}
        else{        ZeraBit(PORTB,pino);}
    }else if(pino<24){
        pino -=16;
        if (valor){  LigaBit(PORTC,pino);}
        else{        ZeraBit(PORTC,pino);}
    }else if(pino<32){
        pino -=24;
        if (valor){  LigaBit(PORTD,pino);}
        else{        ZeraBit(PORTD,pino);}
    }else if(pino<40){
        pino -=32;
        if (valor){  LigaBit(PORTE,pino);}
        else{        ZeraBit(PORTE,pino);}
    }
    
	
}
int LeituraDigital(int pino){
    if(pino <8){
        return LerBit(PORTA,pino);
    }else if(pino<16){
        return LerBit(PORTB,pino-8);
    }else if(pino<24){
        return LerBit(PORTC,pino-16);
    }else if(pino<32){
        return LerBit(PORTD,pino-24);
    }else if(pino<40){
        return LerBit(PORTE,pino-32);
    }
    return -1;
}

void ModoDoPino(int pino, int tipo){
    if(pino <8){
        if (tipo){  LigaBit(TRISA,pino);}
        else{       ZeraBit(TRISA,pino);}
    }else if(pino<16){
        if (tipo){  LigaBit(TRISB,pino-8);}
        else{       ZeraBit(TRISB,pino-8);}
    }else if(pino<24){
        if (tipo){  LigaBit(TRISC,pino-16);}
        else{       ZeraBit(TRISC,pino-16);}
    }else if(pino<32){
        if (tipo){  LigaBit(TRISD,pino-24);}
        else{       ZeraBit(TRISD,pino-24);}
    }else if(pino<40){
        if (tipo){  LigaBit(TRISE,pino-32);}
        else{       ZeraBit(TRISE,pino-32);}
    }
            
}
