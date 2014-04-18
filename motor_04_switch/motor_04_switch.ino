/* Motor Shield 1-Channel DC Motor Demo
For more information see: http://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/
For motor shield see http://arduino.cc/en/Main/ArduinoMotorShieldR3 
Hardware: Arduino Uno with Arduino Motor Shield and 1 motor connected.
*/
#include <SoftwareSerial.h>
#include <stdarg.h>

/* CONFIG / CONSTANTS: */

int onSec = 60 * 3;
int offSec = 60 * 4;

#define FORWARD          12  // Pin for Motor A forward
#define BRAKE             9  // Pin for Motor A brake   
#define SPEED           255  // Full speed = 255

#define BUTTON_PIN_A      2  // Pin for Button A
#define BUTTON_PIN_B      3  // Pin for Button B
#define DELAY            20  // Button probe - delay in ms

#define LED              13  // Pin for onboard LED

/* HELPERS: */

boolean handle_button(int pin) {
  int button_pressed = !digitalRead(pin); // pin low -> pressed
  return button_pressed;
}

/* VARS: */

int loop_count;

/* INIT: */

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

  //prepare on/off time string for log messages:
  div_t condt = div(onSec, 60);
  int conm = condt.quot;
  int cons = condt.rem;
  div_t coffdt = div(offSec, 60);
  int coffm = coffdt.quot;
  int coffs = coffdt.rem;
  slog(sformat("RUN: %02dm%02ds / PAUSE: %02dm%02ds\n", conm, cons, coffm, coffs));
  
  
  for (int seconds = s; seconds > 0; seconds--) {   
    if ( (s - seconds < 6
    ) || (seconds <= 15) || ( seconds % 15 == 0 )) {
      div_t loopdt = div(seconds, 60);
      int loopm = loopdt.quot;
      int loops = loopdt.rem;
      slog(sformat("Loop no. %d / currently %s / %02dm%02ds left.\n", 
        lc, msg, loopm, loops));
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
  pinMode(LED, OUTPUT);  // LED
  // Motor Channel A:
  pinMode(FORWARE, OUTPUT); // Initiates Motor Channel A pin
  pinMode(BRAKE, OUTPUT); // Initiates Brake Channel A pin 
}

/* MAIN LOOP: */

void loop() {

  slog("Start channel A ...\n");
  digitalWrite(FORWARE, HIGH); // Establishes forward direction of Channel A
  digitalWrite(BRAKE, LOW);   // Disengage the Brake for Channel A
  analogWrite(3, SPEED);   // Spins the motor on Channel A at the desired speed
  digitalWrite(LED, HIGH);   // Turn the LED on (HIGH is the voltage level)
  
  delaySec(onSec, "RUNNING", loop_count);
  slogMinus();

  slog("Stop channel A ...\n");
  digitalWrite(BRAKE, HIGH); // Engage the Brake for Channel A
  digitalWrite(LED, LOW);    // Turn the LED off by making the voltage LOW

  delaySec(offSec, "PAUSING", loop_count);
  slogMinus();
  
  loop_count++;
}

