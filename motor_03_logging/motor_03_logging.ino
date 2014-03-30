/* Motor Shield 1-Channel DC Motor Demo
For more information see: http://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/
For motor shield see http://arduino.cc/en/Main/ArduinoMotorShieldR3 
Hardware: Arduino Uno with Arduino Motor Shield and 1 motor connected.
*/
#include <SoftwareSerial.h>
#include <stdarg.h>

/* CONFIG: */

int onSec = 60 * 3;
int offSec = 60 * 7;

/*
int onSec = 7;
int offSec = 11;
*/

/* CONSTANTS: */

// Pin 13 onboard LED
int led = 13;

// motor a:
int forward = 12;
int brake = 9;   

/* INIT: */

int loop_count;
SoftwareSerial mySerial(10, 11); // RX, TX

/* HELPERS: */

void slog(char* msg) {
  Serial.print(msg);
}

void slogMinus() {
  slog("---------------------------------------\n");
}

char *sformat(char *fmt, ... ) {
  // include <stdarg.h>
  // see http://playground.arduino.cc/Main/Printf
  char buf[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(buf, 128, fmt, args);
  va_end (args);
  return buf;
}

void delaySec(int s, char* msg, int lc) {
  div_t maxdt = div(s, 60)
  ;
  int maxm = maxdt.quot;
  int maxs = maxdt.rem;
  for (int seconds = s; seconds > 0; seconds--) {   
    if ( (s - seconds < 6
    ) || (seconds <= 15) || ( seconds % 15 == 0 )) {
      div_t loopdt = div(seconds, 60);
      int loopm = loopdt.quot;
      int loops = loopdt.rem;
      slog(sformat("Loop no. %d / currently %s for %02dm%02ds / %02dm%02ds left.\n", lc, 
  
        msg, maxm, maxs, loopm, loops));
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
  
  //init loop counter for logging
  loop_count = 0;

  // initialize the digital pins as outputs
  pinMode(led, OUTPUT);  // LED
  // Motor Channel A:
  pinMode(forward, OUTPUT); // Initiates Motor Channel A pin
  pinMode(brake, OUTPUT); // Initiates Brake Channel A pin 
}

/* MAIN LOOP: */

void loop() {

  slog("Start channel A ...\n");
  digitalWrite(forward, HIGH); // Establishes forward direction of Channel A
  digitalWrite(brake, LOW);   // Disengage the Brake for Channel A
  analogWrite(3, 255);   // Spins the motor on Channel A at full speed
  digitalWrite(led, HIGH);   // Turn the LED on (HIGH is the voltage level)
  
  delaySec(onSec, "RUNNING", loop_count);
  slogMinus();


  slog("Stop channel A ...\n");
  digitalWrite(brake, HIGH); // Engage the Brake for Channel A
  digitalWrite(led, LOW);    // Turn the LED off by making the voltage LOW

  delaySec(offSec, "PAUSING", loop_count);
  slogMinus();
  
  loop_count++;
}
