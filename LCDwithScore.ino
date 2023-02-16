#include <LiquidCrystal.h>
#include <Keyboard.h>

// initialize pins for LCD Screen
const int RSpin = 2;
const int ENpin = 3;
const int d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(RSpin, ENpin, d4, d5, d6, d7);

// initialize pins for LED and Button(s)
const int LEDpin = 11;
const int buttonPin = 12;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2); // 16 pixels, 2 rows
  lcd.print("Hello World!");
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT); // set LEDpin as an output
  pinMode(buttonPin, INPUT); // set buttonPin as an input
}

int score = 0; // initialize variable for score; called "counter"
bool lightOn = false; // initialize flag to see if light is on
bool canScorePoint = false; // ... if user can score a point
int buttonPress; // initialize variable to detect if button is pressed
// char input = 0;

void loop() {

  // turn on LED and signal that it is on
  digitalWrite(LEDpin, HIGH);
  lightOn = true;
  canScorePoint = true;

  // turn light on for 1 second
  // and while the light is on, check if the button is pressed
  int time = millis();
  int startTime = startTime;
  while (lightOn == true) {
    
    // see if button is pressed
    // if button is pressed while the light is on:
    // increment score, print it out, and make sure user can't score an extra point
    buttonPress = digitalRead(buttonPin);
    if ((buttonPress == HIGH) && (canScorePoint == true)) {
      score++;
      lcd.setCursor(0, 1);
      lcd.print(score);
      canScorePoint = false;
    }

    // turn off LED if it has been on for 1000 ms
    time = millis();
    if((time - startTime) > 1000) {
      digitalWrite(LEDpin, LOW);
      lightOn = false;
      canScorePoint = false;
    }
  }


  // if (Serial.available()) {
  //   input = Serial.read();
  //   if ((input != 0) && (canScorePoint == true)) {
  //     score++;
  //   }
  // }
  
  lcd.print(score);
  Serial.println(score);
  // input = 0;
}
