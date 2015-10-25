#pragma once

#include <vector>
#include <iostream>

namespace AbletonProject
{
    class Message final
    {
    public:
        Message() {}
        Message(std::vector<unsigned char> payload) :
            payload(payload)
        {
        }

        std::vector<unsigned char> payload;

        bool Matches(Message const& other) const
        {
            return other.payload == payload;
        }
        
    };
}
