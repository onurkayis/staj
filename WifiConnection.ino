#include <WiFi.h>

const char* ssid = "SSTE";
const char* password = "password";

void initWifi(){
  Serial.print("İnternete bağlanılıyor");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("İnternete bağlanılamadı.");
  }else{
    Serial.print("\n");
    Serial.println("İnternete bağlanıldı.");
    Serial.print("IP Address: ");
    Serial.print(WiFi.localIP());
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  initWifi();
}

void loop() {
  // put your main code here, to run repeatedly:

}
