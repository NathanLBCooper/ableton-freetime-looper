#include "InitialLoopWaitingState.hpp"
#include "InitialLoopState.hpp"
#include "CreatedState.hpp"
#include "../Logging/StateChangedEvent.hpp"

namespace LiveFreetimeLooper
{
    InitialLoopWaitingState::InitialLoopWaitingState(StateResources& resources)
        : _resources(resources)
    {
    }

    void InitialLoopWaitingState::handle(std::unique_ptr<StateBase>& state, std::unique_ptr<StartMessage> message)
    {
        _resources.messageDispatcher.sendMidiMessage(message.get());
        _resources.loopTracker.commandReceived(message->command);
        _resources.logger.log(std::make_unique<StateChangedEvent>(
            std::string("Start Message Received. Progress: InitialLoopWaiting -> InitialLoop"),
            std::string("InitialLoopWaitingState")));
        state = std::make_unique<InitialLoopState>(_resources, *message.get());
    }

    void InitialLoopWaitingState::handle(std::unique_ptr<StateBase>& state, std::unique_ptr<StopMessage> message)
    {
        // not implemented
    }

    void InitialLoopWaitingState::handleStdin(std::unique_ptr<StateBase>& state, const std::string& input)
    {
        _resources.loopTracker.clear();
        _resources.logger.log(std::make_unique<StateChangedEvent>(
            std::string("StdIn. Reset: InitialLoopWaiting -> Created"),
            std::string("InitialLoopWaitingState")));
        state = std::move(std::make_unique<CreatedState>(_resources));
    }

}