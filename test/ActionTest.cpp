#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Action.hpp"
#include "FiniteAction.hpp"

class TestAction : public FiniteAction
{
public:
	TestAction(float duration) :
		FiniteAction("TestAction", duration)
	{}
	~TestAction() {}

	void update()
	{}
};

TEST_CASE("Construction", "[action][construction]")
{
	TestAction test(10.f);

	REQUIRE(test.name() == "TestAction");
	REQUIRE(test.status() == ActionStatus::FRESH);
}
