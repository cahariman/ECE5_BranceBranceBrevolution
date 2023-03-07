#include <FastLED.h>
#define NUM_LEDS 110
#define DATA_PIN 4
#define BUTTON1_PIN 5
#define BUTTON2_PIN 6
#define BUTTON3_PIN 7
#define BUTTON4_PIN 8

// led stuff
CRGB leds[NUM_LEDS];
const int LED_delay = 70;
// index of second led in column
const int column1_index = 1;
const int column2_index = 11;
const int column3_index = 21;
const int column4_index = 31;

// arrays that represent when stuff should happen; will come from C++ program
// below example arrays mark that first button should be pressed 1000 ms after song starts
// 2nd button should be pressed 1500ms after song starts
// 3rd button should be pressed 2000ms after song starts
// future: first element will have number of times; "size" of the array
long song1_key1_times[] = {-1, 2606, 12085, 13491, 14442, 18213, 22020, 24852, 26743, 31854, 32821, 35932, 36877, 38989, 39949, 42749, 45598, 46598, 47685, 50814, 53116, 54566, 55978, 56904, 60678, 62575, 68998, 72535, 74886, 76534, 78497, 78825, 83394, 85620, 86422, 90253};
long song1_key2_times[] = {-1, 3057, 5715, 8932, 12568, 13998, 16510, 17931, 20604, 21742, 24725, 26588, 29515, 32133, 33085, 35621, 36589, 39205, 40148, 41062, 42977, 43702, 45845, 47028, 47972, 49566, 51236, 53374, 54821, 56223, 57174, 58340, 60926, 62839, 65878, 66342, 68718, 71078, 72791, 73702, 74221, 75132, 76268, 79588, 81021, 82001, 82661, 87127, 88620, 89261};
long song1_key3_times[] = {-1, 3531, 5007, 5452, 8564, 13076, 14916, 15837, 16308, 17249, 17708, 19607, 20085, 20380, 21052, 21510, 23373, 24262, 25286, 26190, 28545, 29044, 31390, 32364, 33279, 35397, 36389, 37326, 39518, 40397, 40878, 43220, 43950, 44880, 45324, 46092, 47229, 48670, 49366, 49830, 50341, 53597, 54110, 55057, 55533, 56438, 57372, 57908, 58807, 61176, 61644, 63054, 63509, 64455, 65238, 66108, 68302, 69238, 70141, 70612, 72022, 73022, 73486, 74411, 75364, 75821, 79588, 81021, 82017, 82680, 87150, 88601, 89268};
long song1_key4_times[] = {-1, 4019, 5244, 8293, 16060, 17500, 19859, 21278, 23613, 24495, 25500, 26382, 28775, 31631, 32588, 33509, 35197, 36181, 37110, 39732, 40638, 43453, 44205, 44669, 45117, 46340, 47494, 48895, 50079, 53836, 55285, 56672, 57661, 61382, 63269, 64950, 65445, 68509, 70388, 70844, 72256, 73265, 74613, 75587, 78497, 78843, 83408, 85639, 86444, 90271};
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


// function that will update time that light should turn on for next light using the next element of the arrays
// these functions endup accessing out of array bounds, I think i can fix that by including the size of the array in the first element in the future
void getNextTime_button1() {

    // check next element of array and update the next time with the value
    next_light_1 = song1_key1_times[w];
    Serial.println("updated next_light1");
    
    // increment i so that next element is ready to be read when the function is called again
    w++;
}
void getNextTime_button2() {
    
    // check next element of array and update the next time with the value
    next_light_2 = song1_key2_times[a];
    Serial.println("updated next_light2");
    
    // increment i so that next element is ready to be read when the function is called again
    a++;
}
void getNextTime_button3() {
    
    // check next element of array and update the next time with the value
    next_light_3 = song1_key3_times[s];
    Serial.println("updated next_light3");
    
    // increment i so that next element is ready to be read when the function is called again
    s++;
}
void getNextTime_button4() {
    
    // check next element of array and update the next time with the value
    next_light_4 = song1_key4_times[d];
    Serial.println("updated next_light4");
    
    // increment i so that next element is ready to be read when the function is called again
    d++;
}

// function for debugging
void Print_Next_Times() {
    Serial.print("next_light_1: ");
    Serial.println(next_light_1);
    Serial.print("next_light_2: ");
    Serial.println(next_light_2);
    Serial.print("next_light_3: ");
    Serial.println(next_light_3);
    Serial.print("next_light_4: ");
    Serial.println(next_light_4);
}

void setup() { 
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 

    // create a variable for when the arduino starts running
    long t_arduino_start= millis ();

    // update next_times
    getNextTime_button1();
    getNextTime_button2();
    getNextTime_button3();
    getNextTime_button4();

    // update initial next_columns
    next_column_1 = next_light_1 + LED_delay;
    next_column_2 = next_light_2 + LED_delay;
    next_column_3 = next_light_3 + LED_delay;
    next_column_4 = next_light_4 + LED_delay;

    // update initial buttons
    canScorePoint_column1_duration = next_light_1 + (8 * LED_delay);
    canScorePoint_column2_duration = next_light_2 + (8 * LED_delay);
    canScorePoint_column3_duration = next_light_3 + (8 * LED_delay);
    canScorePoint_column4_duration = next_light_4 + (8 * LED_delay);

    // debugging
    Serial.begin(9600);
    Print_Next_Times();

    //
    pinMode(BUTTON1_PIN, INPUT);
    pinMode(BUTTON2_PIN, INPUT);
    pinMode(BUTTON3_PIN, INPUT);
    pinMode(BUTTON4_PIN, INPUT);

}

// event based programming !
void loop() {

    // check if it is time to prompt for the first button
    if ( millis() > next_light_1 ) {

        if (column1InProgress1 == false) {
            column1InProgress1 = true;
            leds[column1_index - 1] = CRGB::MediumVioletRed; FastLED.show();
            next_column_1  = next_light_1 + LED_delay; 
            i = column1_index;
            getNextTime_button1();
            Print_Next_Times();
        }
        else if (column1InProgress2 == false) {
            column1InProgress2 = true;
            leds[column1_index - 1] = CRGB::MediumVioletRed; FastLED.show();
            next_column_1_2  = next_light_1 + LED_delay; 
            i_2 = column1_index;
            getNextTime_button1();
            Print_Next_Times();
        }
        else if (column1InProgress3 == false) {
            column1InProgress3 = true;
            leds[column1_index - 1] = CRGB::MediumVioletRed; FastLED.show();
            next_column_1_3  = next_light_1 + LED_delay; 
            i_3 = column1_index;
            getNextTime_button1();
            Print_Next_Times();
        }

        // TODO
        // iterate for column 1 with fastLED.h stuff; for loop
        // at 9th or 10th row in for loop, do a button check and then score stuff
        // note: if the for loop takes more than 500ms, the code won't work because the smallest time difference in the time arrays is 500ms

        // turn on first led in column and update column delay
            // leds[0] = CRGB::MediumVioletRed; FastLED.show(); 
        // Serial.println("on");
            // next_column_1  = next_light_1 + LED_delay; 
        // Serial.print("updated next_column_1: ");
        // Serial.println(next_column_1);
            // i = 1; // iterator for column

        // debugging
        // Serial.println("NEXT");

        // get next time from array
            // getNextTime_button1();

        // debugging
            // Print_Next_Times();

    }
    if ( (millis() > next_column_1) && (column1InProgress1 == true) ) {

        if (i < column1_index + 9) {
            leds[i - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            leds[i] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            // Serial.println("on");
            i++;
            next_column_1 += LED_delay; 
            // Serial.print("updated next_column_1: ");
            // Serial.println(next_column_1);
        }
        else {
            leds[i - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            next_column_1 = next_light_1;
            column1InProgress1 = false;
        }

        if (i == (column1_index + 7)) {
            canScorePoint_column1 = true;
            canScorePoint_column1_duration = millis() + (8 * LED_delay);
        }
    }
    if ( (millis() > next_column_1_2) && (column1InProgress2 == true) ) {

        if (i_2 < column1_index + 9) {
            leds[i_2 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            leds[i_2] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            // Serial.println("on");
            i_2++;
            next_column_1_2 += LED_delay; 
            // Serial.print("updated next_column_1: ");
            // Serial.println(next_column_1);
        }
        else {
            leds[i_2 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            next_column_1_2 = next_light_1;
            column1InProgress2 = false;
        }
        if (i_2 == (column1_index + 7)) {
            canScorePoint_column1 = true;
            canScorePoint_column1_duration = millis() + (8 * LED_delay);
        }
    }
    if ( (millis() > next_column_1_3) && (column1InProgress3 == true) ) {

        if (i_3 < column1_index + 9) {
            leds[i_3 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            leds[i_3] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            // Serial.println("on");
            i_3++;
            next_column_1_3 += LED_delay; 
            // Serial.print("updated next_column_1: ");
            // Serial.println(next_column_1);
        }
        else {
            leds[i_3 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            next_column_1_3 = next_light_1;
            column1InProgress3 = false;
        }
        if (i_3 == (column1_index + 7)) {
            canScorePoint_column1 = true;
            canScorePoint_column1_duration = millis() + (8 * LED_delay);
        }
    }
    if ( millis() > canScorePoint_column1_duration) {
        if (canScorePoint_column1 == true) {
            canScorePoint_column1 = false;
            score++;
        }
    }
    if ( millis() > next_light_2 ) {

        if (column2InProgress1 == false) {
            column2InProgress1 = true;
            leds[10] = CRGB::MediumVioletRed; FastLED.show();
            next_column_2  = next_light_2 + LED_delay; 
            j = 11;
            getNextTime_button2();
            Print_Next_Times();
        }
        else if (column2InProgress2 == false) {
            column2InProgress2 = true;
            leds[10] = CRGB::MediumVioletRed; FastLED.show();
            next_column_2_2  = next_light_2 + LED_delay; 
            j_2 = 11;
            getNextTime_button2();
            Print_Next_Times();
        }
        else if (column2InProgress3 == false) {
            column2InProgress3 = true;
            leds[10] = CRGB::MediumVioletRed; FastLED.show();
            next_column_2_3  = next_light_2 + LED_delay; 
            j_3 = 11;
            getNextTime_button2();
            Print_Next_Times();
        }
    }
    if ( (millis() > next_column_2) && (column2InProgress1 == true) ) {

        if (j < 20) {
            leds[j - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            leds[j] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            // Serial.println("on");
            j++;
            next_column_2 += LED_delay; 
            // Serial.print("updated next_column_1: ");
            // Serial.println(next_column_1);
        }
        else {
            leds[j - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            next_column_2 = next_light_2;
            column2InProgress1 = false;
        }
    }
    if ( (millis() > next_column_2_2) && (column2InProgress2 == true) ) {

        if (j_2 < 20) {
            leds[j_2 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            leds[j_2] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            // Serial.println("on");
            j_2++;
            next_column_2_2 += LED_delay; 
            // Serial.print("updated next_column_1: ");
            // Serial.println(next_column_1);
        }
        else {
            leds[j_2 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            next_column_2_2 = next_light_2;
            column2InProgress2 = false;
        }
    }
    if ( (millis() > next_column_2_3) && (column2InProgress3 == true) ) {

        if (j_3 < 20) {
            leds[j_3 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            leds[j_3] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            // Serial.println("on");
            j_3++;
            next_column_2_3 += LED_delay; 
            // Serial.print("updated next_column_1: ");
            // Serial.println(next_column_1);
        }
        else {
            leds[j_3 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            next_column_2_3 = next_light_2;
            column2InProgress3 = false;
        }
    }
    
    if ( millis() > next_light_3 ) {

        if (column3InProgress1 == false) {
            column3InProgress1 = true;
            leds[20] = CRGB::MediumVioletRed; FastLED.show();
            next_column_3  = next_light_3 + LED_delay; 
            k = 21;
            getNextTime_button3();
            Print_Next_Times();
        }
        else if (column3InProgress2 == false) {
            column3InProgress2 = true;
            leds[20] = CRGB::MediumVioletRed; FastLED.show();
            next_column_3_2  = next_light_3 + LED_delay; 
            k_2 = 21;
            getNextTime_button3();
            Print_Next_Times();
        }
        else if (column1InProgress3 == false) {
            column3InProgress3 = true;
            leds[20] = CRGB::MediumVioletRed; FastLED.show();
            next_column_3_3  = next_light_3 + LED_delay; 
            k_3 = 21;
            getNextTime_button3();
            Print_Next_Times();
        }
    }
    if ( (millis() > next_column_3) && (column3InProgress1 == true) ) {

        if (k < 30) {
            leds[k - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            leds[k] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            // Serial.println("on");
            k++;
            next_column_3 += LED_delay; 
            // Serial.print("updated next_column_1: ");
            // Serial.println(next_column_1);
        }
        else {
            leds[k - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            next_column_3 = next_light_3;
            column3InProgress1 = false;
        }
    }
    if ( (millis() > next_column_3_2) && (column3InProgress2 == true) ) {

        if (k_2 < 30) {
            leds[k_2 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            leds[k_2] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            // Serial.println("on");
            k_2++;
            next_column_3_2 += LED_delay; 
            // Serial.print("updated next_column_1: ");
            // Serial.println(next_column_1);
        }
        else {
            leds[k_2 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            next_column_2_2 = next_light_1;
            column3InProgress2 = false;
        }
    }
    if ( (millis() > next_column_3_3) && (column3InProgress3 == true) ) {

        if (k_3 < 30) {
            leds[k_3 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            leds[k_3] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            // Serial.println("on");
            k_3++;
            next_column_3_3 += LED_delay; 
            // Serial.print("updated next_column_1: ");
            // Serial.println(next_column_1);
        }
        else {
            leds[k_3 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            next_column_3_3 = next_light_3;
            column3InProgress3 = false;
        }
    }

    if ( millis() > next_light_4 ) {

        if (column4InProgress1 == false) {
            column4InProgress1 = true;
            leds[30] = CRGB::MediumVioletRed; FastLED.show();
            next_column_4  = next_light_4 + LED_delay; 
            l = 31;
            getNextTime_button4();
            Print_Next_Times();
        }
        else if (column4InProgress2 == false) {
            column4InProgress2 = true;
            leds[30] = CRGB::MediumVioletRed; FastLED.show();
            next_column_4_2  = next_light_4 + LED_delay; 
            l_2 = 31;
            getNextTime_button4();
            Print_Next_Times();
        }
        else if (column4InProgress3 == false) {
            column4InProgress3 = true;
            leds[30] = CRGB::MediumVioletRed; FastLED.show();
            next_column_4_3  = next_light_4 + LED_delay; 
            l_3 = 31;
            getNextTime_button4();
            Print_Next_Times();
        }
    }
    if ( (millis() > next_column_4) && (column4InProgress1 == true) ) {

        if (l < 40) {
            leds[l - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            leds[l] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            // Serial.println("on");
            l++;
            next_column_4 += LED_delay; 
            // Serial.print("updated next_column_1: ");
            // Serial.println(next_column_1);
        }
        else {
            leds[l - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            next_column_4 = next_light_4;
            column4InProgress1 = false;
        }
    }
    if ( (millis() > next_column_4_2) && (column4InProgress2 == true) ) {

        if (l_2 < 40) {
            leds[l_2 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            leds[l_2] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            // Serial.println("on");
            l_2++;
            next_column_4_2 += LED_delay; 
            // Serial.print("updated next_column_1: ");
            // Serial.println(next_column_1);
        }
        else {
            leds[l_2 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            next_column_4_2 = next_light_4;
            column4InProgress2 = false;
        }
    }
    if ( (millis() > next_column_4_3) && (column4InProgress3 == true) ) {

        if (l_3 < 40) {
            leds[l_3 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            leds[l_3] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            // Serial.println("on");
            l_3++;
            next_column_4_3 += LED_delay; 
            // Serial.print("updated next_column_1: ");
            // Serial.println(next_column_1);
        }
        else {
            leds[l_3 - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            // Serial.println("off");
            next_column_4_3 = next_light_4;
            column4InProgress3 = false;
        }
    }
}