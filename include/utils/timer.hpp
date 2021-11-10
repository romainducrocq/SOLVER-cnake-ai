#ifndef _TIMER_H
#define _TIMER_H

#include <iostream>
#include <chrono>

struct Timer
{
    std::chrono::_V2::system_clock::time_point m_start, m_end;
    std::chrono::duration<float> m_duration;

    Timer()
    {
        this->m_start = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        this->m_end = std::chrono::high_resolution_clock::now();
        this->m_duration = this->m_end - this->m_start;

        float ms = this->m_duration.count() * 1000.0f;
        std::cout << "Time: " << ms << "ms" << std::endl;
    }
};

#endif