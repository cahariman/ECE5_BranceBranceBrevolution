
#define NUM_LEDS 110
#define DATA_PIN 4


const int LED_delay = 70;

// arrays that represent when stuff should happen; will come from C++ program
// below example arrays mark that first button should be pressed 1000 ms after song starts
// 2nd button should be pressed 1500ms after song starts
// 3rd button should be pressed 2000ms after song starts
// future: first element will have number of times; "size" of the array

long long song1_key1_times[] = {-1, 1302, 999999999999999};
long long song1_key2_times[] = {-1, 1961, 999999999999999};
long long song1_key3_times[] = {-1, 2167, 99999999999999999};
long long song1_key4_times[] = {-1, 2622, 99999999999999999999};
int w = 1;
int a = 1;
int s = 1;
int d = 1;


// these represent the next time a light should turn on; technically when a button should be pressed after the song starts
unsigned long next_light_1 , next_light_2 , next_light_3, next_light_4;
unsigned long next_column_1 , next_column_2 , next_column_3, next_column_4;
int i, j, k, l = -1;

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
    //FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 

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

    // debugging
    Serial.begin(9600);
    Print_Next_Times();

}

// event based programming !
void loop() {

    // check if it is time to prompt for the first button
    if ( millis() > next_light_1 ) {

        // TODO
        // iterate for column 1 with fastLED.h stuff; for loop
        // at 9th or 10th row in for loop, do a button check and then score stuff
        // note: if the for loop takes more than 500ms, the code won't work because the smallest time difference in the time arrays is 500ms

        // turn on first led in column and update column delay
        //leds[0] = CRGB::MediumVioletRed; FastLED.show(); 
        Serial.println("on");
        next_column_1  = next_light_1 + LED_delay; 
        Serial.print("updated next_column_1: ");
        Serial.println(next_column_1);
        i = 1; // iterator for column

        // debugging
        Serial.println("NEXT");

        // get next time from array
        getNextTime_button1();

        // debugging
        Print_Next_Times();

    }
    if ( millis() > next_column_1 ) {

        if (i < 10) {
           // leds[i - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            Serial.println("off");
          //  leds[i] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            Serial.println("on");
            i++;
            next_column_1 += LED_delay; 
            Serial.print("updated next_column_1: ");
            Serial.println(next_column_1);
        }
        else {
         //   leds[i - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            Serial.println("off");
            next_column_1 = next_light_1;
        }

    }

    if ( millis() > next_light_2 ) {

        // TODO
        // iterate for column 1 with fastLED.h stuff; for loop
        // at 9th or 10th row in for loop, do a button check and then score stuff
        // note: if the for loop takes more than 500ms, the code won't work because the smallest time difference in the time arrays is 500ms

        // turn on first led in column and update column delay
       // leds[0] = CRGB::MediumVioletRed; FastLED.show(); 
        Serial.println("on");
        next_column_2  = next_light_2 + LED_delay; 
        Serial.print("updated next_column_2: ");
        Serial.println(next_column_2);
        j = 1; // iterator for column

        // debugging
        Serial.println("NEXT");

        // get next time from array
        getNextTime_button2();

        // debugging
        Print_Next_Times();

    }
    if ( millis() > next_column_2 ) {

        if (j < 10) {
        //    leds[j - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            Serial.println("off");
           // leds[j] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            Serial.println("on");
            j++;
            next_column_2 += LED_delay; 
            Serial.print("updated next_column_2: ");
            Serial.println(next_column_2);
        }
        else {
          //  leds[j - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            Serial.println("off");
            next_column_2 = next_light_2;
        }

    }
    
    if ( millis() > next_light_3 ) {

        // TODO
        // iterate for column 1 with fastLED.h stuff; for loop
        // at 9th or 10th row in for loop, do a button check and then score stuff
        // note: if the for loop takes more than 500ms, the code won't work because the smallest time difference in the time arrays is 500ms

        // turn on first led in column and update column delay
    //    leds[0] = CRGB::MediumVioletRed; FastLED.show(); 
        Serial.println("on");
        next_column_3  = next_light_3 + LED_delay; 
        Serial.print("updated next_column_3: ");
        Serial.println(next_column_3);
        k = 1; // iterator for column

        // debugging
        Serial.println("NEXT");

        // get next time from array
        getNextTime_button3();

        // debugging
        Print_Next_Times();

    }
    if ( millis() > next_column_3 ) {

        if (k < 10) {
     //       leds[k - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            Serial.println("off");
       //     leds[k] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            Serial.println("on");
            k++;
            next_column_3 += LED_delay; 
            Serial.print("updated next_column_3: ");
            Serial.println(next_column_3);
        }
        else {
      //      leds[k - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            Serial.println("off");
            next_column_3 = next_light_3;
        }

    }

    if ( millis() > next_light_4 ) {

        // TODO
        // iterate for column 1 with fastLED.h stuff; for loop
        // at 9th or 10th row in for loop, do a button check and then score stuff
        // note: if the for loop takes more than 500ms, the code won't work because the smallest time difference in the time arrays is 500ms

        // turn on first led in column and update column delay
    //    leds[0] = CRGB::MediumVioletRed; FastLED.show(); 
        Serial.println("on");
        next_column_4  = next_light_4 + LED_delay; 
        Serial.print("updated next_column_4: ");
        Serial.println(next_column_4);
        l = 1; // iterator for column

        // debugging
        Serial.println("NEXT");

        // get next time from array
        getNextTime_button4();

        // debugging
        Print_Next_Times();

    }
    if ( millis() > next_column_4 ) {

        if (l < 10) {
       //     leds[l - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            Serial.println("off");
      //      leds[l] = CRGB::MediumVioletRed; FastLED.show(); // turn current light on
            Serial.println("on");
            l++;
            next_column_4 += LED_delay; 
            Serial.print("updated next_column_4: ");
            Serial.println(next_column_4);
        }
        else {
     //       leds[l - 1] = CRGB::Black; FastLED.show(); // turn previous light off
            Serial.println("off");
            next_column_4 = next_light_4;
        }

    }
    
}