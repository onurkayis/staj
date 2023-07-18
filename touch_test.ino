const int pin12 = 12; //touch pin gpio12

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.println("Esp32 touch test!");
}

void loop() {
  Serial.println(touchRead(pin12));
  delay(1000);
  // put your main code here, to run repeatedly:

}
