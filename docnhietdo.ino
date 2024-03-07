
#include <Firebase.h>
#include <FirebaseESP8266.h>




#include <ESP8266Firebase.h>
#include <DHT.h>
#include  <ESP8266WiFi.h>

#define FIREBASE_HOST "https://hehe-8fbe3-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "jlYmbXJbTM4v30SK3przrvPTyMN4C7pAFTcnXBjn"
#define WIFI_SSID "IOT_AI LAB" // Thay đổi tên wifi của bạn
#define WIFI_PASSWORD "Y3aDsrt3" // Thay đổi password wifi của bạn
#define DHTPIN 14    // Chân dữ liệu của DHT 11 , với NodeMCU chân D5 GPIO là 14
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
FirebaseData fbdo;

void setup() {

  Serial.begin(9600);
  delay(1000);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Dang ket noi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  dht.begin();
  Serial.println ("");
  Serial.println ("Da ket noi WiFi!");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Đọc nhiệt độ theo độ C

  for (int j = 0; j < 360; j++) {
   Serial.println(t=h);
   delay(10);
  }
  delay(200);

}
