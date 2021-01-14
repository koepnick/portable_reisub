#include <Arduino.h>
#include <Keyboard.h>

#define DEBOUNCE_TIME 1000
#define KEY_DELAY 100
#define CMD_DELAY 5000

// Any keys that aren't defined by the Keyboard.h library
#define KEY_PRINTSCREEN 0xce

#define REBOOT_PIN 2


void setup() {
  pinMode(REBOOT_PIN, OUTPUT);
  digitalWrite(REBOOT_PIN, HIGH);
  Keyboard.begin();
  Serial.begin(9600);
}

void graceful() {
  /*
  Any action involving the system halting should call this
  function first
  */
  Keyboard.press(KEY_LEFT_ALT);
  delay(KEY_DELAY);
  Keyboard.press(KEY_PRINTSCREEN);
  delay(KEY_DELAY);
  Keyboard.press('r');  // Take control of any X sessions
  delay(KEY_DELAY); 
  Keyboard.press('e');  // Send SIGTERM to all processes
  delay(KEY_DELAY);
  Keyboard.press('i');  // Send SIGKILL to all processes
  delay(KEY_DELAY);
  Keyboard.press('s');  // Flush data to disk
  delay(KEY_DELAY);
  Keyboard.press('u');  // Remount filesystems to read-only
  delay(KEY_DELAY);
  Keyboard.releaseAll();
}

void finalCommand(char cmd){
  Keyboard.press(KEY_LEFT_ALT);
  delay(KEY_DELAY);
  Keyboard.press(KEY_PRINTSCREEN);
  delay(KEY_DELAY);
  Keyboard.press(cmd);
  delay(KEY_DELAY);
  Keyboard.releaseAll();
}

void loop() {
  while (digitalRead(2) == HIGH){
    delay(DEBOUNCE_TIME);
  }  
  graceful();
  finalCommand('b');
}
