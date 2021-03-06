#pragma once

#include "IMessageDispatcher.hpp"
#include "../RtMidi/RtMidi.hpp"
#include <memory>

namespace LiveFreetimeLooper
{
    class IMessage;
    class IEventLogger;
    class Command;

    class MessageDispatcher final : public IMessageDispatcher
    {
    private:
        RtMidiOut& _midiOut;
        IEventLogger& _logger;
    public:
        explicit MessageDispatcher(RtMidiOut& mOut, IEventLogger& logger);
        void sendNewMidiMessage(Command command) override;
        void sendMidiMessage(IMessage* message) override;
    };
}
