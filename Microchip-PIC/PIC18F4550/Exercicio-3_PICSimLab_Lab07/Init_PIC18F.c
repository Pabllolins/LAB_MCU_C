// -----------------------------------------------------------------------
//   Arquivo: Init_PIC18F.c
//            
//   Co-Autor:   Pabllo Lins
//   Data: 08/12/2020
//   Arquivo de biblioteca baseado na biblioteca do autor abaixo
//
// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2014
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licença: GNU GPL 2
// -----------------------------------------------------------------------

#include "Init_PIC18F.h"
#include <xc.h>

/*
PORTD is an 8-bit wide, bidirectional port. 
The corresponding Data Direction register is TRISD. 

Setting a TRISD bit (= 1) ENTRADA - will make the corresponding PORTD pin an input 
(i.e., put the corresponding output driver in a high-impedance mode). 

Clearing a TRISD bit (= 0) SAIDA - will make the corresponding PORTD pin an output (i.e.,
put the contents of the output latch on the selected pin).
 * 
 */

void SentidoPortas(void){ //associa os pinos 
    //TRISA = 0x00; // 
    //TRISB = 0xF0; // 0b11110000; --> Seta os bits B0 a B3 como saida e B4 a B7 como entrada
    //TRISC = 0x00; //
    //TRISD = 0x00; //
    //TRISE = 0x00; //
}

void SetupPortas(void){
    //PORTA = 0x00; //
    //PORTB = 0x00; //
    //PORTC = 0x00; //
    //PORTD = 0x00; //
    //PORTE = 0x00; //
}	



void InicializaPortas(void){
    SentidoPortas();
    SetupPortas();    
}

