#pragma once

#include <string>
#include <chrono>

namespace AbletonProject
{
    enum LogLevel { INFO };

    class EventBase
    {
    protected:
        EventBase() {};
    public:
        virtual ~EventBase() = default;
        virtual std::string getName() const = 0;
        virtual std::chrono::high_resolution_clock::time_point getTime() const = 0;
        virtual std::string getDetail() const = 0;
        virtual LogLevel getLogLevel() const = 0;
        virtual std::string getEventSource() const = 0;
    };
}