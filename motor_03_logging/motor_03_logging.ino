/* Motor Shield 1-Channel DC Motor Demo
For more information see: http://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/
For motor shield see http://arduino.cc/en/Main/ArduinoMotorShieldR3 
Hardware: Arduino Uno with Arduino Motor Shield and 1 motor connected.
*/
#include <SoftwareSerial.h>
#include <stdarg.h>

/* CONFIG: */

int onSec = 20;
//int onSec = 60 * 3;
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
  div_t maxdt = div(s, 60)
  ;
  int maxm = maxdt.quot;
  int maxs = maxdt.rem;
  for (int seconds = s; seconds > 0; seconds--) {   
    if ( (s - seconds < 6 ) || (seconds <= 15) || ( seconds % 15 == 0 )) {
      div_t loopdt = div(seconds, 60);
      int loopm = loopdt.quot;
      int loops = loopdt.rem;
      slogf("%s - delay 00:%02d:%02d / 00:%02d:%02d ... \n", msg, loopm, loops, maxm, maxs);
    }
    delay(1000);  
  }
}

/* SETUP: */

void setup() {
  // Open serial communications
  Serial.begin(9600);
  // while (!Serial) ... // Leonardo only, wait for port to open
  
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
