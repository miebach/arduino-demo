/* Motor Shield 1-Channel DC Motor Demo
For more information see: http://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/
For motor shield see http://arduino.cc/en/Main/ArduinoMotorShieldR3 
Hardware: Arduino Uno with Arduino Motor Shield and 1 motor connected.
*/
#include <SoftwareSerial.h>
#include <stdarg.h>

/* CONFIG / CONSTANTS: */

uint16_t onSec = 60 * 3;
uint16_t offSec = 60 * 4;

#define DEC_TIME   0.99      // factor for decreasing time intervals
#define INC_TIME   1.010101  // factor for increasing time intervals

#define FORWARD          12  // Pin for Motor A forward
#define BRAKE             9  // Pin for Motor A brake   
#define SPEED           255  // Full speed = 255

#define BUTTON_PIN_A      2  // Pin for Button A
#define BUTTON_PIN_B      3  // Pin for Button B
#define DELAY            20  // Button probe - delay in ms
#define DELAYS_PER_SEC   50  // Number of delays per second = 1000 / DELAY

#define LED              13  // Pin for onboard LED

/* HELPERS: */

boolean handle_button(uint16_t pin) {
  uint16_t button_pressed = !digitalRead(pin); // pin low -> pressed
  return button_pressed;
}

/* VARS: */

uint16_t loop_count;

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

void delaySec(uint16_t s, char* msg, uint16_t lc) {

  //prepare on/off time string for log messages:
  div_t condt = div(onSec, 60);
  uint16_t conm = condt.quot;
  uint16_t cons = condt.rem;
  div_t coffdt = div(offSec, 60);
  uint16_t coffm = coffdt.quot;
  uint16_t coffs = coffdt.rem;
  slog(sformat("RUN: %02dm%02ds / PAUSE: %02dm%02ds\n", conm, cons, coffm, coffs));
  
  for (uint16_t seconds = s; seconds > 0; seconds--) {   
    if ( (s - seconds < 6
    ) || (seconds <= 15) || ( seconds % 15 == 0 )) {
      div_t loopdt = div(seconds, 60);
      uint16_t loopm = loopdt.quot;
      uint16_t loops = loopdt.rem;
      slog(sformat("Loop no. %d / currently %s / %02dm%02ds left.\n", 
        lc, msg, loopm, loops));
    }

    // we need to tack if there were button infos printed:
    static uint16_t any_button;
    any_button = 0; // no button info printed yet

    static uint16_t char_count; //count single chars printed 
    char_count = 0;

    for (uint16_t delays = 0; delays < DELAYS_PER_SEC; delays++) { 
      delay(DELAY);

      // check button A:
      boolean button_pressed_a = handle_button(BUTTON_PIN_A);

      // write dot, or A if pressed for Button A:
      if (button_pressed_a) {
        if (any_button == 0) {
          any_button = 1;
          Serial.println(); //newline before first Button info char
        }
        Serial.print("A");
        onSec = (uint16_t)(0.5f + INC_TIME * onSec);
        offSec = (uint16_t)(0.5f + DEC_TIME * offSec);
        char_count++;
      }

      // same for B:
      boolean button_pressed_b = handle_button(BUTTON_PIN_B);
      if (button_pressed_b) {
        if (any_button == 0) {
          any_button = 1;
          Serial.println(); //newline before first Button info char
        }
        Serial.print("B");
        onSec = (uint16_t)(0.5f + DEC_TIME * onSec);
        offSec = (uint16_t)(0.5f + INC_TIME * offSec);
        char_count++;
      }

      if (char_count > 0)
        // add newline every 64 chars:
        if ((char_count & 0x1f) == 0) //0x1f = 31, 0x3f = 63
          Serial.println();
    }

    if (any_button == 1) {
      //newline after Button info line(s), only if there was something:
      Serial.println(); 
      any_button = 0;
    }

      slog(sformat("New Values: onSec / offSec = %d / %d \n", 
        onSec, offSec));

  }
}

/* SETUP: */

void setup() {
  // Open serial console:
  SoftwareSerial mySerial(10, 11); // RX, TX
  Serial.begin(9600);
 
  slog("Arduino initializing...\n");
  
  // digital pin initialize A:
  pinMode(BUTTON_PIN_A,INPUT);
  digitalWrite(BUTTON_PIN_A, HIGH); // configure as pull-up using internal resistor

  // same for B:
  pinMode(BUTTON_PIN_B,INPUT);
  digitalWrite(BUTTON_PIN_B, HIGH);
  
  //init loop counter for logging
  loop_count = 0;
 
  // initialize the digital pins as outputs
  pinMode(LED, OUTPUT);  // LED

  // Motor Channel A:
  pinMode(FORWARD, OUTPUT); // Initiates Motor Channel A pin
  pinMode(BRAKE, OUTPUT); // Initiates Brake Channel A pin 

  slog("... initialized.\n");
}

/* MAIN LOOP: */

void loop() {

  slog("Start channel A ...\n");
  digitalWrite(FORWARD, HIGH); // Establishes forward direction of Channel A
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

