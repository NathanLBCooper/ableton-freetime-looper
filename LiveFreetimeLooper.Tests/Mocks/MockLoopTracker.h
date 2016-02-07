#pragma once

#include <memory>
#include <vector>
#include <cstdint>

#include "..\..\LiveFreetimeLooper\Messaging\ILoopTracker.h"
#include "..\..\LiveFreetimeLooper\Messaging\Message.h"
#include "..\..\LiveFreetimeLooper\Messaging\Loop.h"


class MockLoopTracker final : public LiveFreetimeLooper::ILoopTracker
{
private:
    std::vector<std::unique_ptr<LiveFreetimeLooper::Message>> _commandsReceived;
    std::int32_t _interval;
    std::int32_t _nextRestartMessagesCallCount;
    bool _cleared;
public:
    MockLoopTracker();

    void commandReceived(std::unique_ptr<LiveFreetimeLooper::Message> message);
    std::vector<LiveFreetimeLooper::Message*> getNextRestartMessages();
    void incrementInterval();
    void clear();

    std::vector<std::unique_ptr<LiveFreetimeLooper::Message>> const& getCommandsReceived() const;
    std::int32_t const& getInterval() const;
    std::int32_t const& getNextRestartMessagesCallCount() const;
    bool isCleared() const;
};