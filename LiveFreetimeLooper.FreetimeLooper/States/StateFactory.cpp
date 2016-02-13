#include "StateFactory.hpp"
#include <stdexcept>

namespace LiveFreetimeLooper
{
    StateFactory::StateFactory(IMessageDispatcher& messageDispatcher, 
        ILoopTracker& loopTracker, IEventLogger& logger, IAsyncTimerFactory& asyncTimerFactory) :
        _messageDispatcher(messageDispatcher),
        _loopTracker(loopTracker),
        _logger(logger),
        _asyncTimerFactory(asyncTimerFactory)
    {
    }

    std::unique_ptr<CreatedState> GetCreatedState()
    {
        throw std::runtime_error("not implemented");
    }

    std::unique_ptr<InitialLoopWaitingState> GetInitialLoopWaitingState()
    {
        throw std::runtime_error("not implemented");
    }

    std::unique_ptr<InitialLoopState> GetInitialLoopState()
    {
        throw std::runtime_error("not implemented");
    }

    std::unique_ptr<RunningState> GetRunningState()
    {
        throw std::runtime_error("not implemented");
    }
}