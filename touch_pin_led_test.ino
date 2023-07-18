const int touchPin = 12; //touch pin gpio12
const int ledPin = 26; //led pin gpio 26


const int threshold = 20; //variable threshold
int touchValue; //storing touch pin value

void setup(){
  Serial.begin(115200);
  Serial.print("Esp 32 touch pin test!");
  delay(1000); 
  // initialize the LED pin as an output:
  pinMode (ledPin, OUTPUT);
}

void loop(){
  // read the state of the pushbutton value:
  touchValue = touchRead(touchPin);
  Serial.print(touchValue);
  // check if the touchValue is below the threshold
  // if it is, set ledPin to HIGH
  if(touchValue < threshold){
    // turn LED on
    digitalWrite(ledPin, HIGH);
    Serial.println(" - LED on");
  }
  else{
    // turn LED off
    digitalWrite(ledPin, LOW);
    Serial.println(" - LED off");
  }
  delay(500);
}