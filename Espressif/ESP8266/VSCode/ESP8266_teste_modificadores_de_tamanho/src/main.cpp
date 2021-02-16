#include <Arduino.h>
#include <EEPROM.h>

/*
Por definição as variaveis não sinalização definida, trabalham com valores negativos e positivos,
logo, definir signed ou não de coloca-lo, dá no mesmo.
*/

unsigned char A = 1; //variável mão pode assumir valores negativos, tem excurssão máxima 0 a 255
signed char B = 2; //Variável trabalha com valores positivos e negativos, tem excurssão máxima -128 a 127.
unsigned int C = 3;//variável mão pode assumir valores negativos, tem excurssão máxima 0 a 65535
signed int D = 4; //Variável trabalha com valores positivos e negativos, tem excurssão máxima -32768 a 32767
long int E = 5; ////Variável trabalha com valores positivos e negativos, tem excurssão máxima -2147483648 a 2147483647
unsigned long int F = 6; //variável mão pode assumir valores negativos, tem excurssão máxima 0 a 4294967295
short int G = 7; //Variável trabalha com valores positivos e negativos, tem excurssão máxima -32768 a 32767

void setup() {
  Serial.begin(9600);
  EEPROM.begin(4096);
  delay(500);

  Serial.println();
  Serial.print("O valor da variável A unsigned char: ");
  Serial.println(A);
  Serial.print("Seu endereco em HEX é: ");
  Serial.println((long) &A, HEX);
  Serial.print("Seu endereco em DEC é: ");
  Serial.println((long) &A, DEC);
  Serial.print("Seu endereco em BIN é: ");
  Serial.println((long) &A, BIN);
  Serial.println();
  
  Serial.print("O valor da variável B signed char: ");
  Serial.println(B);
  Serial.print("Seu endereco em HEX é: ");
  Serial.println((long) &B, HEX);
  Serial.print("Seu endereco em DEC é: ");
  Serial.println((long) &B, DEC);
  Serial.print("Seu endereco em BIN é: ");
  Serial.println((long) &B, BIN);
  Serial.println();
  
  Serial.print("O valor da variável C unsigned int: ");
  Serial.println(C);
  Serial.print("Seu endereco em HEX é: ");
  Serial.println((long) &C, HEX);
  Serial.print("Seu endereco em DEC é: ");
  Serial.println((long) &C, DEC);
  Serial.print("Seu endereco em BIN é: ");
  Serial.println((long) &C, BIN);
  Serial.println();

  Serial.print("O valor da variável D signed int: ");
  Serial.println(D);
  Serial.print("Seu endereco em HEX é: ");
  Serial.println((long) &D, HEX);
  Serial.print("Seu endereco em DEC é: ");
  Serial.println((long) &D, DEC);
  Serial.print("Seu endereco em BIN é: ");
  Serial.println((long) &D, BIN);
  Serial.println();

  Serial.print("O valor da variável E long int: ");
  Serial.println(E);
  Serial.print("Seu endereco em HEX é: ");
  Serial.println((long) &E, HEX);
  Serial.print("Seu endereco em DEC é: ");
  Serial.println((long) &E, DEC);
  Serial.print("Seu endereco em BIN é: ");
  Serial.println((long) &E, BIN);
  Serial.println();

  Serial.print("O valor da variável F unsigned long int: ");
  Serial.println(F);
  Serial.print("Seu endereco em HEX é: ");
  Serial.println((long) &F, HEX);
  Serial.print("Seu endereco em DEC é: ");
  Serial.println((long) &F, DEC);
  Serial.print("Seu endereco em BIN é: ");
  Serial.println((long) &F, BIN);
  Serial.println();

  Serial.print("O valor da variável G short int: ");
  Serial.println(G);
  Serial.print("Seu endereco em HEX é: ");
  Serial.println((long) &G, HEX);
  Serial.print("Seu endereco em DEC é: ");
  Serial.println((long) &G, DEC);
  Serial.print("Seu endereco em BIN é: ");
  Serial.println((long) &G, BIN);
  Serial.println();
}

void loop() {


}