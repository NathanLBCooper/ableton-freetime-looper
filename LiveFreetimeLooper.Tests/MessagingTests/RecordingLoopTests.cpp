#include "../Catch/catch.hpp"
#include "../../LiveFreetimeLooper.FreetimeLooper/Messaging/Message.hpp"

#include "../../LiveFreetimeLooper.FreetimeLooper/Messaging/RunningLoop.hpp"
#include "../../LiveFreetimeLooper.FreetimeLooper/Messaging/RecordingLoop.hpp"

#include <memory>
#include <cstdint>
using namespace LiveFreetimeLooper;

TEST_CASE("Recording Loop yields a loop of correct interval and message")
{
    std::vector<unsigned char> payload = { 'q' };
    Message message(payload);
    RecordingLoop recordingLoop(std::make_unique<Message>(message));

    for (std::int32_t i = 0; i < 27; i++)
    {
        recordingLoop.incrementInterval();
    }

    auto loop = recordingLoop.moveToRunningLoop();

    REQUIRE(loop.getInterval() == 27);
    REQUIRE(*loop.getControlMessage() == message);
}

TEST_CASE("Recording Loop cannot move to Running Loop with a zero interval")
{
    std::vector<unsigned char> payload = { 'g' };
    Message message(payload);
    RecordingLoop recordingLoop(std::make_unique<Message>(message));
    REQUIRE_THROWS_AS(recordingLoop.moveToRunningLoop(), std::runtime_error);
}