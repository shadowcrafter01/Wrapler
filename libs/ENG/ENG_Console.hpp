#ifndef ENG_CONSOLE_HPP
#define ENG_CONSOLE_HPP

#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <ENG_Timer.hpp>

class ENG_Console
{
private:
    static std::string reportCurrentMS()
    {
        std::string time = std::to_string(std::round(timer->now_ms() * 100) / 100);
        std::string buffer = "";
        int decimal = 0;
        for (char i : time)
        {
            if (i == '.' || decimal > 0)
                decimal++;
            if (decimal > 3)
                break;
            buffer = buffer + i;
        }

        for (int i = buffer.length(); i < 8; ++i)
        {
            buffer = " " + buffer;
        }

        return "[" + buffer + "]";
    }

    inline static ENG_Timer* timer;

public:
    ENG_Console(ENG_Timer* timer_in)
    {
        timer = timer_in;
    }

    static void Log(std::string message, std::string label = "")
    {
        std::cout << label << message << "\n";
    }

    static void LogInfo(std::string message)
    {
        std::cout << reportCurrentMS() << " -INFO : " << message << "\n";
    }

    static void LogDebug(double message)
    {
        std::cout << reportCurrentMS() << " -DEBUG: " << message << "\n";
    }

    static void LogError(std::string message = "")
    {
        std::cout << reportCurrentMS() << " -ERROR: " << message << " -> " << SDL_GetError();
    }
};
//static ENG_Console console;

#endif