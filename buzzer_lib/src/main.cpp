
#include <Arduino.h>
#include <tuple>
#include "Buzzer.h"

unsigned TONE_PWM_CHANNEL = 0;

void play_song(Song* song){
        if (song->note_begin_time + song->unit_duration * std::get<2>(song->sheet[song->last_note]) <= millis()) {
        song->last_note++;
        if (song->last_note >= song->sheet.size()) song->last_note = 0;

        note_t note = std::get<0>(song->sheet[song->last_note]);
        int octave = std::get<1>(song->sheet[song->last_note]);

        if (octave == -1) ledcWrite(0,0);
        else ledcWriteNote(0, note, octave);

        song->note_begin_time = millis();
    }
}

void setup() {
    ledcSetup(0,1E4,12);
    ledcAttachPin(23,0);
    Serial.begin(112500);
};
Music_note note1 = {NOTE_A,5,500};
Sheet coffin1({{NOTE_A,4,2},{NOTE_A,-1,2},{NOTE_A,4,2},{NOTE_E,5,2},{NOTE_D,5,4},{NOTE_C,5,4},
               {NOTE_B,4,2},{NOTE_C,-1,2},{NOTE_B,4,1},{NOTE_B,-1,1},{NOTE_B,4,1},{NOTE_B,-1,1},
               {NOTE_D,5,4},{NOTE_C,5,2},{NOTE_B,4,2},
               {NOTE_A,4,2},{NOTE_A,-1,2},{NOTE_A,4,2},{NOTE_C,6,2},{NOTE_B,5,2},{NOTE_C,6,2},{NOTE_B,5,2},{NOTE_C,6,2},
               {NOTE_A,4,2},{NOTE_A,-1,2},{NOTE_A,4,2},{NOTE_C,6,2},{NOTE_B,5,2},{NOTE_C,6,2},{NOTE_B,5,2},{NOTE_C,6,2}});

Sheet coffin2({{NOTE_C,5,1},{NOTE_C,-1,1},{NOTE_C,5,1},{NOTE_C,-1,1},{NOTE_C,5,1},{NOTE_C,-1,1},{NOTE_C,5,1},{NOTE_C,-1,1},
               {NOTE_E,5,1},{NOTE_E,-1,1},{NOTE_E,5,1},{NOTE_E,-1,1},{NOTE_E,5,1},{NOTE_E,-1,1},{NOTE_E,5,1},{NOTE_E,-1,1},
               {NOTE_D,5,1},{NOTE_D,-1,1},{NOTE_D,5,1},{NOTE_D,-1,1},{NOTE_D,5,1},{NOTE_D,-1,1},{NOTE_D,5,1},{NOTE_D,-1,1},
               {NOTE_G,5,1},{NOTE_G,-1,1},{NOTE_G,5,1},{NOTE_G,-1,1},{NOTE_G,5,1},{NOTE_G,-1,1},{NOTE_G,5,1},{NOTE_G,-1,1},});

Sheet coffin_drop({{NOTE_A,5,1},{NOTE_A,-1,1},{NOTE_A,5,1},{NOTE_A,-1,1},{NOTE_A,5,1},{NOTE_A,-1,1},{NOTE_A,5,1},{NOTE_A,-1,1},
                   {NOTE_A,5,1},{NOTE_A,-1,1},{NOTE_A,5,1},{NOTE_A,-1,1},{NOTE_A,5,1},{NOTE_A,-1,1},{NOTE_A,5,1},{NOTE_A,-1,1},
                   {NOTE_A,5,1},{NOTE_A,-1,1},{NOTE_A,5,1},{NOTE_A,-1,1},{NOTE_A,5,1},{NOTE_A,-1,1},{NOTE_A,5,1},{NOTE_A,-1,1},
                   {NOTE_D,5,1},{NOTE_A,-1,1},{NOTE_C,5,1},{NOTE_A,-1,1},{NOTE_B,4,1},{NOTE_A,-1,1},{NOTE_G,4,1},{NOTE_A,-1,1},});


Song coffin_dance({{NOTE_A,4,2},{NOTE_A,-1,2},{NOTE_A,4,2},{NOTE_E,5,2},{NOTE_D,5,4},{NOTE_C,5,4},
              {NOTE_B,4,2},{NOTE_C,-1,2},{NOTE_B,4,1},{NOTE_B,-1,1},{NOTE_B,4,1},{NOTE_B,-1,1},
              {NOTE_D,5,4},{NOTE_C,5,2},{NOTE_B,4,2},
              {NOTE_A,4,2},{NOTE_A,-1,2},{NOTE_A,4,2},{NOTE_C,6,2},{NOTE_B,5,2},{NOTE_C,6,2},{NOTE_B,5,2},{NOTE_C,6,2},
              {NOTE_A,4,2},{NOTE_A,-1,2},{NOTE_A,4,2},{NOTE_C,6,2},{NOTE_B,5,2},{NOTE_C,6,2},{NOTE_B,5,2},{NOTE_C,6,2}},
             50);

Song coffin_full(( coffin1 + coffin1 + coffin2 + coffin_drop),100);

void loop() {
    play_song(&coffin_full);
    delay(1);
}

