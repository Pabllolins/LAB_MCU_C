///////////////////////Carrega as bibliotecas/////////////////////////////
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>//biblioteca para trabalhar com os sensores DHT
#include <NTPClient.h> //biblioteca para trabalhar com Network Time Protocol
#include <WiFiUdp.h> //biblioteca para trabalhar com User Datagram Protocol, protocolo leve para receber dados de NTP
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <Adafruit_Sensor.h>
#include <stdint.h>
/////////////////////////////////////////////////////////////////////////


////////////////////////////Define_os_pinos////////////////////////////
String Alarme = "Alarme";
String Lampada_Telhado = "Lampada Telhado";
String disponivel = "Disponivel";//saida vazia
String lampada_da_escada = "Lampadas da escada";
#define RELE_NO    false// Set to true to define rele as NOORMAL ABERTO (NO)
#define NUMERO_RELES  4// Set number of reles
#define NOME_SAIDAS 4
int releGPIOs[NUMERO_RELES] = {12, 13, 14, 15};// Assign each GPIO to a rele
String nomeGPIOs[20] = {Alarme, Lampada_Telhado, disponivel, lampada_da_escada};
//GPIO 12 - Pino D6 - rele Alarme
//GPIO 13 - (PROBLEMA DE ACIONAMENTO) - Pino D7 - Rele Lampada Telhado
//GPIO 14 - Pino D5 - rele1 (disponível)
//GPIO 15 - Pino D8 - rele da lampada da escada
const char* PARAM_INPUT_1 = "rele";
const char* PARAM_INPUT_2 = "estado";
/////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
String releestado(int numrele) {
  if (RELE_NO) {
    if (digitalRead(releGPIOs[numrele - 1])) {
      return "";
    }
    else {
      return "checked";
    }
  }
  else {
    if (digitalRead(releGPIOs[numrele - 1])) {
      return "checked";
    }
    else {
      return "";
    }
  }
  return "";
}
/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////Define de saidas///////////////////////////////////////////
#define LedPiloto 4     //define o Led piloto na GPIO4 - Pino D2
#define PIN_SENSOR  0   //definição do pino de entrada do sensor de presença infravermelho (PIR) GPIO 0 - Pino D3
#define GPIO5_PinoD1 5  //Habilita a GPIO5 para entradas futuras GPIO 5 - Pino D1
/////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////Entradas de credenciais WiFi////////////////////////////
const char* ssid = "yourSSID"; //SSID
const char* password = "yourPASSWORD"; //Senha de rede
/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////Definiçoes sobre o DHT///////////////////////////////////////////
#define DHTPIN 2     // define o pino digital conectado ao DHT GPIO 2 - Pino D4
#define DHTTYPE    DHT11     // Define qual tipo de sensor DHT está sendo ultilizado
DHT dht(DHTPIN, DHTTYPE); //função da biblioteca DHT, especifica o pino e o sensor

float Temperature = 0.0; //declara uma variável flutuante para temperatura
float Humidity = 0.0; //declara uma variável flutuante para umidade
/////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////Outras variáveis ////////////////////////////
bool presenca; //variável para o sensor de presença
AsyncWebServer server(80); // Inicia o objeto servidor web na porta 80
unsigned long previousMillis = 0;    // will store last time DHT was updated
const long interval = 300000;  // atualização do DHT a cada 5 mimutos (tempo em milisegundos)
/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////Parametros para atualização de NTP///////////////////////////
const long utcOffsetInSeconds = -10800; //Ajuste da parametro de zona de horário = (São Paulo = -3), (Uma hora em segundos = 3600), logo -3*3600 = -10800
char daysOfTheWeek[7][15] = {"Domingo", "Segunda-feira", "Terca-feira", "Quarta-feira", "Quinta-feira", "Sexta-feira", "Sabado"};
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////Página HTML//////////////////////////////////////////
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px}
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 34px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
    input:checked+.slider {background-color: #2196F3}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
</body>
  <h2>CONTROLE CHALE</h2>
<p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i>
    <span class="dht-labels">Temperatura</span>
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i>
    <span class="dht-labels">Humidade</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">%</sup>
  </p>
</body>
<script>

///////////////////////////////HTML Botões, temperatura e humidade////////////////////////////
setInterval(function ( ) {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if (this.readyState == 4 && this.status == 200) {
document.getElementById("temperature").innerHTML = this.responseText;
}
};
xhttp.open("GET", "/temperature", true);
xhttp.send();
}, 10000 ) ;


setInterval(function ( ) {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if (this.readyState == 4 && this.status == 200) {
document.getElementById("humidity").innerHTML = this.responseText;
}
};
xhttp.open("GET", "/humidity", true);
xhttp.send();
}, 10000 ) ;
</script>

%BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
var xhr = new XMLHttpRequest();
if(element.checked){ xhr.open("GET", "/update?rele="+element.id+"&estado=1", true); }
else { xhr.open("GET", "/update?rele="+element.id+"&estado=0", true); }
xhr.send();
}</script>
</body>
</html>
)rawliteral";
/////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////Função de preenchimento do espaço reservado com botões////////////////////////////
String processor(const String& var){
if(var == "BUTTONPLACEHOLDER"){
String buttons ="";

for(int i=1; i<=NUMERO_RELES; i++){
String releestadoValue = releestado(i);
//buttons+= "<h4>" + nomeGPIOs[i-1] + " " /*+ releGPIOs[i-1]*/ + "</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(i) + "\" "+ releestadoValue +"><span class=\"slider\"></span></label>";
//Inversão na apresentação na pagina web para melhor utilização (personalização)
buttons+= "<h4>" + nomeGPIOs[4-i] + " " /*+ releGPIOs[i-1]*/ + "</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(5-i) + "\" "+ releestadoValue +"><span class=\"slider\"></span></label>";
}

return buttons;
}
//return String();
return String(Humidity);
return String(Temperature);
}
/////////////////////////////////////////////////////////////////////////////////////////

String releestado();//protótipo de função
void MostraDataNaSerial(); //protótipo de função
void conectarWifi(); //protótipo de função
void atualizaNTP(); //protótipo de função
void LedConexao(); //protótipo de função
/////////////////////////////////////////////////////////////////////////////////////////


/////////////////////FUNÇAO SETUP/////////////////////////////////////////////////////////
void setup(){
// Serial port for debugging purposes
delay(500);
Serial.begin(115200);
delay(500);
dht.begin();
pinMode(LedPiloto, OUTPUT);
digitalWrite(LedPiloto, HIGH);

// Set all reles to off when the program starts - if set to Normally Open (NO), the rele is off when you set the rele to HIGH
for(int i=1; i<=NUMERO_RELES; i++){
pinMode(releGPIOs[i-1], OUTPUT);
if(RELE_NO){
digitalWrite(releGPIOs[i-1], HIGH);
}
else{
digitalWrite(releGPIOs[i-1], LOW);
}
}

Serial.println();
Serial.println();
Serial.print("ESP Board MAC Address:  ");
Serial.println(WiFi.macAddress());

delay(500);
conectarWifi();

timeClient.begin();
timeClient.update(); //Solicita a atualização de horário ao servidor NTP
MostraDataNaSerial();
Serial.println();


// Route for root / web page
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/html", index_html, processor);
});

server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/plain", String(Temperature).c_str());
});

server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/plain", String(Humidity).c_str());
});

// Send a GET request to <ESP_IP>/update?rele=<inputMessage>&estado=<inputMessage2>
server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
String inputMessage;
String inputParam;
String inputMessage2;
String inputParam2;
// GET input1 value on <ESP_IP>/update?rele=<inputMessage>
if (request->hasParam(PARAM_INPUT_1) & request->hasParam(PARAM_INPUT_2)) {
inputMessage = request->getParam(PARAM_INPUT_1)->value();
inputParam = PARAM_INPUT_1;
inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
inputParam2 = PARAM_INPUT_2;
if(RELE_NO){
Serial.print("NO ");
digitalWrite(releGPIOs[inputMessage.toInt()-1], !inputMessage2.toInt());
}
else{
Serial.print("NC ");
digitalWrite(releGPIOs[inputMessage.toInt()-1], inputMessage2.toInt());
}
}
else {
inputMessage = "No message sent";
inputParam = "none";
}

//Serial.println(inputMessage + inputMessage2);
Serial.print("Saída: ");
Serial.print(inputMessage);
Serial.print(" = ");
Serial.println(inputMessage2);
request->send(200, "text/plain", "OK");
});
/////////////////////////////////////////////////////////////////////////////////////////


/////////////////////FUNÇAO LOOP/////////////////////////////////////////////////////////
}

void loop() {
//if (client() == true ) {
//SyncClient
unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= interval) {
previousMillis = currentMillis; // save the last time you updated the DHT values
float newT = dht.readTemperature();// Read temperature as Celsius (the default)
if (isnan(newT)) {     // if temperature read failed, don't change t value
Serial.println("Falha na leitura do sensor de Temperatura!");
}
else {
Temperature = newT;
Serial.println(Temperature);
}
// Read Humidity
float newH = dht.readHumidity();
if (isnan(newH)) { // if humidity read failed, don't change h value
Serial.println("Falha na leitura do sensor de humidade!");
}
else {
Humidity = newH;
Serial.println(Humidity);
}
}
//}

//Serial.println("tempo em millis decorrido");
//Serial.println(millis());
//Serial.println("");

//if (millis() > 300000){ //reinicia o ESP e a conexão a cada 5 minutos
if (millis() > 21600000){ //reinicia o ESP e a conexão a cada 6 horas
Serial.println("");
Serial.print("ESP reiniciando por tempo limite ");
Serial.println("");
 ESP.restart();
}
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
void MostraDataNaSerial() {
//Serial.println("");
Serial.print("Dia e hora atual: ");
Serial.print(daysOfTheWeek[timeClient.getDay()]);
Serial.print(" as ");
Serial.print(timeClient.getHours());
Serial.print(":");
Serial.print(timeClient.getMinutes());
Serial.print(":");
Serial.println(timeClient.getSeconds());
//Serial.print("getFormattedTime: ");
//Serial.println(timeClient.getFormattedTime());
}
/////////////////////////////////////////////////////////////////////////////////////////

////////////////////////Conexão ao Wi-Fi/////////////////////////////////////
void conectarWifi() {
delay(500);
WiFi.begin(ssid, password);
delay(500);
Serial.print("Conectando ao WiFi");
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
if (millis() > 120000) //se ao tentar conectar por 2 minutos não conseguir, reinicia o ESP
{
Serial.println("");
Serial.print("ESP reiniciando por falha na conexao com a rede ");
Serial.println("");
ESP.restart();
}
}

if (WiFi.status() == WL_CONNECTED) { // Print local IP address and start web server
Serial.println("");
Serial.print("Conectado a: ");
Serial.println(ssid);
Serial.print("Com IP: ");
Serial.println(WiFi.localIP());
LedConexao();
}
// Start server
server.begin();
Serial.println("Servidor Web iniciado");
}
/////////////////////////////////////////////////////////////////////////


////////////////////////atualizaNTP/////////////////////////////////////
void atualizaNTP()
{
timeClient.begin();
timeClient.update(); //Solicita a atualização de horário ao servidor NTP
//server.begin();
//Serial.println("Servidor Web iniciado");
MostraDataNaSerial();
}
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
void LedConexao() {
  digitalWrite(LedPiloto, LOW);
  delay(200);
  digitalWrite(LedPiloto, HIGH);
  delay(200);
  digitalWrite(LedPiloto, LOW);
  delay(200);
  digitalWrite(LedPiloto, HIGH);
  delay(200);
  digitalWrite(LedPiloto, LOW);
  delay(200);
  digitalWrite(LedPiloto, HIGH);
}
/////////////////////////////////////////////////////////////////////////////////////////
