#include "..\Catch\catch.h"

#include <cstdint>
#include <memory>

#include "..\Mocks\MockEventLogger.h"
#include "..\Mocks\MockMessageDispatcher.h"
#include "..\Mocks\MockAsyncTimerFactory.h"

#include "..\..\LiveFreetimeLooper\Messaging\Message.h"
#include "..\..\LiveFreetimeLooper\Messaging\LoopTracker.h"
#include "..\..\LiveFreetimeLooper\States\StateBase.h"
#include "..\..\LiveFreetimeLooper\States\CreatedState.h"
#include "..\..\LiveFreetimeLooper\States\InitialLoopWaitingState.h"

using namespace LiveFreetimeLooper;

TEST_CASE("Created State")
{
    MockEventLogger loggerMock;
    MockMessageDispatcher dispatcherMock;

    LoopTracker loopTracker;
    MockAsyncTimerFactory asyncTimerFactory;

    StateResources resources(dispatcherMock, loopTracker, loggerMock, asyncTimerFactory);
    
    std::unique_ptr<StateBase> state = std::make_unique<CreatedState>(resources);

    SECTION("Created State acts as a transparent relay before StdIn supplied")
    {
        for (unsigned char i = 1; i < 21; i++)
        {
            std::vector<unsigned char> messagePayload = { 0, i };
            state->handle(state, std::make_unique<Message>(messagePayload));
            REQUIRE(dispatcherMock.getMessages().size() == i);
            REQUIRE(dispatcherMock.getMessages().back() == messagePayload);
        }
    }

    SECTION("Created State returns InitialLoopWaitingState when StdIn supplied")
    {
        state->handleStdin(state, std::string("any string value"));
        REQUIRE(dynamic_cast<InitialLoopWaitingState*>(state.get()));
    }
}