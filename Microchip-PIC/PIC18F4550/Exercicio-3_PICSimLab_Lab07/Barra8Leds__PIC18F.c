// -----------------------------------------------------------------------
//   Arquivo: CBarra8Leds__PIC18F.c
//            
//   Co-Autor:   Pabllo Lins
//   Data: 09/02/2021
//   Arquivo de biblioteca baseado na biblioteca do autor abaixo
//
// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2014
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   LicenÁa: GNU GPL 2
// -----------------------------------------------------------------------

#include "Barra8Leds__PIC18F.h"
//#include <pic18f4550.h>
#include <xc.h>

void ConfiguraLed(void){ //Leds configurados no PortD
	//(*(volatile __near unsigned char*) 0xF95) = 0x00; // Define o endere√ßo de TRISD com o sentido de sa√≠da
	TRISD = 0x00; //Define como saida
    PORTD = 0x00; //Os leds iniciam ligados (l√≥gica inversa)
}


void LigarLed(char num){
    char acionamento = 0b11111111;  
    acionamento &= (0 << num);    
    PORTD = acionamento;
}


void DesligarLed(char num){
    char acionamento = 0b00000000;    
    acionamento |= (1 << num);  //LÛgica inversa no led    
    PORTD = acionamento;
}

