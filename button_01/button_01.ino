/* Switch Demo. Output current state of switch to serial console.
Hardware: 
- Arduino Uno
- Switch connected to GND and Pin 2 */

#include <SoftwareSerial.h>
#include <stdarg.h>

/* CONFIG / CONSTANTS: */

#define BUTTON_PIN        2  // Button
#define DELAY            20  // Delay per loop in ms

/* HELPERS: */

boolean handle_button(int pin) {
  int button_pressed = !digitalRead(pin); // pin low -> pressed
  return button_pressed;
}

void slog(char* msg) {
  Serial.print(msg);
}

/* SETUP: */

void setup() {
  // Open serial communications
  SoftwareSerial mySerial(10, 11); // RX, TX
  Serial.begin(9600);
  slog("Arduino initializing...\n");
  
  // digital pin initialize:
  pinMode(BUTTON_PIN,INPUT);
  digitalWrite(BUTTON_PIN, HIGH); // configure as pull-up using internal resistor
  
  slog("... initialized.\n");
}

/* MAIN LOOP: */

void loop() {
  // check button:
  boolean button_pressed = handle_button(BUTTON_PIN);

  // write dot, or ^ if pressed:
  Serial.print(button_pressed ? "^" : ".");

  // add newline sometimes
  static int counter = 0;
  if ((++counter & 0x3f) == 0)
    Serial.println();

  delay(DELAY);
}
