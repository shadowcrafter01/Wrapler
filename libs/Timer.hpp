#ifndef TIMER_HPP
#define TIMER_HPP

#include <atomic>
#include <chrono>
#include <cstdint>
#include <thread>
#include <iostream>
#include <iomanip>
#include <stdexcept>

/*
class Timer//scratch esque timer and fps handling
{
private:
    bool active;
    double timeLast;
    double timeStart;

    std::thread trackTime;
    void trackMS()
    {
        while (active)
        {
            nanoseconds=std::chrono::system_clock::now().time_since_epoch().count()-timeStart;
            milliseconds=nanoseconds/1000000;
            seconds=nanoseconds/1000000000;
        }
    }


public:
    Timer(double TPS=20):
    targetTPS{TPS},timeStart{timeStart=std::chrono::system_clock::now().time_since_epoch().count()}
    {
        active=true;
        trackTime=std::thread(&Timer::trackMS,this);
    }
    ~Timer()
    {
        active=false;
        trackTime.join();
    }

    double targetTPS;
    double seconds;
    double milliseconds;
    double nanoseconds;
    double fps;
    double delta;
    double physDelta;

    void update()
    {
        //nanoseconds=std::chrono::system_clock::now().time_since_epoch().count()-timeStart;
        //milliseconds=nanoseconds/1000000;
        //seconds=nanoseconds/1000000000;
        fps=1/(seconds-timeLast);
        delta=(seconds-timeLast)*targetTPS;
        physDelta=(delta>1)? 1:delta;
        timeLast=seconds;
    }

    //void stop()
    //{
        //active=false;
        //trackTime.join();
    //}
};
*/

class Timer
{
public:
    Timer(double target_fps = 1000) : _running(true),
                                      _currentNs(0),
                                      targetFPS(target_fps),
                                      FPS(0)
    {
        _thread = std::thread(&Timer::run, this);
    }

    ~Timer()
    {
        stop();
    }

    // Non-copyable, non-movable
    Timer(const Timer &) = delete;
    Timer &operator=(const Timer &) = delete;

    // Returns the latest captured nanosecond count since epoch of steady_clock
    double now_ns() const noexcept
    {
        return _currentNs.load(std::memory_order_acquire);
    }

    double now_ms() const noexcept
    {
        return _currentNs.load(std::memory_order_acquire) / 1000000.0f;
    }

    double now_s() const noexcept
    {
        return _currentNs.load(std::memory_order_acquire) / 1000000000.0f;
    }

    void update()
    {
        double now = now_ns();
        delta = (now - timeLast) / 1000000000.0f;
        physicsDelta = delta * targetFPS;
        if (physicsDelta > 1)
            physicsDelta = 1;
        timeLast = now;
        if (delta == 0)
        {
            FPS = 0;
        }
        else
        {
            FPS = (0.5 * FPS) + ((1 / delta) * (1 - 0.5));
        }
    }
    double physicsDelta;
    double delta;
    double FPS;
    double targetFPS;

    // Stop the updating thread
    void stop()
    {
        bool expected = true;
        if (_running.compare_exchange_strong(expected, false))
        {
            if (_thread.joinable())
            {
                _thread.join();
            }
        }
    }

private:
    void run()
    {
        // Capture the steady_clock epoch once, then measure offsets
        const auto start = std::chrono::steady_clock::now();

        while (_running.load(std::memory_order_acquire))
        {
            auto elapsed = std::chrono::steady_clock::now() - start;
            uint64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
            _currentNs.store(ns, std::memory_order_release);
        }
    }

    double timeLast = 0;
    std::atomic<bool> _running;
    std::atomic<uint64_t> _currentNs;
    std::thread _thread;
};

extern Timer ENG_timer;

#endif