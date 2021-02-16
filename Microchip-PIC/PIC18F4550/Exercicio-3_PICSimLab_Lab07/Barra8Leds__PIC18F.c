/*
 * File:   controle_led.c
 * Author: PablloLins
 *
 * Created on 9 de Fevereiro de 2021, 23:17
 */

#include "Barra8Leds__PIC18F.h"
//#include <pic18f4550.h>
#include <xc.h>

void ConfiguraLed(void){ //Leds configurados no PortD
	//(*(volatile __near unsigned char*) 0xF95) = 0x00; // Define o endereço de TRISD com o sentido de saída
	TRISD = 0x00; //Define como saida
    PORTD = 0x00; //Os leds iniciam ligados (lógica inversa)
}


void LigarLed(char num){
    char acionamento = 0b11111111;  
    acionamento &= (0 << num);    
    PORTD = acionamento;
}


void DesligarLed(char num){
    char acionamento = 0b00000000;    
    acionamento |= (1 << num);  //L�gica inversa no led    
    PORTD = acionamento;
}

