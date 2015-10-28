#include <string>
#include <iostream>
#include "MessageDispatcher.h"
#include "Message.h"
#include "Logging/EventLogger.h"
#include "Logging/MessageDispatchedEvent.h"

namespace LiveFreetimeLooper
{

    MessageDispatcher::MessageDispatcher(RtMidiOut& mOut, EventLogger& logger)
        : _midiOut(mOut),
        _logger(logger)
    {
    }

    void MessageDispatcher::sendMidiMessage(Message* message)
    {
        _logger.log(std::make_unique<MessageDispatchedEvent>(*message, std::string("MessageDispatcher")));

        _midiOut.sendMessage(&(message->payload));
    }

}
