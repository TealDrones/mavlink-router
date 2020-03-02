#include <stdint.h>
#include <stdio.h>
#include <math.h> 
#include <time.h>
#include "Timer.h"

Timer::Timer()
  : m_period(0)
  , m_target(0)
{
    start(0);
}

Timer::Timer(unsigned long interval)
  : m_period(0)
  , m_target(0)
{
    start(interval);
}

void Timer::start(unsigned long interval)
{
    m_period = interval * 1000;
    m_target = GetTime() + m_period;
}

unsigned long Timer::GetTime ()
{
    unsigned long ms; // Milliseconds
    time_t s;  // Seconds
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    ms = spec.tv_sec * 1000;
    ms += (unsigned long) round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds

    return ms;
}


bool Timer::timeOut()
{
    unsigned long now = GetTime();
    if (m_period > 0 && m_target > 0 && now >= m_target) {
        m_target = 0;
        return true;
    }
    return false;
}

bool Timer::active()
{
    return !timeOut();
}

void Timer::restart()
{
    m_target = GetTime() + m_period;
}

/**
 * 
 * Time until timer runs out
 * 
 */
unsigned long Timer::timeLeft() {
    unsigned long now = GetTime();
    return m_target - now;
}

/**
 * 
 * Time since timer was started
 * 
 */
unsigned long Timer::timeOn() {
    unsigned long now = GetTime();
    return m_target - now;
}


