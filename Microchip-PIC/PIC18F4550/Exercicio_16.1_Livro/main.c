/*
 * File:   main.c
 * Author: pabll
 *
 * Created on 25 de Fevereiro de 2021, 19:31
 * 
 */

//como o exercicio pediu para não utilizar bibliotecas, serao feitas abaixo todos os setups

#include <xc.h>
#include "SFR_PIC18F.h" //Inclui o cabeçalho com SETs, #pragma configs para meu microcontrolador 
#include <pic18f4550.h> //Inclui a biblioteca do microcontrolador

#define BitSet(arg, bit) ((arg) |=  (1<<(bit)))
#define BitClr(arg, bit) ((arg) &= ~(1<<(bit)))
#define BitFlp(arg, bit) ((arg) ^=  (1<<(bit)))
#define BitTst(arg, bit) ((arg) & (1<<(bit)))

void main(void) {    
    ADCON1 = 0b00001110; //Apenas AN0 Ã© analÃ³gico
    //BitClr(INTCON2, 7); // liga pull up
    SPPCFG = 0x00; //SFR                    
    TRISB = 0xFF; // 0b11111111; --> Seta os bits B0 a B7 como entrada            
    TRISD = 0x00; // 0b00000000; --> Seta os bits D0 a D7 como saida           
                    
    int valorAntigo;
            
    while(1){                   
        PORTD = 0xFF; //Icinica com todos os pinos da porta D desligados (Logica inversa)                   
        
        for(char i = 0; i < 8; i++){  
            
            valorAntigo |= (BitTst(PORTB, i)<<1);             
            
            if((i <= 3) && (valorAntigo != (BitTst(PORTB, i)))){
                for(long cont = 0; cont <50000; cont++);  //"50000" para simular e perceber o delay no pressionamento
                if(BitTst(PORTB, i)){                
                    BitClr(PORTD, i);
                    for(long cont = 0; cont <1000000; cont++); //tempo para vizualizar o acionamento do pino                
                }  
            }    
            
            if((i > 3)&& (valorAntigo != (BitTst(PORTB, i)))){
                for(long cont = 0; cont <100000; cont++); //"100000" para simular e perceber o delay no pressionamento 
                if(BitTst(PORTB, i)){                
                    BitClr(PORTD, i);
                    for(long cont = 0; cont <1000000; cont++); //tempo para vizualizar o acionamento do pino                
                }  
            }            
        }                        
    }    
    return;
}
