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
