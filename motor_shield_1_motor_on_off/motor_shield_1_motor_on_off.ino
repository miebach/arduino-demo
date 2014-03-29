/* Motor Shield 1-Channel DC Motor Demo
For more information see: http://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/
For motor shield see http://arduino.cc/en/Main/ArduinoMotorShieldR3 
Hardware: Arduino Uno with Arduino Motor Shield and 1 motor connected.
*/

// Pin 13 onboard LED
int led = 13;

// motor a:
int forward = 12;
int brake = 9;   

void setup() {
  // initialize the digital pins as outputs
  pinMode(led, OUTPUT);  // LED
  // Motor Channel A:
  pinMode(forward, OUTPUT); // Initiates Motor Channel A pin
  pinMode(brake, OUTPUT); // Initiates Brake Channel A pin 
}

void loop(){
  //forward @ full speed
  digitalWrite(forward, HIGH); // Establishes forward direction of Channel A
  digitalWrite(brake, LOW);   // Disengage the Brake for Channel A
  analogWrite(3, 255);   // Spins the motor on Channel A at full speed
  digitalWrite(led, HIGH);   // Turn the LED on (HIGH is the voltage level)
  
  delay(10000);

  digitalWrite(brake, HIGH); // Engage the Brake for Channel A
  digitalWrite(led, LOW);    // Turn the LED off by making the voltage LOW

  delay(15000);
}
