#include <FastLED.h>
#include <LiquidCrystal.h>
#define NUM_LEDS 110
#define DATA_PIN 2
#define BUTTON1_PIN 3
#define BUTTON2_PIN 4
#define BUTTON3_PIN 5
#define BUTTON4_PIN 6

// led stuff
CRGB leds[NUM_LEDS];
const int LED_delay = 100;
// index of second led in column
const int column1_index = 11;
const int column2_index = 31;
const int column3_index = 51;
const int column4_index = 71;

// arrays that represent when stuff should happen; will come from C++ program
// below example arrays mark that first button should be pressed 1000 ms after song starts
// 2nd button should be pressed 1500ms after song starts
// 3rd button should be pressed 2000ms after song starts
// future: first element will have number of times; "size" of the array
unsigned long song1_key1_times[] = {-1, 2606, 12085, 13491, 14442, 18213, 22020, 24852, 26743, 31854, 32821, 35932, 36877, 38989, 39949, 42749, 45598, 46598, 47685, 50814, 53116, 54566, 55978, 56904, 60678, 62575, 68998, 72535, 74886, 76534, 78497, 78825, 83394, 85620, 86422, 90253};
unsigned long song1_key2_times[] = {-1, 3057, 5715, 8932, 12568, 13998, 16510, 17931, 20604, 21742, 24725, 26588, 29515, 32133, 33085, 35621, 36589, 39205, 40148, 41062, 42977, 43702, 45845, 47028, 47972, 49566, 51236, 53374, 54821, 56223, 57174, 58340, 60926, 62839, 65878, 66342, 68718, 71078, 72791, 73702, 74221, 75132, 76268, 79588, 81021, 82001, 82661, 87127, 88620, 89261};
unsigned long song1_key3_times[] = {-1, 3531, 5007, 5452, 8564, 13076, 14916, 15837, 16308, 17249, 17708, 19607, 20085, 20380, 21052, 21510, 23373, 24262, 25286, 26190, 28545, 29044, 31390, 32364, 33279, 35397, 36389, 37326, 39518, 40397, 40878, 43220, 43950, 44880, 45324, 46092, 47229, 48670, 49366, 49830, 50341, 53597, 54110, 55057, 55533, 56438, 57372, 57908, 58807, 61176, 61644, 63054, 63509, 64455, 65238, 66108, 68302, 69238, 70141, 70612, 72022, 73022, 73486, 74411, 75364, 75821, 79588, 81021, 82017, 82680, 87150, 88601, 89268};
unsigned long song1_key4_times[] = {-1, 4019, 5244, 8293, 16060, 17500, 19859, 21278, 23613, 24495, 25500, 26382, 28775, 31631, 32588, 33509, 35197, 36181, 37110, 39732, 40638, 43453, 44205, 44669, 45117, 46340, 47494, 48895, 50079, 53836, 55285, 56672, 57661, 61382, 63269, 64950, 65445, 68509, 70388, 70844, 72256, 73265, 74613, 75587, 78497, 78843, 83408, 85639, 86444, 90271};
int w = 1;
int a = 1;
int s = 1;
int d = 1;

// these represent the next time a light should turn on; technically when a button should be pressed after the song starts
unsigned long next_light_1 , next_light_2 , next_light_3, next_light_4;
unsigned long next_column_1, next_column_1_2, next_column_1_3;
unsigned long next_column_2, next_column_2_2, next_column_2_3;
unsigned long next_column_3, next_column_3_2, next_column_3_3;
unsigned long next_column_4, next_column_4_2, next_column_4_3;
int i, i_2, i_3;
int j, j_2, j_3;
int k, k_2, k_3;
int l, l_2, l_3;
bool column1InProgress1, column1InProgress2, column1InProgress3;
bool column2InProgress1, column2InProgress2, column2InProgress3;
bool column3InProgress1, column3InProgress2, column3InProgress3;
bool column4InProgress1, column4InProgress2, column4InProgress3;

// button and score stuff
bool canScorePoint_column1 = false;
bool canScorePoint_column2 = false;
bool canScorePoint_column3 = false;
bool canScorePoint_column4 = false;
unsigned long canScorePoint_column1_duration, canScorePoint_column2_duration, canScorePoint_column3_duration, canScorePoint_column4_duration;
int score = 0;

const int RSpin = 8;
const int ENpin = 9;
const int d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(RSpin, ENpin, d4, d5, d6, d7);

// function that will update time that light should turn on for next light using the next element of the arrays
// these functions endup accessing out of array bounds, I think i can fix that by including the size of the array in the first element in the future
void getNextTime(int button) {
    switch (button) {
        case 1:
        // check next element of array and update the next time with the value
            next_light_1 = song1_key1_times[w];    
        // increment i so that next element is ready to be read when the function is called again
            w++;
            break;
        case 2:
            next_light_2 = song1_key2_times[a];
            a++;
            break;
        case 3:
            next_light_3 = song1_key3_times[s];
            s++;
            break;
        case 4:
            next_light_4 = song1_key4_times[d];
            d++;
            break;
    }
}

void resetColumn(unsigned long &column, unsigned long next_light) {
    column = next_light;
}

void updateColumn(unsigned long &column) {
    column += LED_delay;
}

void startColumnIteration(int column, bool &columnInProgressFlag, int beginningIndex, unsigned long &columnTime, unsigned long next_light, int &iterator) {
    columnInProgressFlag = true;
    leds[beginningIndex - 1] = CRGB::MediumVioletRed; FastLED.show();
    leds[beginningIndex + 9] = CRGB::MediumVioletRed; FastLED.show();
    columnTime  = next_light + LED_delay; 
    iterator = beginningIndex;
    getNextTime(column);
    // Print_Next_Times();
    // Serial.println("column start");
}

void ColumnIteration(bool &columnInProgressFlag, bool &scoreFlag, unsigned long &scoreDuration, int beginningIndex, unsigned long &columnTime, unsigned long next_light, int &iterator) {
    if (iterator < (beginningIndex + 9)) {
            leds[iterator - 1] = CRGB::Black; FastLED.show(); 
            leds[iterator] = CRGB::MediumVioletRed; FastLED.show(); 
            leds[iterator + 9] = CRGB::Black; FastLED.show(); 
            leds[iterator + 10] = CRGB::MediumVioletRed; FastLED.show(); 
            iterator++;
            updateColumn(columnTime);
        }
        else {
            leds[iterator - 1] = CRGB::BlanchedAlmond; FastLED.show(); 
            leds[iterator + 9] = CRGB::BlanchedAlmond; FastLED.show(); 
            columnTime = next_light;
            columnInProgressFlag = false;
            //Serial.println("column done");
        }
        if (iterator == (beginningIndex + 8)) {
            scoreFlag = true;
            scoreDuration = millis() + (4 * LED_delay);
        }
}

// function for debugging
void Print_Next_Times() {
    Serial.print("next_light_1: ");
    //Serial.println(next_light_1);
    Serial.print("next_light_2: ");
    //Serial.println(next_light_2);
    Serial.print("next_light_3: ");
    //Serial.println(next_light_3);
    Serial.print("next_light_4: ");
    //Serial.println(next_light_4);
}

void setup() { 
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 

    // create a variable for when the arduino starts running
    long t_arduino_start= millis ();

    // update next_times
    getNextTime(1);
    getNextTime(2);
    getNextTime(3);
    getNextTime(4);

    // update initial next_columns
    resetColumn(next_column_1, next_light_1);
    resetColumn(next_column_2, next_light_2);
    resetColumn(next_column_3, next_light_3);
    resetColumn(next_column_4, next_light_4);

    // update initial buttons
    canScorePoint_column1_duration = next_light_1 + (8 * LED_delay);
    canScorePoint_column2_duration = next_light_2 + (8 * LED_delay);
    canScorePoint_column3_duration = next_light_3 + (8 * LED_delay);
    canScorePoint_column4_duration = next_light_4 + (8 * LED_delay);

    // debugging
    Serial.begin(9600);
    Print_Next_Times();

    //Initializing button input
    pinMode(BUTTON1_PIN, INPUT);
    pinMode(BUTTON2_PIN, INPUT);
    pinMode(BUTTON3_PIN, INPUT);
    pinMode(BUTTON4_PIN, INPUT);

    //LCD
    lcd.begin(16,2);    

    leds[column1_index + 8] = CRGB::BlanchedAlmond; FastLED.show();
    leds[column1_index + 18] = CRGB::BlanchedAlmond; FastLED.show();
    leds[column2_index + 8] = CRGB::BlanchedAlmond; FastLED.show();
    leds[column2_index + 18] = CRGB::BlanchedAlmond; FastLED.show();
    leds[column3_index + 8] = CRGB::BlanchedAlmond; FastLED.show();
    leds[column3_index + 18] = CRGB::BlanchedAlmond; FastLED.show();
    leds[column4_index + 8] = CRGB::BlanchedAlmond; FastLED.show();
    leds[column4_index + 18] = CRGB::BlanchedAlmond; FastLED.show();

}

// event based programming !
void loop() {

  int button1 = digitalRead(BUTTON1_PIN); 
  int button2 = digitalRead(BUTTON2_PIN);
  int button3 = digitalRead(BUTTON3_PIN);
  int button4 = digitalRead(BUTTON4_PIN);
    // check if it is time to prompt for the first button
    if ( millis() > next_light_1 ) {
      
        if (column1InProgress1 == false) {
            startColumnIteration(1, column1InProgress1, column1_index, next_column_1, next_light_1, i);
        }
        else if (column1InProgress2 == false) {
            startColumnIteration(1, column1InProgress2, column1_index, next_column_1_2, next_light_1, i_2);
        }
        else if (column1InProgress3 == false) {
            startColumnIteration(1, column1InProgress3, column1_index, next_column_1_3, next_light_1, i_3);
        }
    }
    if ( (millis() > next_column_1) && (column1InProgress1 == true) ) {
        ColumnIteration(column1InProgress1, canScorePoint_column1, canScorePoint_column1_duration, column1_index, next_column_1, next_light_1, i);
    }
    if ( (millis() > next_column_1_2) && (column1InProgress2 == true) ) {
        ColumnIteration(column1InProgress2, canScorePoint_column1, canScorePoint_column1_duration, column1_index, next_column_1_2, next_light_1, i_2);
    }
    if ( (millis() > next_column_1_3) && (column1InProgress3 == true) ) {
        ColumnIteration(column1InProgress3, canScorePoint_column1, canScorePoint_column1_duration, column1_index, next_column_1_3, next_light_1, i_3);
    }   
    if ( millis() < canScorePoint_column1_duration) {
      int button1 = digitalRead(BUTTON1_PIN)
        if (canScorePoint_column1 == true && button1 == HIGH) {
            score++;
            lcd.setCursor(0, 1);
            lcd.print(score);
            Serial.print("score updated");
            canScorePoint_column1 = false;
        }
    }

    if ( millis() > next_light_2 ) {
        if (column2InProgress1 == false) {
            startColumnIteration(2, column2InProgress1, column2_index, next_column_2, next_light_2, j);
        }
        else if (column2InProgress2 == false) {
            startColumnIteration(2, column2InProgress2, column2_index, next_column_2_2, next_light_2, j_2);
        }
        else if (column2InProgress3 == false) {
            startColumnIteration(2, column2InProgress3, column2_index, next_column_2_3, next_light_2, j_3);
        }
    }
    if ( (millis() > next_column_2) && (column2InProgress1 == true) ) {
        ColumnIteration(column2InProgress1, canScorePoint_column2, canScorePoint_column2_duration, column2_index, next_column_2, next_light_2, j);
    }
    if ( (millis() > next_column_2_2) && (column2InProgress2 == true) ) {
        ColumnIteration(column2InProgress2, canScorePoint_column2, canScorePoint_column2_duration, column2_index, next_column_2_2, next_light_2, j_2);
    }
    if ( (millis() > next_column_2_3) && (column2InProgress3 == true) ) {
        ColumnIteration(column2InProgress3, canScorePoint_column2, canScorePoint_column2_duration, column2_index, next_column_2_3, next_light_2, j_3);
    }
    if ( millis() < canScorePoint_column2_duration) {
        if (canScorePoint_column2 == true && button2 == HIGH) {
            canScorePoint_column2 = false;
            score++;
            lcd.setCursor(0, 1);
            lcd.print(score);
        }
    }
    
    if ( millis() > next_light_3 ) {
        if (column3InProgress1 == false) {
            startColumnIteration(3, column3InProgress1, column3_index, next_column_3, next_light_3, k);
        }
        else if (column3InProgress2 == false) {
            startColumnIteration(3, column3InProgress2, column3_index, next_column_3_2, next_light_3, k_2);
        }
        else if (column3InProgress3 == false) {
            startColumnIteration(3, column3InProgress3, column3_index, next_column_3_3, next_light_3, k_3);
        }
    }
    if ( (millis() > next_column_3) && (column3InProgress1 == true) ) {
        ColumnIteration(column3InProgress1, canScorePoint_column3, canScorePoint_column3_duration, column3_index, next_column_3, next_light_3, k);
    }
    if ( (millis() > next_column_3_2) && (column3InProgress2 == true) ) {
        ColumnIteration(column3InProgress2, canScorePoint_column3, canScorePoint_column3_duration, column3_index, next_column_3_2, next_light_3, k_2);
    }
    if ( (millis() > next_column_3_3) && (column3InProgress3 == true) ) {
        ColumnIteration(column3InProgress3, canScorePoint_column3, canScorePoint_column3_duration, column3_index, next_column_3_3, next_light_3, k_3);
    }
    if ( millis() < canScorePoint_column3_duration) {
        if (canScorePoint_column3 == true && button3 == HIGH) {
            canScorePoint_column3 = false;
            score++;
            lcd.setCursor(0, 1);
            lcd.print(score);
        }
    }

    if ( millis() > next_light_4 ) {

        if (column4InProgress1 == false) {
            startColumnIteration(4, column4InProgress1, column4_index, next_column_4, next_light_4, l);
        }
        else if (column4InProgress2 == false) {
            startColumnIteration(4, column4InProgress2, column4_index, next_column_4_2, next_light_4, l_2);
        }
        else if (column4InProgress3 == false) {
            startColumnIteration(4, column4InProgress3, column4_index, next_column_4_3, next_light_4, l_3);
        }
    }
    if ( (millis() > next_column_4) && (column4InProgress1 == true) ) {
        ColumnIteration(column4InProgress1, canScorePoint_column4, canScorePoint_column4_duration, column4_index, next_column_4, next_light_4, l);
    }
    if ( (millis() > next_column_4_2) && (column4InProgress2 == true) ) {
        ColumnIteration(column4InProgress2, canScorePoint_column4, canScorePoint_column4_duration, column4_index, next_column_4_2, next_light_4, l_2);
    }
    if ( (millis() > next_column_4_3) && (column4InProgress3 == true) ) {
        ColumnIteration(column4InProgress3, canScorePoint_column4, canScorePoint_column4_duration, column4_index, next_column_4_3, next_light_4, l_3);
    }
    if ( millis() < canScorePoint_column4_duration) {
        if (canScorePoint_column4 == true && button4 == HIGH) {
            canScorePoint_column4 = false;
            score++;
            lcd.setCursor(0, 1);
            lcd.print(score);
            Serial.println("Score added to");
        }
    }
  lcd.setCursor(0,1);
  lcd.print(score); 
}
