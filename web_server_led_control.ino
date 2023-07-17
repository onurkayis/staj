#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "SSTE";
const char* password = "password";

const int output26 = 26; // gpio 26
const int output27 = 27; // gpio 27

WebServer server(80);

void initWifi(){
  Serial.print("İnternete bağlanılıyor");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.print("\n");

  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Bağlantı başarısız oldu!");
  }else{
    Serial.print("İnternete bağlanıldı!\n");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
}

void setup() {
  // put your setup code here, to run once:



  Serial.begin(115200);

  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);

  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);

  initWifi();

  server.on("/", handle_root);
  server.on("/26/on", led_control_gpio26_on);
  server.on("/26/off", led_control_gpio26_off);
  server.on("/27/on", led_control_gpio27_on);
  server.on("/27/off", led_control_gpio27_off);


  server.begin();
  Serial.println("HTTP server started!");
  delay(500);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();


}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<head>\
<title>ESP32 Web Server</title>\
<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
<link rel=\"icon\" href=\"data:,\">\
<style>\
html {\
font-family: Helvetica;\
display: inline-block;\
margin: 0px auto;\
text-align: center;\
}\
.button {\
background-color: #4CAF50;\
border: none;\
color: white;\
padding: 16px 40px;\
text-decoration: none;\
font-size: 30px;\
margin: 2px;\
cursor: pointer;\
}\
.button2 {\
background-color: red;\
}\
</style>\
</head>\
<body>\
<h1>ESP32 Web Server</h1>\
<p>GPIO 26 - State</p>\
<p><a href=\"/26/on\"><button class=\"button\">ON</button></a><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>\
<p>GPIO 27 - State</p>\
<p></p>\<a href=\"/27/on\"><button class=\"button\">ON</button></a><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>\
</body>\
</html>";

void handle_root(){
  server.send(200, "text/html", HTML);
}

void led_control_gpio26_on(){
  server.send(200, "text/html", HTML);
  digitalWrite(output26, HIGH);
  Serial.println("GPIO 26 is ON");
}

void led_control_gpio26_off(){
  server.send(200, "text/html", HTML);
  digitalWrite(output26, LOW);
  Serial.println("GPIO 26 is OFF");
}

void led_control_gpio27_on(){
  server.send(200, "text/html", HTML);
  digitalWrite(output27, HIGH);
  Serial.println("GPIO 27 is ON");
}

void led_control_gpio27_off(){
  server.send(200, "text/html", HTML);
  digitalWrite(output27, LOW);
  Serial.println("GPIO 27 is OFF");
}
