#include "RunningState.h"


namespace AbletonProject
{

    RunningState::RunningState(std::chrono::milliseconds timespan, MessageDispatcher* messageDispatcher)
        : _asyncTimer(timespan, std::bind(&RunningState::_dequeueAndSendAll, this)),
          _queue(),
          _messageDispatcher(messageDispatcher)
    {
        _asyncTimer.start();
    }

    RunningState::~RunningState()
    {
        _asyncTimer.stop();
    }

    void RunningState::_dequeueAndSendAll()
    {
        std::string message;
        while (_queue.tryDequeue(message))
        {
            _messageDispatcher->sendMessage(message);
        }
    }

    void RunningState::handle(std::unique_ptr<StateBase>& state, std::string message)
    {
        _queue.enqueue(message);
    }


}
