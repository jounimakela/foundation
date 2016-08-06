#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Action.hpp"
#include "FiniteAction.hpp"
#include "InstantAction.hpp"

class FiniteTestAction : public FiniteAction
{
public:
	FiniteTestAction(float duration) :
		FiniteAction("FiniteTestAction", duration)
	{}
	~FiniteTestAction() {}

	void update() {}
};

class InstantTestAction : public InstantAction
{
public:
	InstantTestAction() :
		InstantAction("InstantTestAction")
	{}
	~InstantTestAction() {}

	void update() {}
};

TEST_CASE("Standard Action", "[standard][construction]")
{
	FiniteTestAction test(10.f);

	REQUIRE(test.name() == "FiniteTestAction");
	REQUIRE(test.status() == ActionStatus::FRESH);
}

TEST_CASE("Finite Action", "[finite][construction]")
{
	FiniteTestAction test(10.f);
	Node node;

	SECTION("Time elapses grows each step by delta")
	{
		test.execute(&node);
		test.step(5);

		REQUIRE(test.timeElapsed() == 5);
		REQUIRE(test.status() == ActionStatus::RUNNING);

		test.step(5);

		REQUIRE(test.timeElapsed() == 10);
		REQUIRE(test.status() == ActionStatus::SUCCEEDED);

		test.step(5);

		REQUIRE(test.timeElapsed() == 10);
	}
}

TEST_CASE("Instant Action", "[finite][construction]")
{
	InstantTestAction test;
	Node node;

	SECTION("Instant actions succeed after first step")
	{
		test.execute(&node);
		REQUIRE(test.status() == ActionStatus::RUNNING);

		test.step(5);
		REQUIRE(test.status() == ActionStatus::SUCCEEDED);
	}
}
