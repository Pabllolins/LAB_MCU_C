 
#ifndef PADRAO_ARDUINOIDE_H
#define	PADRAO_ARDUINOIDE_H

#define SAIDA 0
#define ENTRADA 1
#define BAIXO 0
#define ALTO 1


enum pino_etiqueta{
    PINO_A0,PINO_A1,PINO_A2,PINO_A3,PINO_A4,PINO_A5,PINO_A6,PINO_A7,            
    PINO_B0,PINO_B1,PINO_B2,PINO_B3,PINO_B4,PINO_B5,PINO_B6,PINO_B7,
    PINO_C0,PINO_C1,PINO_C2,PINO_C3,PINO_C4,PINO_C5,PINO_C6,PINO_C7,
    PINO_D0,PINO_D1,PINO_D2,PINO_D3,PINO_D4,PINO_D5,PINO_D6,PINO_D7,
    PINO_E0,PINO_E1,PINO_E2,PINO_E3,PINO_E4,PINO_E5,PINO_E6,PINO_E7
};

void EscreveDigital(int pino, int valor);
int LeituraDigital(int pino);
void ModoDoPino(int pino, int tipo);

#endif	

