#pragma once

#include <memory>

namespace LiveFreetimeLooper
{
    class CreatedState;
    class InitialLoopWaitingState;
    class InitialLoopState;
    class RunningState;
    class IMessageDispatcher;
    class ILoopTracker;
    class IEventLogger;
    class IAsyncTimerFactory;

    class StateFactory final
    {
    private:
        IMessageDispatcher& _messageDispatcher;
        ILoopTracker& _loopTracker;
        IEventLogger& _logger;
        IAsyncTimerFactory& _asyncTimerFactory;
    public:
        StateFactory(IMessageDispatcher& messageDispatcher, ILoopTracker& loopTracker,
            IEventLogger& logger, IAsyncTimerFactory& asyncTimerFactory);
        std::unique_ptr<CreatedState> GetCreatedState();
        std::unique_ptr<InitialLoopWaitingState> GetInitialLoopWaitingState();
        std::unique_ptr<InitialLoopState> GetInitialLoopState();
        std::unique_ptr<RunningState> GetRunningState();
    };
}