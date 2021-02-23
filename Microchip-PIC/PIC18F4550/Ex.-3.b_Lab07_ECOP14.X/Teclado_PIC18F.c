// -----------------------------------------------------------------------
//   Arquivo: Teclado_PIC18F.h//            
//   Autor:   Pabllo Lins
//	 Data: 17/02/2021
//	 Baseado na biblioteca das informações dos comentários abaixo
//
// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2014
// -----------------------------------------------------------------------
//   Arquivo: keypad.c
//            Biblioteca de operação de um teclado matricial
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licença: GNU GPL 2
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------

#include "Teclado_PIC18F.h"
#include <pic18f4550.h>
#include "Padrao_ArduinoIDE.h"
#include "Bits_PIC18F.h"

#define COL0 PIN_B0 //Pino saída
#define COL1 PIN_B1	//Pino saída
#define COL2 PIN_B2 //Pino saída
#define COL3 PIN_B3 //Pino saída

#define LIN0 PIN_B4 //Pino Entrada (leitura)
#define LIN1 PIN_B5	//Pino Entrada (leitura)


static unsigned char valor = 0b0000000000000000;

unsigned char LeituraTeclado(void){
    return valor;
}

void DebounceTeclado(void){
    unsigned char i, j;
    static unsigned char tempo;
    static unsigned int valorNovo = 0x00;
    static unsigned int valorAntigo = 0x00;
    
    for (i = 0; i < 4; i++) {//PORTA B 0,1,2 e 3 -- p�e o pino de sa�da (colunas) em nivel alto sequencialmente        
        TRISB = ~((unsigned char)1<<i); //desabilita todas os pinos configurados como colunas                        
        PORTB = ~((unsigned char)1<<i); //Coloca nivel alto os pinos para serem saídas, mas somente ficará com o valor 1 o pino(i)        
        for (j = 0; j < 2; j++) { //0,1
            if (!LerBit(PORTB, j + 4)) {//PORTA B 4,5
                LigaBit(valorNovo, ((i * 2) + j));
            } else {
                ZeraBit(valorNovo, ((i * 2) + j));
            }
        }
    }
      
    if (valorAntigo == valorNovo) {
        tempo--;
    } else {
        tempo = 10;
        valorAntigo = valorNovo;
    }
    
    if (tempo == 0) {
        valor = valorAntigo;
    }
}

	
void IniciaTeclado(void){    
    TRISB = 0xF0; //coloca 0 a 3 como pinos entradas (linhas)(leitura), e 4 a 7 como pinos Saida (colunas)     
    ZeraBit(INTCON2, 7); // liga pull up
    ADCON1 = 0b00001110; //Apenas AN0 é analógico

#ifdef _PIC18F4550_H_
	SPPCFG = 0x00; //SFR
#endif
}

