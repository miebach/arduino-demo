/* Switch Demo. Output current state of 2 seperate switches / buttons to serial console.
Hardware: 
- Arduino Uno
- Switch A connected to GND and Pin 2 
- Switch B connected to GND and Pin 3 */

#include <SoftwareSerial.h>
#include <stdarg.h>

/* CONFIG / CONSTANTS: */

#define BUTTON_PIN_A      2  // Button A
#define BUTTON_PIN_B      3  // Button B
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
  
  // digital pin initialize A:
  pinMode(BUTTON_PIN_A,INPUT);
  digitalWrite(BUTTON_PIN_A, HIGH); // configure as pull-up using internal resistor

  // same for B:
  pinMode(BUTTON_PIN_B,INPUT);
  digitalWrite(BUTTON_PIN_B, HIGH);
  
  slog("... initialized.\n");
}

/* MAIN LOOP: */

void loop() {
  // check button A:
  boolean button_pressed_a = handle_button(BUTTON_PIN_A);

  // write dot, or A if pressed for Button A:
  Serial.print(button_pressed_a ? "A" : ".");

  // same for B:
  boolean button_pressed_b = handle_button(BUTTON_PIN_B);
  Serial.print(button_pressed_b ? "B" : ".");

  // add newline sometimes
  static int counter = 0;
  if ((++counter & 0x1f) == 0) //0x1f = 31, 0x3f = 63
    Serial.println();

  delay(DELAY);
}
