#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "SmeTeste";
const char* password = "npaz5072";

short frequencies[8][7] = {
  {33, 37, 41, 43, 49, 55, 61}, // oitava 1     Inaudível
  {65, 73, 82, 87, 98, 110, 123}, // oitava 2   Inaudível
  {131, 147, 165, 174, 196, 220, 247}, // oitava 3 Ruim
  {261, 293, 329, 349, 392, 440, 494}, // oitava 4 OK
  {523, 587, 659, 698, 784, 880, 987}, // oitava 5 OK
  {1046, 1174, 1318, 1397, 1568, 1760, 1975}, // oitava 6 OK
  {2093, 2349, 2637, 2794, 3136, 3520, 3951}, // oitava 7 OK PADRÃO
  {4186, 4698, 5274, 5587, 6272, 7040, 7902}  // oitava 8 OK, mas tenho medo de aumentar além
};

//Default Values
short C = 2093;
short D = 2394;
short E = 2637;
short F = 2794;
short G = 3136;
short A = 3520;
short B = 3951;

//settando tresholds para os pinos
int set_ldr_treshold(short pin){
  int sensorValue = analogRead(pin);
  int treshold = sensorValue + 800;
  if (treshold > 4095){
    treshold = 4095;
  }
  return treshold;
}

int A0Treshold = set_ldr_treshold(36);
int A3Treshold = set_ldr_treshold(39);
int A6Treshold = set_ldr_treshold(34);
int A7Treshold = set_ldr_treshold(35);
int A4Treshold = set_ldr_treshold(32);
int A5Treshold = set_ldr_treshold(33);

char buzzer = 5; //insira o pin do digital output aqui
char noteDuration = 8;//insira duração da nota

//ledc, estava causando erros estranhos se eu n setasse
int freq = 2000;
int channel = 0;
int duty_cycle_res = 8;

TaskHandle_t wifi_task, make_sound;

void setup() {
  Serial.begin(115200);
  ledcSetup(channel, freq, duty_cycle_res);
  ledcAttachPin(buzzer, channel);
  delay(4000);
  //Serial.printf("SETUP esta rodando no core %d \n", xPortGetCoreID());

  xTaskCreatePinnedToCore(
    make_get_request,  // func
    "wifi_connection", // nome da task
    10000,             // tamanho do stack
    NULL,              // parâmetros da func
    0,                 // prioridade da task
    &wifi_task,        // referência ao task handler
    0);                // core em que irá rodar 

  xTaskCreatePinnedToCore(
    makeSound,     // func
    "buzzer_play", // nome da task
    10000,         // tamanho do stack
    NULL,          // parâmetros da func
    0,             // prioridade da task
    &make_sound,   // referência ao task handler
    1);            // core em que irá rodar 
}


void loop() {
  delay(10000); 
}

void makeSound(void * parameter){
  while(true){
    int sensorValueA0 = analogRead(36);
    //Serial.println(sensorValueA0);
    if (sensorValueA0 >= A0Treshold){
      //Serial.println("A0");
      tone(buzzer, C, noteDuration);
    }else{
      noTone(buzzer);
    };

    int sensorValueA3 = analogRead(39);
    if (sensorValueA3 >= A3Treshold){
      //Serial.println("A3");
      tone(buzzer, D, noteDuration);
    }else{
      noTone(buzzer);
    };

    int sensorValueA6 = analogRead(34);
    if (sensorValueA6 >= A6Treshold){
      //Serial.println("A6");
      tone(buzzer, E, noteDuration);
    }else{
      noTone(buzzer);
    };

    int sensorValueA7 = analogRead(35);
    if (sensorValueA7 >= A7Treshold){
      //Serial.println("A7");
      tone(buzzer, F, noteDuration);
    }else{
      noTone(buzzer);
    };

    int sensorValueA4 = analogRead(32);
    if (sensorValueA4 >= A4Treshold){
      //Serial.println("A4");
      tone(buzzer, G, noteDuration);
    }else{
      noTone(buzzer);
    };

    int sensorValueA5 = analogRead(33);
    if (sensorValueA5 >= A5Treshold){
      //Serial.println("A5");
      tone(buzzer, A, noteDuration);
    }else{
      noTone(buzzer);
    };
  }
}

void make_get_request(void * parameter){
  //Serial.printf("task do wifi esta rodando no core %d \n", xPortGetCoreID());
  while(true){
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED){
      delay(1000);
      //Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connection succeeded!!!!");
    if ((WiFi.status() == WL_CONNECTED)) {
      HTTPClient http;

      http.begin("https://sme-integracao.azurewebsites.net/frequencia");
      int httpCode = http.GET();
      StaticJsonDocument<200> doc;

      if (httpCode > 0) {
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
        DeserializationError erro = deserializeJson(doc, payload);

        int frequencia = doc["frequenciaNota"];
        Serial.println(frequencia);

        //int lower_index = payload.indexOf("Nota\"") + 5; //61
        //payload.substring(lower_index, lower_index+1);
        //Serial.println(lower_index);
        switch_frequency(frequencia);
      }
      else {
        //Serial.println("Error on HTTP request");
      }
      http.end();
    }
    //Serial.println("WIFI DISCONNECTED");
    WiFi.disconnect();
    delay(10000);
  }
}

void switch_frequency(int S){
  if (S >= 0 && S <= 7){
    C = frequencies[S][0];
    D = frequencies[S][1];
    E = frequencies[S][2];
    F = frequencies[S][3];
    G = frequencies[S][4];
    A = frequencies[S][5];
    B = frequencies[S][6];
  }else{
    //Serial.println("Oitava não disponível.");
  }
}

