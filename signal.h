#pragma once

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