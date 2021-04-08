/**********************************************************************************
* Código para: Gerar numeros de jogos de loterias e apresentar no terminal serial
* Autor: Pabllo Lins
* Data: 04/04/2021
* Placa: NodeMCU (ESP8266)
***********************************************************************************/

#include <Arduino.h>

/* Defines */
#define BotaoEnter 13 //Pino D7
#define BotaoVoltar 12 //Pino D6
#define BotaoEsquerda 0 //Pino D3
#define BotaoDireita 2 //Pino D4
#define BotaoCima 5 //Pino D1
#define BotaoBaixo 4 //Pino D2

/*  Protótipo de funções  */
void Megasena();
void Quina();
void Lotofacil();
char BotaoPressionado();
void Lotomania();

/*   Variáveis globais  */
String palavra;
String c;
char opcaoMenu;
int quantidade;
int aleatorio;
int contadorDebouncing = 0;


/* struct jogos  */
struct jogos{
  /* Método da struct */
  void Aleatorios(int quantidade, int RandonMax){
    int numeros[quantidade];
    int numerosOrdenados[quantidade];
    int menorNumero = RandonMax+1;
    int posicaoMenorNum = 0;
    int numAleatorio;
    int indice = 0;
    int contador = 0;

   for(indice = 0; indice < quantidade; indice++){
      numAleatorio = random(1, RandonMax); //a variaável recebe umnumero randomico
      if(indice > 0){
        for(contador = 0; contador < quantidade; contador++){//Laço para varrer e comparar se já existe o numero na lista      
          while(numAleatorio == numeros[contador]){
            numAleatorio = random(1, RandonMax); //a variaável recebe umnumero randomico
            contador=0;
          }
        }
      }
      numeros[indice] = numAleatorio; //salva o novo numero aleatório no array
    } 


    /*  Trecho para ordenação dos numeros de forma crescente */  
    for(contador = 0; contador < quantidade; contador++){    
      for(indice = 0; indice < quantidade; indice++){   
        if(menorNumero > numeros[indice]){ 
          if(numeros[indice] != numeros[posicaoMenorNum]){                        
            menorNumero = numeros[indice];
            posicaoMenorNum = indice;
          }
        }
      }  
      numeros[posicaoMenorNum] = RandonMax+1;
      numerosOrdenados[contador] = menorNumero;
      menorNumero = RandonMax+1;
    }

 
    Serial.println("NUMEROS ALEATÓRIOS GERADOS: "); 
    for(indice = 0; indice < quantidade; indice++){
      if(indice > 0){
        if((indice%10) == 0){
          Serial.println();
        }
      }
      Serial.print(numerosOrdenados[indice]);
      Serial.print(" ");
    }

    Serial.println();
    delay(100);
  }  
};

jogos geradorDeNumeros; /* Inicia uma structure do tipo jogos */


//________________________________________________________________________________________________________________
void setup() {
  delay(50);
  pinMode(BotaoEnter, INPUT_PULLUP);
  pinMode(BotaoVoltar, INPUT_PULLUP);
  pinMode(BotaoEsquerda, INPUT_PULLUP);
  pinMode(BotaoDireita, INPUT_PULLUP);
  pinMode(BotaoCima, INPUT_PULLUP);
  pinMode(BotaoBaixo, INPUT_PULLUP);
  
  Serial.begin(9600); //ESTA DEFINIÇÂO ANTES DAS LINHAS ACIMAS, pois deu problema no terminal
  Serial.println();
  Serial.println(" ______________________________________________________");
  Serial.println("|____________GERADOR_DE_NUMEROS_DE_LOTERIAS____________|");    
  Serial.println("|                      PRESSIONE:                      |");
  Serial.println("|                    CIMA-->Lotofacil                  |");
  Serial.println("| ESQUERDA-->MegaSena                 DIREITA-->Quina  |");
  Serial.println("|____________________BAIXO-->Lotomania_________________|");
  delay(200);
}
//________________________________________________________________________________________________________________



//________________________________________________________________________________________________________________
void loop() {
  switch (BotaoPressionado()){
    case 'e' : contadorDebouncing = 0; Megasena(); delay(100); break;
    case 'D' : contadorDebouncing = 0; Quina(); break;
    case 'C' : contadorDebouncing = 0; Lotofacil(); break;
    case 'B' : contadorDebouncing = 0; Lotomania(); break;
    default: break;
  }    
}
//________________________________________________________________________________________________________________




//________________________________DECLARAÇÔES_DAS_FUNCOES______________________________________________________


//________________FUNCAO_MEGASENA
void Megasena(){
  bool variavelDeControle = false;
  int dezena = 6;
  int dezenaOld = 0;
  int cont = 0;

  Serial.println();
  Serial.println(" _______________________MEGASENA_______________________");
  Serial.println("|        Válido jogos entre 6 e 15 numeros.            |");
  Serial.println("|       Pressione as teclas CIMA e BAIXO para          |");
  Serial.println("|       informar a quantidade de numeros               |");
  Serial.println("|    que voce pretende jogar, depois pressione ENTER   |");
  Serial.println("|______________________________________________________|");
  Serial.print("Quantidade de numeros: ");
  Serial.println(dezena);

  while(variavelDeControle == false){
    while (BotaoPressionado() == '0'){
      switch (BotaoPressionado()){
        case 'C' : if(dezena < 15) dezena++; cont = 0; break;
        case 'B' : if(dezena > 6) dezena--; cont = 0; break;
        case 'E' : geradorDeNumeros.Aleatorios(dezena, 60); variavelDeControle = true; break;      
        case 'V' : Serial.println(); Serial.println("Voltando ao menu inicial..."); cont = 24000; break;          
      } 

      if(variavelDeControle == true){
        for(int contador = 0; contador < 12000; contador++){
          delay(10); //10 x 12000(contador) = 120000(dois minutos)
          if(BotaoPressionado() == 'V'){
            ESP.reset();
          }         
        }
        ESP.restart();
        break;
      }

      if(cont == 24000){ //Se passarem  minutos sem que tenha-se pressionado nada, o programa volta ao menu principal
        ESP.restart(); 
      }

      cont++;
      delay(5);
    }
    
    if(variavelDeControle == false){
      if(dezena != dezenaOld){
        dezenaOld = dezena;
        Serial.print("Quantidade de numeros: ");
        Serial.println(dezena);
      }
    }
  }
}




//________________FUNCAO_QUINA
void Quina(){
  bool variavelDeControle = false;
  int dezena = 5;
  int dezenaOld = 0;
  int cont = 0;

  Serial.println();
  Serial.println("|________________________QUINA_________________________|");
  Serial.println("|        Válido jogos entre 5 e 15 numeros             |");
  Serial.println("|       Pressione as teclas CIMA e BAIXO para          |");
  Serial.println("|       informar a quantidade de numeros               |");
  Serial.println("|    que voce pretende jogar, depois pressione ENTER   |");
  Serial.println("|______________________________________________________|");
  Serial.print("Quantidade de numeros: ");
  Serial.println(dezena);

  while(variavelDeControle == false){
    while (BotaoPressionado() == '0'){
      switch (BotaoPressionado()){
        case 'C' : if(dezena < 15) dezena++; cont = 0; break;
        case 'B' : if(dezena > 5) dezena--; cont = 0; break;
        case 'E' : geradorDeNumeros.Aleatorios(dezena, 80); variavelDeControle = true; break;      
        case 'V' : Serial.println(); Serial.println("Voltando ao menu inicial..."); cont = 24000; break;          
      } 

      if(variavelDeControle == true){
        for(int contador = 0; contador < 12000; contador++){
          delay(10); //10 x 12000(contador) = 120000(dois minutos)
          if(BotaoPressionado() == 'V'){
            ESP.reset();
          }         
        }
        ESP.restart();
        break;
      }

      if(cont == 24000){ //Se passarem  minutos sem que tenha-se pressionado nada, o programa volta ao menu principal
        ESP.restart(); 
      }

      cont++;
      delay(5);
    }
    
    if(dezena != dezenaOld){
      dezenaOld = dezena;
      Serial.print("Quantidade de numeros: ");
      Serial.println(dezena);
    }
  }
}


//________________FUNCAO_LOTOFACIL
void Lotofacil(){
  bool variavelDeControle = false;
  int dezena = 15;
  int dezenaOld = 0;
  int cont = 0;

  Serial.println();
  Serial.println("|_____________________LOTOFACIL________________________|");
  Serial.println("|        Válido jogos entre 15 e 20 numeros            |");
  Serial.println("|       Pressione as teclas CIMA e BAIXO para          |");
  Serial.println("|       informar a quantidade de numeros               |");
  Serial.println("|    que voce pretende jogar, depois pressione ENTER   |");
  Serial.println("|______________________________________________________|");
  Serial.print("Quantidade de numeros: ");
  Serial.println(dezena);

  while(variavelDeControle == false){
    while (BotaoPressionado() == '0'){
      switch (BotaoPressionado()){
        case 'C' : if(dezena < 20) dezena++; cont = 0; break;
        case 'B' : if(dezena > 15) dezena--; cont = 0; break;
        case 'E' : geradorDeNumeros.Aleatorios(dezena, 25); variavelDeControle = true; break;      
        case 'V' : Serial.println(); Serial.println("Voltando ao menu inicial..."); cont = 24000; break;         
      } 

      if(variavelDeControle == true){
        for(int contador = 0; contador < 12000; contador++){
          delay(10); //10 x 12000(contador) = 120000(dois minutos)
          if(BotaoPressionado() == 'V'){
            ESP.reset();
          }         
        }
        ESP.restart();
        break;
      }

      if(cont == 24000){ //Se passarem  minutos sem que tenha-se pressionado nada, o programa volta ao menu principal
        ESP.restart(); 
      }

      cont++;
      delay(5);
    }
    
    if(dezena != dezenaOld){
      dezenaOld = dezena;
      Serial.print("Quantidade de numeros: ");
      Serial.println(dezena);
    }
  }
}


//________________FUNCAO_LOTOMANIA
void Lotomania(){
  bool variavelDeControle = false;
  int dezena = 50;
  int dezenaOld = 0;
  int cont = 0;

  Serial.println();
  Serial.println("|_____________________LOTOMANIA________________________|");
  Serial.println("|              Válido jogos 50 numeros                 |");
  Serial.println("|       Pressione as teclas CIMA e BAIXO para          |");
  Serial.println("|       informar a quantidade de numeros               |");
  Serial.println("|    que voce pretende jogar, depois pressione ENTER   |");
  Serial.println("|______________________________________________________|");
  Serial.print("Quantidade de numeros: ");
  Serial.println(dezena);

  while(variavelDeControle == false){
    while (BotaoPressionado() == '0'){
      switch (BotaoPressionado()){
        case 'C' : if(dezena < 50) dezena++; cont = 0; break;
        case 'B' : if(dezena > 0) dezena--; cont = 0; break;
        case 'E' : geradorDeNumeros.Aleatorios(dezena, 100); variavelDeControle = true; break;      
        case 'V' : Serial.println(); Serial.println("Voltando ao menu inicial..."); cont = 24000; break;         
      } 

      if(variavelDeControle == true){
        for(int contador = 0; contador < 12000; contador++){
          delay(10); //10 x 12000(contador) = 120000(dois minutos)
          if(BotaoPressionado() == 'V'){
            ESP.reset();
          }         
        }
        ESP.restart();
        break;
      }

      if(cont == 24000){ //Se passarem  minutos sem que tenha-se pressionado nada, o programa volta ao menu principal
        ESP.restart(); 
      }

      cont++;
      delay(5);
    }
    
    if(dezena != dezenaOld){
      dezenaOld = dezena;
      Serial.print("Quantidade de numeros: ");
      Serial.println(dezena);
    }
  }
}


//________________FUNCAO_PARA_SELECIONAR_O BOTAO_PRESSIONADO
char BotaoPressionado(){
 if(!digitalRead(BotaoVoltar) || !digitalRead(BotaoEnter) || !digitalRead(BotaoEsquerda) || !digitalRead(BotaoDireita) || !digitalRead(BotaoCima) || !digitalRead(BotaoBaixo)){
    contadorDebouncing++;

    if(contadorDebouncing == 10){ //ROTINA DE DEBOUNCE
      delay(30);      
      if(digitalRead(BotaoVoltar) == 0){/*Serial.println("BOTAO B");*/ opcaoMenu = 'V';}
      else if(digitalRead(BotaoEsquerda) == 0){/*Serial.println("BOTAO 1");*/ opcaoMenu = 'e';}
      else if(digitalRead(BotaoDireita) == 0){/*Serial.println("BOTAO 2");*/ opcaoMenu = 'D';}
      else if(digitalRead(BotaoCima) == 0){/*Serial.println("BOTAO 3");*/ opcaoMenu = 'C';}
      else if(digitalRead(BotaoBaixo) == 0){/*Serial.println("BOTAO 4");*/ opcaoMenu = 'B';}
      else if(digitalRead(BotaoEnter) == 0){/*Serial.println("BOTAO E");*/ opcaoMenu = 'E';}
    }
  }else{
    contadorDebouncing = 0;
    opcaoMenu = '0';
  }

  return opcaoMenu;
}
