/* Motor Shield 1-Channel DC Motor Demo
For more information see: http://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/
For motor shield see http://arduino.cc/en/Main/ArduinoMotorShieldR3 
Hardware: Arduino Uno with Arduino Motor Shield and 1 motor connected.
*/
#include <SoftwareSerial.h>
#include <stdarg.h>

/* CONFIG: */

int onSec = 60 * 3;
int offSec = 60 * 10;

/* CONSTANTS: */

// Pin 13 onboard LED
int led = 13;

// motor a:
int forward = 12;
int brake = 9;   

/* INIT: */

SoftwareSerial mySerial(10, 11); // RX, TX

/* HELPERS: */

void slog(char* msg) {
  Serial.print(msg);
}

void slogf(char *fmt, ... ) {
  // include <stdarg.h>
  // see http://playground.arduino.cc/Main/Printf
  char buf[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(buf, 128, fmt, args);
  va_end (args);
  Serial.print(buf);
}

void delaySec(int s, char* msg) {
  for (int seconds = 0; seconds < s; seconds++) {
    slogf("%s - delay %10d/%%10d seconds ...       \n", msg, seconds, s);
    delay(1000);  
  }
}

/* SETUP: */

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {;} // Leonardo init
  
  slog("Arduino initializing...\n");

  // initialize the digital pins as outputs
  pinMode(led, OUTPUT);  // LED
  // Motor Channel A:
  pinMode(forward, OUTPUT); // Initiates Motor Channel A pin
  pinMode(brake, OUTPUT); // Initiates Brake Channel A pin 
}

/* MAIN LOOP: */

void loop() {
  //forward @ full speed
  slog("Start channel A ...\n");
  digitalWrite(forward, HIGH); // Establishes forward direction of Channel A
  digitalWrite(brake, LOW);   // Disengage the Brake for Channel A
  analogWrite(3, 255);   // Spins the motor on Channel A at full speed
  digitalWrite(led, HIGH);   // Turn the LED on (HIGH is the voltage level)
  
  delaySec(onSec, "started");

  slog("Stop channel A ...\n");
  digitalWrite(brake, HIGH); // Engage the Brake for Channel A
  digitalWrite(led, LOW);    // Turn the LED off by making the voltage LOW

  delaySec(offSec, "stopped");
}
