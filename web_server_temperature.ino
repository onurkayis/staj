#include <WiFi.h>
#include <WebServer.h>

#define REFERENCE_RESISTANCE  	5650.0
//#define NOMINAL_RESISTANCE  		4700.0
#define NOMINAL_RESISTANCE  		100000.0
#define NOMINAL_TEMPERATURE  		298.15//25 + 273.15
#define B_VALUE						  		10145.0
#define STM32_ANALOG_RESOLUTION 4095.0


const char* ssid = "SSTE";
const char* password = "password";

WebServer server(80);

const int pin34 = 34; //analog ADC1_CH6


void initWiFi(){
  
  Serial.print("İnternete bağlanılıyor");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Bağlantı başarısız oldu!");
  }else{
    Serial.print("\n");
    Serial.println("İnternete bağlanıldı!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }

}

int adcValue;  
float temperature;
float resistance;
float TempKelvin;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  initWiFi();

  server.on("/",handle_root);
  server.begin();
  Serial.println("HTTP server started!");

}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

  adcValue = analogRead(pin34);

  // resistance = REFERENCE_RESISTANCE /  (STM32_ANALOG_RESOLUTION /  adcValue - 1);
	// TempKelvin = log(resistance / NOMINAL_RESISTANCE);
  
	// /*
	// https://www.allaboutcircuits.com/industry-articles/how-to-obtain-the-temperature-value-from-a-thermistor-measurement/  
	// https://mehmettopuz.net/stm32-ve-ntc-sensoru-ile-sicaklik-olcme/.html
	// */
	// TempKelvin /= B_VALUE;
	// TempKelvin += (1 / NOMINAL_TEMPERATURE);
	// TempKelvin = 1 / TempKelvin;
	// temperature = TempKelvin - 273.15;

  double voltage = (float)adcValue / 4095.0 * 3.3;                // calculate voltage
  double Rt = 10 * voltage / (3.3 - voltage);                     //calculate resistance value of thermistor
  double tempK = 1 / (1 / (273.15 + 25) + log(Rt / 10) / 3950.0); //calculate temperature (Kelvin)
  double tempC = tempK - 273.15;                                  //calculate temperature (Celsius)
  Serial.printf("ADC value : %d,\tVoltage : %.2fV, \tTemperature : %.2fC\n", adcValue, voltage, tempC);
  delay(750);

  // Serial.print("ADC Value: ");
  // Serial.print(adcValue);
  // Serial.print(" - ");
  // Serial.print("Resistance: ");
  // Serial.print(resistance);
  // Serial.print(" - ");
  // Serial.print("Temperature: ");
  // Serial.println(temperature);

  delay(1000);
}


String HTML="<!DOCTYPE html>\n"
"<html>\n"
"<head>\n"
"\t\t<meta charset=\"utf-8\">\n"
"\t\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\">\n"
"\t\t<title>Sıcaklık Ölçme</title>\n"
"\t</head>\n"
"<body style=\"background-repeat: no-repeat;\n"
"background-position: center center;\n"
"background-attachment: fixed;\n"
"background-size: cover;\n"
"\" background=\"https://images.pexels.com/photos/1450353/pexels-photo-1450353.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=1\">\n"
"\n"
"<style> \n"
"#main {\n"
"margin-top:50px;\n"
"display: flex;\n"
"flex-direction: column;\n"
"align-items:center;\n"
"\n"
"}\n"
"\n"
"\n"
"#main2 {\n"
"display:flex;\n"
"flex-direction:row;\n"
"align-items:center;\n"
"}\n"
"#main3 {\n"
"display:flex;\n"
"flex-direction:row;\n"
"align-items:center;\n"
"margin-top:25px\n"
"}\n"
"\n"
"</style>\n"
"<h1 style=\"text-align: center; color:white; margin-top:25px; font-size: 40px;\">ESP32 WEB SERVER</h1>\n"
"<h1 style=\"text-align: center; color:white; margin-top:25px;\">Sıcaklık Ölçme</h1>\n"
"<div id=\"main\">\n"
"<div id=\"main2\">\n"
"<img src=\"https://cdn.mos.cms.futurecdn.net/jqkeHZrc7H2qJGzQkfkgnX.jpg\" alt=\"temperature\" style=\"width:75px; height:75px; border-radius:10%\"/>\n"
"<p style=\"color:black; margin-left:10px;\">Anlık sıcaklık değeri: °C</p>\n"
"</div>\n"
"\n"
"\n"
"<div id=\"main3\">\n"
"<img src=\"https://clipart-library.com/images/Lcd5ndBri.jpg\" alt=\"temperature\" style=\"width:75px; height:75px;margin-top:10px; border-radius:10%\"/>\n"
"<p style=\"color:black; margin-left:10px\">Anlık nem değeri: %</p>\n"
"</div>\n"
"</div>\n"
"\n"
"</body>\n"
"</html>";

void handle_root(){
  server.send(200, "text/html", HTML);
}

