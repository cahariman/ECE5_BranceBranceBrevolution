#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

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
    high_resolution_clock::time_point song_start_time = high_resolution_clock::now();
    vector<int> time_of_press(1, -1);
    vector<int> key_pressed(1,-1);


    // TODO
    // while the song is playing, see when certain keys are pressed and record the time at which they are pressed into an array
    // this array will be printed into the output file
    // USE cstream and time functions 
    // remember to read timestamp after every cstream input; check if key is desired later; pushback to array if it is the desired key

    // below code sleeps for x milliseconds
    // this_thread::sleep_for(milliseconds(x));

    char c;
    cout << "enter: ";
    cin >> c;
    cout << "done" << endl;
    high_resolution_clock::time_point time_now = high_resolution_clock::now();
    duration<long, milli> time_since_song_start = duration_cast<milliseconds>(time_now - song_start_time);
    cout << time_since_song_start.count() << endl;
    time_of_press.push_back( time_since_song_start.count() );
    key_pressed.push_back( c );
    cout << "test1" << endl;
    // while (time_since_song_start.count() < 50) {
    //     cout << "test2" << endl;

    //     high_resolution_clock::time_point time_now = high_resolution_clock::now();
    //     duration<double, milli> time_since_song_start = time_now - song_start_time;
    //     cout << time_since_song_start.count() << endl;
    //     // if (true) {
    //     //     time_of_press.push_back( time_since_song_start.count() );
    //     // }
    // }
    cout << "test3" << endl;
    // Write to file
    outFS << endl;
    outFS << "long long song1_times[] = {";
    for (int i = 0; i < time_of_press.size() - 1; i++) {
        outFS << time_of_press.at(i) << ", ";
    }
    outFS << time_of_press.at(time_of_press.size() - 1) << "};" << endl;

    outFS << "long long song1_keys[] = {";
    for (int i = 0; i < key_pressed.size() - 1; i++) {
        outFS << key_pressed.at(i) << ", ";
    }
    outFS << key_pressed.at(key_pressed.size() - 1) << "};" << endl;
    outFS << "Hello" << endl;
    outFS << "1 2 3" << endl;

    // Done with file, so close
    outFS.close();

    return 0;
}