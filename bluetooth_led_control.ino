#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int ledPin26 = 26; //pin 26 gpio26
const int ledPin27 = 27; //pin 27 gpio27

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialBT.begin("ESP32 device"); // bluetooth device name
  Serial.println("The device started, now you can pait it with bluetooth!");

  pinMode(ledPin26, OUTPUT);
  pinMode(ledPin27, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly: 
  if(SerialBT.available()){
    String value = SerialBT.readString();
    Serial.println(value);
    //ses algılamada bazı kelimelerin baş harfi büyük olarak algılandığı için if blokları böyle yazıldı
    if(value == "kırmızı ışığı aç" || "value == kırmızı Işığı aç"){
      digitalWrite(ledPin27, HIGH);  //kırmızı ledi yakma
      Serial.println("Red led is ON!");
    }else if(value == "kırmızı ışığı kapat" || "kırmızı Işığı kapat"){
      digitalWrite(ledPin27, LOW); //kırmızı ledi kapama
      Serial.println("Red led is OFF!");
    }else if(value == "mavi Işığı aç" || value == "mavi ışığı aç"){
      digitalWrite(ledPin26, HIGH); //mavi ledi yakma
      Serial.println("Blue led is ON!");
    }else if(value == "mavi Işığı kapat" || value == "mavi ışığı kapat"){
      digitalWrite(ledPin26, LOW); //mavi ledi kapama
      Serial.println("Blue led is OFF!");
    }
  } 
}
