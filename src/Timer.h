#pragma once

class Timer
{
public:

    Timer();
    Timer(unsigned long);

    unsigned long GetTime();

    void start(unsigned long);
    bool timeOut();
    bool active();
    void restart();
    unsigned long timeLeft();
    unsigned long timeOn();
protected:
    unsigned long m_period;
    unsigned long m_target;
};
