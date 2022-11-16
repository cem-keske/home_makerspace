//
// Created by cem on 23/05/2022.
//

#ifndef BUZZER_LIB_BUZZER_H
#define BUZZER_LIB_BUZZER_H
#include <tuple>
#include <vector>
#include <Arduino.h>

typedef unsigned Note_duration;
typedef int Octave;
typedef std::tuple<note_t, Octave, Note_duration> Music_note;
typedef std::vector<Music_note> Sheet;



struct Song {
    Song(Sheet sheet, unsigned long unitDuration);

    Sheet sheet;
    unsigned long unit_duration;
    size_t last_note;
    unsigned long note_begin_time;
};




class Buzzer {
    unsigned pin_;
    unsigned channel_;
    unsigned long play_duration_;
    unsigned long play_started_;
    std::vector<Song> songs;

public:
    Buzzer(unsigned pin);
};




template <typename T>
std::vector<T> operator+(std::vector<T> const &x, std::vector<T> const &y)
{
    std::vector<T> vec;
    vec.reserve(x.size() + y.size());
    vec.insert(vec.end(), x.begin(), x.end());
    vec.insert(vec.end(), y.begin(), y.end());
    return vec;
}

template <typename T>
std::vector<T> &operator+=(std::vector<T> &x, const std::vector<T> &y)
{
    x.reserve(x.size() + y.size());
    x.insert(x.end(), y.begin(), y.end());
    return x;
}

#endif //BUZZER_LIB_BUZZER_H
