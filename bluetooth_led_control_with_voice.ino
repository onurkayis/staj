#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int ledPin26 = 26; //pin 26 gpio26
const int ledPin27 = 27; //pin 27 gpio27

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialBT.begin("ESP32 TEST DEVICE"); // bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  pinMode(ledPin26, OUTPUT);
  pinMode(ledPin27, OUTPUT);
}

String redLedOn = "kırmızı ışığı aç";
String blueLedOn = "mavi işığı aç";
String redLedOff = "kırmızı ışığı kapat";
String blueLedOff = "mavi ışığı kapat";

void loop() {
  // put your main code here, to run repeatedly: 

  if(SerialBT.available()){
    String value = SerialBT.readString();
    value.toLowerCase();
    Serial.println(value);

  if(Serial.available()){
    String test = Serial.readString();
    Serial.println(test);
  }

    if(blueLedOn.equals(value)){
      digitalWrite(ledPin26, HIGH); //mavi ledi açma
      Serial.println("Blue led is ON!");
    }else if(blueLedOff.equals(value)){
      digitalWrite(ledPin26, LOW); //mavi ledi kapama
      Serial.println("Blue led is OFF!");
    }else if(redLedOn.equals(value)){
      digitalWrite(ledPin27, HIGH);  //kırmızı ledi açma
      Serial.println("Red led is ON!");
    }else if(redLedOff.equals(value)){
      digitalWrite(ledPin27, LOW); //kırmızı ledi kapama
      Serial.println("Red led is OFF!");
    }
  }
}
