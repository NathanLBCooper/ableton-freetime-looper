#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "ILoopTracker.hpp"
#include "Message.hpp"
#include "RunningLoop.hpp"
#include "RecordingLoop.hpp"

namespace LiveFreetimeLooper
{
    class LoopTracker final : public ILoopTracker
    {
    private:
        std::unordered_map<Message, std::unique_ptr<RecordingLoop>> _recording;
        std::unordered_map<Message, std::unique_ptr<RunningLoop>> _running;
    public:
        LoopTracker();

        void commandReceived(std::unique_ptr<Message> message);
        std::vector<Message*> getNextRestartMessages();
        void incrementInterval();
        void clear();

    };
}