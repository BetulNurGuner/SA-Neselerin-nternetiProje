//Betül Nur Güner --- B181210068 --- Nesnelerin İnterneti Dersi Proje Görevi

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#define FIREBASE_HOST "https://nesintproodev.firebaseio.com/" 
#define FIREBASE_AUTH "XNndBzpZ1k3XhtjqVHKkAOEOZVWHwRoNewm1pldA" 
#define WIFI_SSID "Gizli***" 
#define WIFI_PASSWORD "Gizli***" 

FirebaseData firebaseData;

#define echoPin D7
#define trigPin D6
#define buzzerPin 14

int maxMesafe=50;
int minMesafe = 1;


void setup() {
    Serial.begin(9600); 
    // Wifi bağlantısı yapılıyor 
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
    Serial.print("connecting"); 
 
    while (WiFi.status() != WL_CONNECTED) 
    { 
        Serial.print("."); 
        delay(500); 
    } 
    Serial.println(); 
    Serial.print("connected: "); 
    Serial.println(WiFi.localIP()); 
 
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
 
    Firebase.reconnectWiFi(true);

    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);
    pinMode(buzzerPin,OUTPUT);  
}

void loop() {
  
    int olcum = mesafe(maxMesafe, minMesafe);
    melodi(olcum*10);
    //Firebase veriyi yazdır
    Firebase.setInt(firebaseData, "/table/mesafe", olcum);
    delay(5000);
}

int mesafe(int maxrange, int minrange)
{
  long duration, distance;

  digitalWrite(trigPin,0);
  delayMicroseconds(2);
  digitalWrite(trigPin,1);
  delayMicroseconds(10);
  digitalWrite(trigPin,0);

  duration = pulseIn(echoPin,1);
  distance = duration/58.2;
  delay(50);

  if(distance >= maxrange || distance <= minrange)
  return 0;
  return distance;
  
}

int melodi(int dly)
{
  tone(buzzerPin,500);
  delay(dly);
  noTone(buzzerPin);
  delay(dly);
}
