#pragma once
/*
Pico Traffic Signals
Copyright (C) 2021  goballstate at gmail

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "pico/stdlib.h" 
#include "hardware/gpio.h"

#define GPIO_LOW    0
#define GPIO_HIGH   1

class Signal
{
public:
    typedef enum SIGNALSTATE {
        RED,
        YELLOW,
        GREEN,
    } SignalState;

    Signal(uint red, uint yellow, uint green, SignalState state = SignalState::RED);
    ~Signal();
    Signal(Signal &other);

    void stateChange();
    void stateChange(SignalState);
    void changeDelay(uint d) { m_delay = d; }

private:
    uint m_red;
    uint m_yellow;
    uint m_green;
    uint m_delay;
    SignalState m_state;
    alarm_id_t m_alarmId;
};