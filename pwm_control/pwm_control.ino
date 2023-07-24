const int ledPin26 = 26;
const int ledPin27 = 27;

const int freq = 5000;
const int resolution = 8;
const int ledChannel = 0;

void setup() {
  // put your setup code here, to run once:

  ledcSetup(ledChannel,freq,resolution);

  ledcAttachPin(ledPin26,ledChannel);
  ledcAttachPin(ledPin27,ledChannel);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(ledChannel, dutyCycle);
    delay(25);
  }
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(ledChannel, dutyCycle);
    delay(25);
  }

}
