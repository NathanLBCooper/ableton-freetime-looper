#pragma once

#include <string>
#include <chrono>
#include "IEvent.h"

namespace LiveFreetimeLooper
{

    class StateChangedEvent final : public IEvent
    {
    private:
        std::chrono::high_resolution_clock::time_point _time;
        std::string _detail;
        std::string _eventSource;
    public:
        StateChangedEvent(std::string detail, std::string eventSource);

        std::string getName() const override;
        std::chrono::high_resolution_clock::time_point getTime() const override;
        std::string getDetail() const override;
        LogLevel getLogLevel() const override;
        std::string getEventSource() const override;
    }; 
}
