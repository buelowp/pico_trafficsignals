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

#include "intersection.h"

Intersection::Intersection(Signal *primary, Signal *opposed)
{
    m_primary = primary;
    m_opposed = opposed;

    m_redTimeout = 30000;
    m_yellowTimeout = 3000;
    m_greenTimeout = 27000;

    m_primary->stateChange(Signal::SignalState::RED);
    m_opposed->stateChange(Signal::SignalState::GREEN);

    m_primaryDirection = IS_RED;
    m_opposedDirection = IS_GREEN;

    m_primaryCountdown = m_redTimeout;
    m_opposedCountdown = m_greenTimeout;
}

Intersection::~Intersection()
{}

/**
 * @brief The forever loop for this function. Sets the
 * direction and the color as the timer counts down
 * 
 */
void Intersection::run()
{
    while (1) {
        if (--m_primaryCountdown <= 0) {
            switch (m_primaryDirection) {
                case IS_RED:
                    m_primaryCountdown = m_greenTimeout;
                    m_primaryDirection = IS_GREEN;
                    break;
                case IS_YELLOW:
                    m_primaryCountdown = m_redTimeout;
                    m_primaryDirection = IS_RED;
                    break;
                case IS_GREEN:
                    m_primaryCountdown = m_yellowTimeout;
                    m_primaryDirection = IS_YELLOW;
                    break;
            }
            m_primary->stateChange();
        }
        if (--m_opposedCountdown <= 0) {
            switch (m_opposedDirection) {
                case IS_RED:
                    m_opposedCountdown = m_greenTimeout;
                    m_opposedDirection = IS_GREEN;
                    break;
                case IS_YELLOW:
                    m_opposedCountdown = m_redTimeout;
                    m_opposedDirection = IS_RED;
                    break;
                case IS_GREEN:
                    m_opposedCountdown = m_yellowTimeout;
                    m_opposedDirection = IS_YELLOW;
                    break;
            }
            m_opposed->stateChange();
        }
        sleep_ms(1);
    }
}
