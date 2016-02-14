#pragma once
#include <memory>
#include <string>

#include "StateBase.hpp"
#include "../Utilities/Stopwatch.hpp"
#include "../Messaging/Message.hpp"

namespace LiveFreetimeLooper
{
    // Waiting for and timing completion of initial loop
    class InitialLoopState final : public StateBase
    {
    private:
        Stopwatch _stopWatch;
        StateResources& _resources;
        Message _loopStartingMessage;
    public:
        InitialLoopState(StateResources& resources, Message& message);

        void handle(std::unique_ptr<StateBase>& state, std::unique_ptr<Message> message) override;
        void handleStdin(std::unique_ptr<StateBase>& state, const std::string& input) override;
    };

}