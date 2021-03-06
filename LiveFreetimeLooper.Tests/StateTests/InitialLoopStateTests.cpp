#include "../Catch/catch.hpp"

#include <cstdint>
#include <memory>

#include "../Mocks/MockEventLogger.hpp"
#include "../Mocks/MockMessageDispatcher.hpp"
#include "../Mocks/MockLoopTracker.hpp"
#include "../Mocks/MockAsyncTimerFactory.hpp"

#include "../../LiveFreetimeLooper.Core/Messaging/StartMessage.hpp"
#include "../../LiveFreetimeLooper.Core/States/StateBase.hpp"
#include "../../LiveFreetimeLooper.Core/States/CreatedState.hpp"
#include "../../LiveFreetimeLooper.Core/States/InitialLoopState.hpp"
#include "../../LiveFreetimeLooper.Core/States/RunningState.hpp"

using namespace LiveFreetimeLooper;

TEST_CASE("InitialLoopState")
{
    MockEventLogger loggerMock;
    MockMessageDispatcher dispatcherMock;
    MockLoopTracker loopTrackerMock;

    std::vector<unsigned char> startingCommandContent = { 7, 1 };
    std::vector<unsigned char> stopCommandContent = { 8, 1 };
    std::vector<unsigned char> otherCommandContent = { 3, 5 };
    Command startingCommand(startingCommandContent);
    Command stopCommand(stopCommandContent);
    Command otherCommand(otherCommandContent);

    MockAsyncTimerFactory asyncTimerFactory;

    StateResources resources(dispatcherMock, loopTrackerMock, loggerMock, asyncTimerFactory);
    StartMessage startingMessage(startingCommand);
    std::unique_ptr<StateBase> state = std::make_unique<InitialLoopState>(
        resources, startingMessage);

    SECTION(
        "Start Message with the same command as the beginning message "
        "is dispatched, sent to looptracker and changes state to RunningState")
    {
        state->handle(state, std::make_unique<StartMessage>(startingCommand));

        REQUIRE(dispatcherMock.getDispatchedCommands().size() == 1);
        REQUIRE(dispatcherMock.getDispatchedCommands().back().content == startingCommand.content);
        REQUIRE(loopTrackerMock.getCommandsStarted().size() == 1);
        REQUIRE(loopTrackerMock.getCommandsStarted().back().content == startingCommand.content);

        REQUIRE(dynamic_cast<RunningState*>(state.get()));
    }

    SECTION(
        "Start Message with the different command as the beginning message "
        "is not dipatched, not sent to looptracker and the state does not change")
    {
        state->handle(state, std::make_unique<StartMessage>(otherCommand));
        REQUIRE(dispatcherMock.getDispatchedCommands().size() == 0);
        REQUIRE(loopTrackerMock.getCommandsStarted().size() == 0);
        REQUIRE(dynamic_cast<InitialLoopState*>(state.get()));
    }


    SECTION("When Stdin is supplied it clears looptracker and returns state to CreatedState")
    {
        state->handleStdin(state, std::string("any string value"));
        REQUIRE(loopTrackerMock.isCleared());
        REQUIRE(dynamic_cast<CreatedState*>(state.get()));
    }

    // todo, I don't think this will be the case for long. 
    // Once we have the concept of an extant stopped loop we need to rethink
    SECTION(
        "Stop message that matches the beginning message "
        "is dispatched, the START command is sent to looptracker and changes state to "
        "RunningState ie its treated the same as a start command")
    {
        state->handle(state, std::make_unique<StopMessage>(stopCommand, startingCommand));
        REQUIRE(loopTrackerMock.getCommandsStarted().size() == 1);
        REQUIRE(loopTrackerMock.getCommandsStarted().back().content == startingCommand.content);
        REQUIRE(dispatcherMock.getDispatchedCommands().size() == 1);
        REQUIRE(dispatcherMock.getDispatchedCommands().back().content == stopCommand.content);
        REQUIRE(dynamic_cast<RunningState*>(state.get()));
    }

    SECTION(
        "Stop message that doesn't match the beginning message is immediately "
        "dispatched but ignored: does not clear the looptracker, is not sent "
        "to the loop tracker and does not change the state")
    {
        state->handle(state, std::make_unique<StopMessage>(stopCommand, otherCommand));
        REQUIRE(loopTrackerMock.getCommandsStarted().size() == 0);
        REQUIRE(dispatcherMock.getDispatchedCommands().size() == 1);
        REQUIRE(dispatcherMock.getDispatchedCommands().back().content == stopCommand.content);
        REQUIRE(dynamic_cast<InitialLoopState*>(state.get()));
    }
}