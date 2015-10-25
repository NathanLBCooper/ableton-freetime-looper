#pragma once
#include <memory>
#include <string>

#include "StateBase.h"
#include "Utilities/Stopwatch.h"
#include "Messaging/MessageDispatcher.h"
#include "Messaging/Message.h"
#include "Logging/EventLogger.h"
#include "Logging/StateChangedEvent.h"

// Next states:
#include "RunningState.h"
#include "CreatedState.h"

namespace AbletonProject
{
    // Waiting for and timing completion of initial loop
    class InitialLoopState final : public StateBase
    {
    private:
        Stopwatch _stopWatch;
        MessageDispatcher& _messageDispatcher;
        std::unique_ptr<Message> _loopStartingMessage;
        EventLogger& _logger;
    public:
        InitialLoopState(MessageDispatcher& messageDispatcher, EventLogger& logger, std::unique_ptr<Message> message);

        void handle(std::unique_ptr<StateBase>& state, std::unique_ptr<Message> message) override;
        void handleStdin(std::unique_ptr<StateBase>& state, std::string& input) override;
    };

}
