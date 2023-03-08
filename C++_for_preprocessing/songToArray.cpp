#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include "conio.h"

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
    vector<unsigned long> song1_key1_times(1, -1);
    vector<unsigned long> song1_key2_times(1, -1);
    vector<unsigned long> song1_key3_times(1, -1);
    vector<unsigned long> song1_key4_times(1, -1);


    // while the song is playing, see when certain keys are pressed and record the time at which they are pressed into an array
    // this array will be printed into the output file
    // USE cstream and time functions 
    // remember to read timestamp after every cstream input; check if key is desired later; pushback to array if it is the desired key

    // below code sleeps for x milliseconds
    // this_thread::sleep_for(milliseconds(x));

    char c;
    cout << "enter: ";
    // cin >> c;

    high_resolution_clock::time_point time_now;
    duration<long, milli> time_since_song_start;
    while(c != 'b') {
        if (kbhit()) {
            c = getch();
            cout << "You pressed: " << c << endl;
            time_now = high_resolution_clock::now();
            time_since_song_start = duration_cast<milliseconds>(time_now - song_start_time);
            cout << time_since_song_start.count() << endl;
            switch (c) {
                case 'd':
                    song1_key1_times.push_back(time_since_song_start.count());
                    cout << "added to song1_key1_times" << endl;
                    break;
                case 'f':
                    song1_key2_times.push_back(time_since_song_start.count());
                    cout << "added to song1_key2_times" << endl;
                    break;
                case 'j':
                    song1_key3_times.push_back(time_since_song_start.count());
                    cout << "added to song1_key3_times" << endl;
                    break;
                case 'k':
                    song1_key4_times.push_back(time_since_song_start.count());
                    cout << "added to song1_key4_times" << endl;
                    break;
            }
        }
    }
    cout << "done" << endl;


    // high_resolution_clock::time_point time_now = high_resolution_clock::now();
    // duration<long, milli> time_since_song_start = duration_cast<milliseconds>(time_now - song_start_time);
    // cout << time_since_song_start.count() << endl;


    // song1_key1_times.push_back( time_since_song_start.count() );
    // song1_key2_times.push_back( c );
    // cout << "test1" << endl;
    // while (time_since_song_start.count() < 50) {
    //     cout << "test2" << endl;

    //     high_resolution_clock::time_point time_now = high_resolution_clock::now();
    //     duration<double, milli> time_since_song_start = time_now - song_start_time;
    //     cout << time_since_song_start.count() << endl;
    //     // if (true) {
    //     //     song1_key1_times.push_back( time_since_song_start.count() );
    //     // }
    // }
    //cout << "test3" << endl;


    // Write to file
    outFS << endl;
    outFS << "unsigned long song1_key1_times[] = {";
    for (int i = 0; i < song1_key1_times.size() - 1; i++) {
        outFS << song1_key1_times.at(i) << ", ";
    }
    outFS << song1_key1_times.at(song1_key1_times.size() - 1) << "};" << endl;

    outFS << "unsigned long song1_key2_times[] = {";
    for (int i = 0; i < song1_key2_times.size() - 1; i++) {
        outFS << song1_key2_times.at(i) << ", ";
    }
    outFS << song1_key2_times.at(song1_key2_times.size() - 1) << "};" << endl;

    outFS << "unsigned long song1_key3_times[] = {";
    for (int i = 0; i < song1_key3_times.size() - 1; i++) {
        outFS << song1_key3_times.at(i) << ", ";
    }
    outFS << song1_key3_times.at(song1_key3_times.size() - 1) << "};" << endl;

    outFS << "unsigned long song1_key4_times[] = {";
    for (int i = 0; i < song1_key4_times.size() - 1; i++) {
        outFS << song1_key4_times.at(i) << ", ";
    }
    outFS << song1_key4_times.at(song1_key4_times.size() - 1) << "};" << endl;

    outFS   <<  "int w = 1;" << endl;
    outFS   <<  "int a = 1;" << endl;
    outFS   <<  "int s = 1;" << endl;
    outFS   <<  "int d = 1;" << endl;

    outFS << "Hello" << endl;
    outFS << "1 2 3" << endl;

    // Done with file, so close
    outFS.close();

    return 0;
}