
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PADRAO_ARDUINOIDE_H
#define	PADRAO_ARDUINOIDE_H

/*
#define OUTPUT 0
#define INPUT  1
#define LOW 0
#define HIGH 1
*/

#define SAIDA 0
#define ENTRADA 1
#define BAIXO 0
#define ALTO 1

/*
enum pin_label{
    PIN_A0,PIN_A1,PIN_A2,PIN_A3,PIN_A4,PIN_A5,PIN_A6,PIN_A7,            
    PIN_B0,PIN_B1,PIN_B2,PIN_B3,PIN_B4,PIN_B5,PIN_B6,PIN_B7,
    PIN_C0,PIN_C1,PIN_C2,PIN_C3,PIN_C4,PIN_C5,PIN_C6,PIN_C7,
    PIN_D0,PIN_D1,PIN_D2,PIN_D3,PIN_D4,PIN_D5,PIN_D6,PIN_D7,
    PIN_E0,PIN_E1,PIN_E2,PIN_E3,PIN_E4,PIN_E5,PIN_E6,PIN_E7
};
*/

enum pino_etiqueta{
    PINO_A0,PINO_A1,PINO_A2,PINO_A3,PINO_A4,PINO_A5,PINO_A6,PINO_A7,            
    PINO_B0,PINO_B1,PINO_B2,PINO_B3,PINO_B4,PINO_B5,PINO_B6,PINO_B7,
    PINO_C0,PINO_C1,PINO_C2,PINO_C3,PINO_C4,PINO_C5,PINO_C6,PINO_C7,
    PINO_D0,PINO_D1,PINO_D2,PINO_D3,PINO_D4,PINO_D5,PINO_D6,PINO_D7,
    PINO_E0,PINO_E1,PINO_E2,PINO_E3,PINO_E4,PINO_E5,PINO_E6,PINO_E7
};

/*
void digitalWrite(int pin, int value);
int digitalRead(int pin);
void pinMode(int pin, int type);
*/

void EscreveDigital(int pino, int valor);
int LeituraDigital(int pino);
void ModoDoPino(int pino, int tipo);

//void systemInit(void);
#endif	/* XC_HEADER_TEMPLATE_H */

