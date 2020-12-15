# 1 "Delay_PIC18F.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.40/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "Delay_PIC18F.c" 2
# 33 "Delay_PIC18F.c"
# 1 "./Delay_PIC18F.h" 1



            void tempo(unsigned char a);
            void MeioSegundo();
            void tempoSegundos(unsigned char segundos);
            void UmSegundo();
# 33 "Delay_PIC18F.c" 2


void tempo(unsigned char a){
    volatile unsigned char i, j, k;
    for (i = 0; i<a; i++){
        for(j = 0; j < 100; j++){
            for(k = 0; k < 8; k++);
        }
    }
}

void MeioSegundo(){
volatile unsigned char h, i, j, k;
        for (i = 0; i<100; i++){
                for(j = 0; j < 98; j++){
                    for(k = 0; k < 15; k++);




            }
        }
}

void tempoSegundos(unsigned char segundos){
    volatile unsigned char h, i, j, k, l;
    for(l=0; l<segundos; l++){
        for(h = 0; h<10; h++){
            for (i = 0; i<100; i++){
                for(j = 0; j < 100; j++){
                    for(k = 0; k < 9; k++);
                }
            }
        }
    }
}

void UmSegundo(){
volatile unsigned char h, i, j, k;
        for (i = 0; i<200; i++){
                for(j = 0; j < 98; j++){
                    for(k = 0; k < 15; k++);




            }
        }
}
