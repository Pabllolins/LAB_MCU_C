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
    //TRISB = 0xF0; // 
    //TRISC = 0x00; //
      TRISD = 0x00; //Copnfigura a porta D como saida
    //TRISE = 0x00; //
}

void SetupPortas(void){
    //PORTA = 0x00; //
    //PORTB = 0x00; //
    //PORTC = 0x00; //
      PORTD = 0xFF; // Inicia com os leds desligados (Lógica invertida)
    //PORTE = 0x00; //
}	



void InicializaPortas(void){
    SentidoPortas();
    SetupPortas();    
}

