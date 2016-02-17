#pragma once

#include <vector>
#include "Command.hpp"

namespace LiveFreetimeLooper
{
    class StartMessage final
    {
    public:
        StartMessage(Command command) :
            command(command), deltatime(0.0)
        {
        }

        StartMessage(std::vector<unsigned char> command) :
            command(command), deltatime(0.0)
        {
        }

        StartMessage(Command command, double deltatime) :
            command(command), deltatime(deltatime)
        {
        }

        Command command;
        double deltatime;

        bool operator==(const StartMessage& other) const
        {
            return other.command == command;
        }
    };
}