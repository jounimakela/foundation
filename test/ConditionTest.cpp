#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Condition.hpp"
#include "Node.hpp"

class SuccessCondition : public Condition
{
public:
	TestCondition(Node *node) :
		Condition(node) {}

	/* TODO: value_ == actual */
	void rules()
	{
		// I like this style the best
		require<int>("hundred").toEqual(100);
		expect<int>("hundred").toNotEqual(100);

		expect<int>("hundred").toEqual(100);
		expect<int>("hundred").toNot(STRICTLY).equal(101);

		expect<int>("hundred").beGreater(100);
		expect<int>("hundred").notTo().beGreater(100);

		expect<int>("hundred").beGreaterOrEqual(101);
		expect<int>("hundred").notTo().beGreaterOrEqual(99);

		expect<int>("Key").beLess(T expected),
		expect<int>("Key").notTo().beLess(T expected),

		expect<int>("Key").beLessOrEqual(T expected),
		expect<int>("Key").notTo().beLessOrEqual(T expected),

		expect<int>("Key").beBetween(T minimum, T maximum),
		expect<int>("Key").notTo().beBetween(T minimum, T maximum),

		expect<int>("Key").match(std::string expression),
		expect<int>("Key").notTo().match(std::string expression),

		expect<int>("Key").beWithin(float delta, T expected),
		expect<int>("Key").notTo().beWithin(10.f, 100),

		expect<int>("Key").startsWith(std::string expected),
		expect<int>("Key").notTo().startsWith(std::string expected),

		expect<int>("Key").endsWith(std::string expected),
		expect<int>("Key").notTo().endsWith(std::string expected),
	}
};

TEST_CASE("Construction", "[condition][construction]")
{
	Node node;
	node.properties["Key"] = 100;

	TestCondition c(&node);
	REQUIRE(c.check());
	REQUIRE(c.score() == 100);
}
