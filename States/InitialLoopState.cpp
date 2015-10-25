#include "InitialLoopState.h"

namespace AbletonProject
{

    InitialLoopState::InitialLoopState(StateResources& resources, std::unique_ptr<Message> message)
        : _stopWatch(),
         _resources(resources),
         _loopStartingMessage(std::move(message))
    {
        _stopWatch.start();
    }

    void InitialLoopState::handle(std::unique_ptr<StateBase>& state, std::unique_ptr<Message> message)
    {
        _resources.messageDispatcher.sendMidiMessage(message.get());

        if (_loopStartingMessage == message)
        {
            _stopWatch.stop();
            state = std::move(std::make_unique<RunningState>(
                _resources, _stopWatch.getElapsedMilliseconds()));
            _resources.logger.log(std::make_unique<StateChangedEvent>(
                std::string("Loop ending message detected, moving from InitialLoop to Running"),
                std::string("InitialLoopState")));
        }
    }

    void InitialLoopState::handleStdin(std::unique_ptr<StateBase>& state, std::string& input)
    {
        state = std::move(std::make_unique<CreatedState>(_resources));
        _resources.logger.log(std::make_unique<StateChangedEvent>(
            std::string("StdIn detected, reverting from InitialLoop to Created"),
            std::string("InitialLoopState")));
    }
}
