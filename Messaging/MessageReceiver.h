#pragma once
#include <memory>
#include <mutex>
#include <string>

#include "States/StateBase.h"
#include "Message.h"

class MessageDispatcher;
class EventLogger;
class LoopTracker;

namespace AbletonProject
{
    class MessageReceiver final
    {
    private:
        std::mutex _mutex;
        StateResources _resources;
        std::unique_ptr<StateBase> _currentState;

        bool isMidiCommand(Message* message);
    public:
        MessageReceiver(
            MessageDispatcher& messageDispatcher, LoopTracker& loopTracker, EventLogger& logger);

        void receiveRawMidiMessage(double deltatime, std::vector<unsigned char> *rawMessage);
        void receiveMidiMessage(std::unique_ptr<Message> message);
        void receiveStdin(std::string& input);
    };
}
