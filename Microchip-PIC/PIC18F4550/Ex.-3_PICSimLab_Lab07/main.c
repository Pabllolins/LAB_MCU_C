/*
 * File:   main.c
 * Author: pabll
 *
 * Created on 11 de Fevereiro de 2021, 01:11
 */


#include <xc.h>
#include "SFR_PIC18F.h"
#include "Barra8Leds__PIC18F.h"
#include "Init_PIC18F.h"

void main(void) {    
    InicializaPortas();
    char cont, cont2;
    
    while(1){
        //PORTD = 0xFF;
        for(cont = 0; cont <=7 ; cont ++){
            //PORTD = 0xFF;
            LigarLed(cont);
            for(int a = 0; a <3; a++){
                for(int b = 0; b<30000; b++);
            }
            //PORTD = 0xFF;
            DesligarLed(cont);
            for(int a = 0; a <3; a++){
                for(int b = 0; b<30000; b++);
            }
        }  
    }
    return;
}
