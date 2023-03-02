#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ofstream outFS; // Output file stream

    // Open file
    outFS.open("song1_times.csv");

    if (!outFS.is_open()) {
        cout << "Could not open file song1_times.csv." << endl;
        return 1;
    }

    // TODO
    // play song


    // TODO
    // while the song is playing, see when certain keys are pressed and record the time at which they are pressed into an array
    // this array will be printed into the output file
    // USE cstream and time functions 
    // remember to read timestamp after every cstream input; check if key is desired later; pushback to array if it is the desired key
    //
    vector<int> time_of_press(5, 0);


    // Write to file
    outFS << "long long song1[] = {";
    for (int i = 0; i < time_of_press.size() - 1; i++) {
        outFS << time_of_press.at(i) << ", ";
    }
    outFS << time_of_press.at(time_of_press.size() - 1) << "};" << endl;
    outFS << "Hello" << endl;
    outFS << "1 2 3" << endl;

    // Done with file, so close
    outFS.close();

    return 0;
}