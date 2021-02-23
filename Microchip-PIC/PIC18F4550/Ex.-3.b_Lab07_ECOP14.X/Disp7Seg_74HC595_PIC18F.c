#include "Disp7Seg_74HC595_PIC18F.h"
#include "Conversor_74HC595_PIC18F.h"
#include "Padrao_ArduinoIDE.h"
#include "Bits_PIC18F.h"
#include <pic18f4550.h>
#include <xc.h>

//#define DATA  PORTD //Coloca no PORT D o valor recebido
/********ESTE Padrão não funciona
#define DISP0 PORTAbits.RA2 //Define o pino de habilitar o display
#define DISP1 PORTAbits.RA3 //Define o pino de habilitar o display
#define DISP2 PORTAbits.RA4 //Define o pino de habilitar o display
#define DISP3 PORTAbits.RA5 //Define o pino de habilitar o display
*/

#define DISP0 PINO_A2 //Define o pino de habilitar o display
#define DISP1 PINO_A3 //Define o pino de habilitar o display
#define DISP2 PINO_A4 //Define o pino de habilitar o display
#define DISP3 PINO_A5 //Define o pino de habilitar o display

//vetor para armazenar a conversão do display
// CODIGO PARA CATODO COMUM
/*
static const char valor[] = {
    0x3F, //Pos 0 _-_ Valor = 0 
    0x06, //Pos 1 _-_ Valor = 1
    0x5B, //Pos 2 _-_ Valor = 2
    0x4F, //Pos 3 _-_ Valor = 3
    0x66, //Pos 4 _-_ Valor = 4
    0x6D, //Pos 5 _-_ Valor = 5
    0x7D, //Pos 6 _-_ Valor = 6
    0x07, //Pos 7 _-_ Valor = 7
    0x7F, //Pos 8 _-_ Valor = 8
    0x6F, //Pos 9 _-_ Valor = 9
    0x77, //Pos 10 _-_ Valor = A
    0x7C, //Pos 11 _-_ Valor = B
    0x39, //Pos 12 _-_ Valor = C
    0x5E, //Pos 13 _-_ Valor = D
    0x79, //Pos 14 _-_ Valor = E
    0x71  //Pos 15 _-_ Valor = F
};
*/
 
//vetor para armazenar a conversão do display
// CODIGO PARA ANODO COMUM
static const char valor[] = {
    0xC0, //0b11000000 -- Pos 0 _-_ Valor = 0 
    0xF9, //0b11111001 -- Pos 1 _-_ Valor = 1        
    0xA4, //0b10100100 -- Pos 2 _-_ Valor = 2
    0xB0, //0b10110000 -- Pos 3 _-_ Valor = 3
    0x99, //0b10011001 -- Pos 4 _-_ Valor = 4
    0x92, //0b10010010 -- Pos 5 _-_ Valor = 5
    0x82, //0b10000010 -- Pos 6 _-_ Valor = 6
    0xF8, //0b11111000 -- Pos 7 _-_ Valor = 7
    0x80, //0b10000000 -- Pos 8 _-_ Valor = 8
    0x90, //0b10010000 -- Pos 9 _-_ Valor = 9
    0x88, //0b10001000 -- Pos 10 _-_ Valor = A
    0x83, //0b10000011 -- Pos 11 _-_ Valor = B
    0x66, //0b11000110 -- Pos 12 _-_ Valor = C
    0xA1, //0b10100001 -- Pos 13 _-_ Valor = D
    0x86, //0b10000110 -- Pos 14 _-_ Valor = E
    0x8D  //0b10001110 -- Pos 15 _-_ Valor = F
};


static char display; //Variável que armazena qual é o display disponivel
static char v0, v1, v2, v3; //Variáveis que armazenam o valor a ser enviado ao display

void InicializaSeteSegmentos(void) {
    Inicia74HC595();
    //configuração dos pinos de controle
    ModoDoPino(DISP0, SAIDA);
    ModoDoPino(DISP1, SAIDA);
    ModoDoPino(DISP2, SAIDA);
    ModoDoPino(DISP3, SAIDA);   
}

void SeteSegmentosDigito(char pos, char val) {
    if (pos == 0) { v0 = val; }
    if (pos == 1) { v1 = val; }
    if (pos == 2) { v2 = val; }
    if (pos == 3) { v3 = val; }
}

void AtualizaSeteSegmentos(void) {    
    //desliga todos os displays
    EscreveDigital(DISP0,BAIXO);
    EscreveDigital(DISP1,BAIXO);
    EscreveDigital(DISP2,BAIXO);
    EscreveDigital(DISP3,BAIXO);

    switch (display) //liga apenas o display da vez
    {
        case 0:
            Escreve74HC595(valor[v0]);
            EscreveDigital(DISP0, ALTO);
            display = 1;
            break;

        case 1:
            Escreve74HC595(valor[v1]);
            EscreveDigital(DISP1, ALTO);
            display = 2;
            break;

        case 2:
            Escreve74HC595(valor[v2]);
            EscreveDigital(DISP2, ALTO);
            display = 3;
            break;

        case 3:
            Escreve74HC595(valor[v3]);
            EscreveDigital(DISP3, ALTO);
            display = 0;
            break;

        default:
            display = 0;
            break;
    }
}

