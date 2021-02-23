// Equivalencia da Lib io.h
#ifndef Bits_PIC18F_H
#define	Bits_PIC18F_H

//fun��es de bit
#define LigaBit(arg,bit) ((arg) |=  (1<<(bit))) //Liga o bit (p�e o valor 1) (bitSet)
#define ZeraBit(arg,bit) ((arg) &= ~(1<<(bit))) //Desliga o bit (p�e o valor 0) (bitClr)
#define InverterBit(arg,bit) ((arg) ^=  (1<<(bit))) //Inverte o bit (bitFlp)
#define LerBit(arg,bit) ((arg) &   (1<<(bit))) //L� o bit (bitTst)

#endif	/* XC_HEADER_TEMPLATE_H */

