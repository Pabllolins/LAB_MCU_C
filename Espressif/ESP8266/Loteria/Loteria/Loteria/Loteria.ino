
String palavra, c, aposta, palavraAposta;
uint16_t quantidade, aleatorio, numAposta;
int numMax, numMin, numeroDaSorte;//Variavel que definirá o maior numero do jogo

char caractereUm;

//void gerarAleatorios(uint16_t);
void gerarAleatorios();
void Megasena();
void Quina();
void Lotofacil();
int getInt();

void setup() {
delay(300);
Serial.begin(9600);
Serial.println();
Serial.println();
Serial.println("___Programa gerador de numeros de loteria___");
Serial.println("Digite a palavra abaixo e na sequencia digite @ ");
Serial.println("Mega@ - para Megasena");
Serial.println("Quina@ - para Quina");
Serial.println("Lotofacil@ - para Lotofacil");
Serial.println();
Serial.println();
Serial.println("Boa Sorte !!!");
Serial.println();
//Serial.read();
}

void loop() {
  while(Serial.available() > 0){
    c = (char)Serial.read();
      palavra += c;
    if(c == "@"){
      break;
    }

  }

  if(palavra == "superUser@"){
    delay(500);
    Serial.println("Funções de superUser!!!");
    Serial.println();
    return;
  }

  else if(palavra == "Mega@"){
    numMin = 1; // numero minimo permitido no jogo
    numMax = 60; // numero maximo permitido no jogo
    Serial.end();
    Megasena();
    }

    else if(palavra == "Quina@"){
      numMin = 1; // numero minimo permitido no jogo
      numMax = 80; // numero maximo permitido no jogo
      Serial.println("Valor invalido");
        }

      else if(palavra == "Lotofacil@"){
        numMin = 1; // numero minimo permitido no jogo
        numMax = 25; // numero maximo permitido no jogo
        Serial.println("Valor invalido");
          }

        else if(palavra == "Lotomania@"){
          numMin = 0; // numero minimo permitido no jogo
          numMax = 99; // numero maximo permitido no jogo
          Serial.println("Valor invalido");
            }

  c = ""; //zera o valor da variavel
  palavra = ""; //zera o valor da variavel
  numMax = 0;
  aposta = "";
  palavraAposta = "";
  numAposta = 0;
  numeroDaSorte = 0;
  delay(500); // DELAY DE 1 segundo
}

void Megasena(){
Serial.begin(9600);
  delay(200);
  Serial.println("___MEGA SENA___");
  Serial.println();
  delay(200);
  Serial.println("Digite a quantidade de numeros que voce pretende jogar");
  Serial.println("As quantidades permitidas sao: 6, 7, 8, 9, 10, 11, 12, 13, 14 a 15");
  Serial.println("Ao final digite @");
  Serial.println("EXEMPLO: 7@");
  delay(200);

  while(Serial.available() > 0){
    aposta = (char)Serial.read();
    if(aposta != " "){
    palavraAposta += aposta;
  }
    if(aposta == "@"){
      break;
    }

  }
      numAposta = getInt(&palavraAposta[0]);

      Serial.print("valor recebido ");
      Serial.println(&palavraAposta[0]);

    if((6 <= numAposta) && ( numAposta <= 15)) {
          //Serial.print("Valor numeros da aposta ");
          //Serial.println(numAposta);
          gerarAleatorios();
    }else{
      Serial.println("Valor abaixo de 6 ou maior do que 15!");
    }
    delay(200);
}

void gerarAleatorios(){
Serial.println("Estes sao seus numeros da sorte! ");
int i = 0;
while (i < numAposta){
numeroDaSorte = random(numMin, numMax); //radom(valormin, valormax);
Serial.print(" - ");
Serial.print(numeroDaSorte);
i++;
}
Serial.println();
Serial.println("Boa sorte");
}


int getInt(String texto){ //Função de valor inteiro que recebe uma string e retorna uma inteiro
  int temp = texto.length() + 1;
  char buffer[temp];
  texto.toCharArray(buffer, temp);
  int num = atoi(buffer);
  return num; //Ao final da função retorna um inteiro
}
