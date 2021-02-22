#include "intersection.h"

Intersection::Intersection(Signal *primary, Signal *opposed)
{
    m_primary = primary;
    m_opposed = opposed;

    m_redTimeout = 30000;
    m_yellowTimeout = 4000;
    m_greenTimeout = 26000;

    m_primary->stateChange(Signal::SignalState::RED);
    m_opposed->stateChange(Signal::SignalState::GREEN);

    m_primaryDirection = IS_RED;
    m_opposedDirection = IS_GREEN;

    m_primaryCountdown = m_redTimeout;
    m_opposedCountdown = m_greenTimeout;
}

Intersection::~Intersection()
{}

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