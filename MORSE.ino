#include <string.h>

bool isMorseBlinking = false;       // Tracks if the LED is currently blinking in Morse code
String inputtedName = "";           // Stores the name entered through serial input
const int BUTTON_PIN = 3;           // Pin for the button input

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Set the built-in LED as an output
  pinMode(BUTTON_PIN, INPUT_PULLUP);// Set the button pin as an input with internal pull-up resistor
  Serial.begin(9600);               // Initialize serial communication
}

int getAlphabetPosition(char letter) {
  return (letter - 'a');            // Calculate the position of the letter in the alphabet
}

String morseCodeArray[26]{
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." 
};

void blinkMorseLED(String morseCode) {
  for (int i = 0; i < morseCode.length(); i++) {
    if (morseCode[i] == '.') {
      digitalWrite(LED_BUILTIN, HIGH); // Turn on LED for dot
      delay(1000);                      // Delay for dot duration
      digitalWrite(LED_BUILTIN, LOW);  // Turn off LED
      delay(500);                       // Delay between dot and dash
    } else if (morseCode[i] == '-') {
      digitalWrite(LED_BUILTIN, HIGH); // Turn on LED for dash
      delay(2000);                      // Delay for dash duration
      digitalWrite(LED_BUILTIN, LOW);  // Turn off LED
      delay(500);                       // Delay between characters
    }
  }
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (!isMorseBlinking) {
      isMorseBlinking = true;

      if (inputtedName == "") {
        Serial.println("Enter your name");
        while (!Serial.available()) {
          // Wait until serial data is available
        }
        inputtedName = Serial.readStringUntil('\n'); // Read the name from serial input
        Serial.println(inputtedName);
      }
      
      for (int i = 0; i < inputtedName.length(); i++) {
        int alphabetPosition = getAlphabetPosition(inputtedName[i]);
        String morseCode = morseCodeArray[alphabetPosition];
        blinkMorseLED(morseCode);        // Blink LED based on Morse code
        digitalWrite(LED_BUILTIN, LOW); // Turn off LED
        delay(3000);                     // Delay between letters
      }
    }
  } else {
    isMorseBlinking = false;
  }
}
