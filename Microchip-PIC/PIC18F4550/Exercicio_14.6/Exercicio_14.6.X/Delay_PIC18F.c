/*
 * 
 * EXEMPLO DE FUNCIONAMENTO DO LA�O FOR
 * unsigned char i, j, k;
 * for(i=0; i < 34; i++){ //3 + 34 * (30.003 + 3) = 1.020.207 instru��es
 * for(j=0; j < 100; j++){ //3 + 100 * (297 + 3) = 30.003 instru��es
 * for(k=0; k < 98; k++); // 3 + 98 * (3) = 297 instru��es
 * }
 * } 
 * 
 * Percebemos pelo c�digo acima que para realizar um for precisamos de 3 passos de inicializa��o.
 * Cada itera��o exige 2 passos: uma compara��o e um ?pulo?, totalizando 3 ciclos de inicializa��o e 3 ciclos de intera��o
 * 
 * Se temos um processador trabalhando a 8 MHz, cada instru��o � executada em 0.5us. 
 * Para termos um tempo de espera de 0.5s precisamos de 1 milh�o de instru��es. Se colocarmos loops
 * encadeados podemos multiplicar a quantidade de instru��es que ser�o executadas. Para obtermos
 * um valor de 1 milh�o de instru��es devemos utilizar pelo menos 3 loops encadeados. Os valores
 * dos loops s�o obtidos de maneira iterativa.
 * 
 * 
 * Oscilador interno de 4MHz, = Frequencia de entrada de 4MHz
 * Frequencia de m�quina com essa arquitetura em Pipeline, � igual a Frequencia de entrada/4;
 * Frequencia de maquina = 4MHz/4 = FreqMaq = 1MHz
 * 
 * Frequencia = 1/T
 * Tempo de m�quina = 1/Frequencia de maquina.
 * Tempo de m�quina = 1/1MHz = 1/1000000Hz = 0,000001 segundo
 * 
 * Cada ciclo de maquina (instru��o) leva 0,000001 (1us) segundo
 * para 0,5 segundos, precisa-se de 500.000 (quinhentas mil ciclos de m�quina)
 */

#include "Delay_PIC18F.h"

void tempo(unsigned char a){
    volatile unsigned char i, j, k;
    for (i = 0; i<a; i++){ // X a entrada
        for(j = 0; j < 100; j++){ // X 100
            for(k = 0; k < 8; k++); // 8 ciclos de 0,000001 s
        }
    }
}

void MeioSegundo(){ //para 0,5 segundos, precisa-se de 500.000 (quinhentas mil ciclos de m�quina)
volatile unsigned char h, i, j, k;
        for (i = 0; i<100; i++){ // 3 + 100 * (5001+3) = 500403 instru��es
                for(j = 0; j < 98; j++){ // 3 + 98* (48+3) =  5001 instru��es
                    for(k = 0; k < 15; k++); // 3 + 15 * (3) =  48 instru��es
                    
                    //Um la�o for precisamos de 3 passos de inicializa��o. 
                    //Cada itera��o exige 2 passos: uma compara��o e um ?pulo?.
                    //totalizando 3 ciclos de inicializa��o e 3 ciclos de intera��o
            }
        }
}

void tempoSegundos(unsigned char segundos){
    volatile unsigned char h, i, j, k, l;
    for(l=0; l<segundos; l++){
        for(h = 0; h<10; h++){ // X 5
            for (i = 0; i<100; i++){ // X 100
                for(j = 0; j < 100; j++){ // 3 + 100* (30+3) = * (297 + 3) = 30.003 instru��es
                    for(k = 0; k < 9; k++); // 3 + 9 * (3) = 30 instru��es
                }
            }
        }
    }
}

void UmSegundo(){ //para 0,5 segundos, precisa-se de 500.000 (quinhentas mil ciclos de m�quina)
volatile unsigned char h, i, j, k;
        for (i = 0; i<200; i++){ // 3 + 200 * (5001+3) = 1000800 instru��es
                for(j = 0; j < 98; j++){ // 3 + 98* (48+3) =  5001 instru��es
                    for(k = 0; k < 15; k++); // 3 + 15 * (3) =  48 instru��es
                    
                    //Um la�o for precisamos de 3 passos de inicializa��o. 
                    //Cada itera��o exige 2 passos: uma compara��o e um ?pulo?.
                    //totalizando 3 ciclos de inicializa��o e 3 ciclos de intera��o
            }
        }
}