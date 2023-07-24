#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int ledPin26 = 26;
const int ledPin27 = 27;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialBT.begin("ESP32 TEST DEVICE");
  Serial.println("The device is started, now you can pair it with bluetooth");


  pinMode(ledPin26, OUTPUT);
  pinMode(ledPin27, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(SerialBT.available()){

    char value = SerialBT.read();
    Serial.println(value);

    if(value == '1'){
      digitalWrite(ledPin26, HIGH);
    }else if(value == '0'){   
      digitalWrite(ledPin26, LOW);
    }else if(value == '2'){
      digitalWrite(ledPin27, HIGH);
    }else if(value == '3'){
      digitalWrite(ledPin27, LOW);
    }

  }
}
