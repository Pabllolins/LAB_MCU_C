/*
 * File:   main.c
 * Author: PablloLins
 *
 * Created on 13 de Dezembro de 2020, 23:52
 */


#include <xc.h>
#include "SFR_PIC18F.h"
#include "Init_PIC18F.h"
#include "ADC_PIC18F.h"

void main(void) {
    
    InicializaPortas();
    IniciaADC();
    
    float leituraAD; // declara um variavel para armazenar o valor lido
    
    for(;;){                
        leituraAD = (float)LerConversorAD(1); // a variavel recebe o valor de retorno da função;
        
        if(leituraAD < 1){
            PORTD = 0x00;
        }else if(leituraAD < 127.8){
            PORTD = 0x01;
        }else if(leituraAD < 255.75){
            PORTD = 0x03;
        }else if(leituraAD < 383.5){
            PORTD = 0x07;
        }else if(leituraAD < 514.2){
            PORTD = 0x0F;
        }else if(leituraAD < 642.1){
            PORTD = 0x1F;
        }else if(leituraAD < 770){
            PORTD = 0x3F;
        }else if(leituraAD < 897.8){
            PORTD = 0x7F;
        }else if(leituraAD < 1023){
            PORTD = 0xFF;
        }
        
        //else PORTD = 0xFF;
        
    }    
    return;
}
