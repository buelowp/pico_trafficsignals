#include "signal.h"

static int64_t delay_complete(alarm_id_t id, void *user_data)
{
    int pin = (intptr_t)user_data;
    gpio_put(pin, GPIO_HIGH);
    return 0;
}

Signal::Signal(uint red, uint yellow, uint green, SignalState state) : m_red(red), m_yellow(yellow), m_green(green), m_state(state)
{
    m_delay = 100;

    gpio_init(m_red);
    gpio_init(m_yellow);
    gpio_init(m_green);

    gpio_set_dir(m_red, GPIO_OUT);
    gpio_set_dir(m_yellow, GPIO_OUT);
    gpio_set_dir(m_green, GPIO_OUT);

    gpio_put(m_red, GPIO_LOW);
    gpio_put(m_yellow, GPIO_LOW);
    gpio_put(m_green, GPIO_LOW);

    alarm_pool_init_default();
}

Signal::Signal(Signal &other)
{
    m_red = other.m_red;
    m_yellow = other.m_yellow;
    m_green = other.m_green;
    m_state = other.m_state;
}

Signal::~Signal()
{}

void Signal::stateChange(SignalState state)
{
    switch (state) {
        case RED:
            gpio_put(m_red, GPIO_HIGH);
            gpio_put(m_yellow, GPIO_LOW);
            gpio_put(m_green, GPIO_LOW);
            break;
        case YELLOW:
            gpio_put(m_red, GPIO_LOW);
            gpio_put(m_yellow, GPIO_HIGH);
            gpio_put(m_green, GPIO_LOW);
            break;
        case GREEN:
            gpio_put(m_red, GPIO_LOW);
            gpio_put(m_yellow, GPIO_LOW);
            gpio_put(m_green, GPIO_HIGH);
            break;
    }
    m_state = state;
}

void Signal::stateChange()
{
    switch (m_state) {
        case RED:
            gpio_put(m_red, GPIO_LOW);
            m_alarmId = add_alarm_in_ms(m_delay, delay_complete, (void*)((intptr_t)m_green), true);
            m_state = GREEN;
            break;
        case YELLOW:
            gpio_put(m_yellow, GPIO_LOW);
            m_alarmId = add_alarm_in_ms(m_delay, delay_complete, (void*)((intptr_t)m_red), true);
            m_state = RED;
            break;
        case GREEN:
            gpio_put(m_green, GPIO_LOW);
            m_alarmId = add_alarm_in_ms(m_delay, delay_complete, (void*)((intptr_t)m_yellow), true);
            m_state = YELLOW;
            break;
    }
}
