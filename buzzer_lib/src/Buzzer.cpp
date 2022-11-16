//
// Created by cem on 23/05/2022.
//

#include "Buzzer.h"
#include <Arduino.h>

static unsigned buzzer_counter = 0;

Buzzer::Buzzer(unsigned pin) : pin_(pin), channel_(buzzer_counter) {
    ledcSetup(buzzer_counter,1E4,12);
    ledcAttachPin(pin_,0);
    buzzer_counter++;
}

Song::Song(Sheet sheet_, unsigned long unitDuration_): sheet(sheet_),
                                                    unit_duration(unitDuration_),
                                                    last_note(sheet.size() - 1),
                                                    note_begin_time(-1 + millis()
                                                                    + unit_duration
                                                                    * std::get<2>(sheet[last_note])){}
