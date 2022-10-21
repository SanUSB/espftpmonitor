/*
Exemplo de código para enviar para o banco de dados online um valor analógico representado 
pela leitura de tensão de um potenciômetro e mostra esse valor no gráfico do ftpmonitor
*/
#include <NTPClient.h> //Instalar a biblioteca https://github.com/SanUSB/NTPClient
#include <time.h>
#include <WiFi.h>
//#include <WiFiManager.h>

const char* rede = "**************"; 
const char* senha = "*************";     

const char* host = "sanusb.org"; 

char url[100];

WiFiClient cliente; //Cria o objeto cliente

int sensorPin = 34;  //Porta do sensor Analógico do potenciometro
int ledPin = 2;      //Porta do Led

int timezone = -3; //Ajustar a hora
int dst = 0;

//------------------------------------------------------------------------------------//

void setup() {
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200); // inicializa a porta serial com 115200 baud
  Serial.println(rede);
  WiFi.begin(rede, senha); //conecta a Rede
  Serial.println("Conectando ao WIFI...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }
  Serial.print("\nIP: ");
  Serial.println(WiFi.localIP()); //Imprime o IP

  
  configTime(timezone * 3600, dst * 0, "pool.ntp.org", "time.nist.gov");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
}

//------------------------------------------------------------------------------------//
void loop() {
  
  while (!cliente.connect(host, 80))//Aguarda a conexão imprimindo |
  {
    delay(500);
    Serial.print('|');
  }

  if (cliente.connect(host, 80))
  {
    Serial.println("Conectado e enviando requisicao HTTP");
  
    time_t now;
    struct tm * timeinfo;
    time(&now);
    //timeinfo = gmtime(&now);
    timeinfo = localtime(&now);
    
    sprintf(url, "GET /ftpmonitor/getESP_condut.php?action=send1&condut=%d&date=%02d-%02d-%02d-%02d:%02d:%02d", analogRead(sensorPin), timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec); 
    
    cliente.print(String(url));
    Serial.println(String(url));
    cliente.print (" HTTP/1.1\r\n");
    cliente.print ("Host: ");
    cliente.print (host);
    cliente.print ("\r\nConnection: close\r\n\r\n");
    
    Serial.println("Aguardando resposta do servidor...");
    while (!cliente.available()) {
      Serial.print('*');
      delay(500);
    }
    
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
    digitalWrite(ledPin, HIGH);
    delay(2000);
    digitalWrite(ledPin, LOW);
    delay(2000);
  }
}
