#pragma once

#include "pico/stdlib.h"
#include "pico/sync.h"
#include "hardware/gpio.h"

#include "signal.h"

class Intersection {
public:

    typedef enum INT_STATE {
        PRIMARY_RED,
        PRIMARY_YELLOW,
        PRIMARY_GREEN,
    } IntersectionState;

    typedef enum DIRECTION {
        IS_RED,
        IS_YELLOW,
        IS_GREEN,
    } Direction;

    Intersection(Signal *primary, Signal *opposed);
    ~Intersection();

    void setDirection(Direction direction);
    void setTimeouts(uint red, uint yellow, uint green);
    void run();

private:
    Signal *m_primary;
    Signal *m_opposed;
    IntersectionState m_state;
    Direction m_primaryDirection;
    Direction m_opposedDirection;
    uint m_redTimeout;
    uint m_greenTimeout;
    uint m_yellowTimeout;
    uint m_primaryCountdown;
    uint m_opposedCountdown;
};
