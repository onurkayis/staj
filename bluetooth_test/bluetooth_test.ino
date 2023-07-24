#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialBT.begin("Esp32 test device");
  Serial.println("The device started, now you can connect!");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    SerialBT.write(Serial.read());
  }
  if(SerialBT.available()){
    Serial.write(SerialBT.read());
  }
  delay(20);
}
