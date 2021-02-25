/*
 * File:   main.c
 * Author: PablloLins
 *
 * Created on 6 de Janeiro de 2021, 19:37
 */

#include <xc.h>
#include "Bits_PIC18F.h"
#include "Conversor_74HC595_PIC18F.h"
#include "Disp7Seg_74HC595_PIC18F.h"
#include "Padrao_ArduinoIDE.h"
#include "SFR_PIC18F.h"

void main(void) {    
    unsigned int time, count;
	InicializaSeteSegmentos();
    
    while(1){    
        count++;        
        //separa cada algarismo da variável count                
        SeteSegmentosDigito(0, (count) %10);  //separa cada algarismo de milhar da variável count        
        LigaPontoDecimal(0);
        SeteSegmentosDigito(1, (count/10) %10); //separa cada algarismo de centena da variável count    
        SeteSegmentosDigito(2, (count/100) %10); //separa cada algarismo de dezena da variável count 
        SeteSegmentosDigito(3, (count/1000) %10); //separa cada algarismo de unidade da variável count           
        AtualizaSeteSegmentos();
        for(time = 0; time < 6000; time++); //Gasta um tempo para evitar o flicker  
        //DesligaPontoDecimal(3);
    }  
    return;
}
