/*
 * File:   main.c
 * Author: pabll
 *
 * Created on 22 de Fevereiro de 2021, 20:29
 */

#include "SFR_PIC18F.h"
#include "Bits_PIC18F.h"
#include "Padrao_ArduinoIDE.h"
#include "Teclado_PIC18F.h"
#include "Conversor_74HC595_PIC18F.h"
#include "Disp7Seg_74HC595_PIC18F.h"
#include <xc.h>

void main(void) {
    char i = 0; 
    unsigned char tecla; 
    unsigned char teclado[8] = {'A', 'B', 3, 6, 2, 5, 1, 4};
    InicializaSeteSegmentos(); 
    IniciaTeclado();       
    
    for (;;) {         
        AtualizaSeteSegmentos(); 
        DebounceTeclado();         
        tecla = LeituraTeclado(); 
        for (i = 0; i < 15; i++){ 
            
            if(LerBit(tecla, i)) { 
                if (i == 0){ //Corrigindo letra para a posição na tabela de caracteres do display de 7 segmentos               
                    SeteSegmentosDigito(3, 0xA); //(Display, valor)
                }
                else if (i == 1){ //Corrigindo letra para a posição na tabela de caracteres do display de 7 segmentos               
                    SeteSegmentosDigito(3, 0xB); //(Display, valor)
                }
                else{  
                    SeteSegmentosDigito(3, teclado[i]); //(Display, valor)            
                }
            }   
        }
    }
}

