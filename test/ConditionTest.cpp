#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Condition.hpp"
#include "Node.hpp"

class TestCondition : public Condition
{
public:
	TestCondition(Node *node) :
		Condition(node) {}

	bool checkStrict()
	{
		return expect<int>("Key").equal(100);
		return expect<int>("Key").notTo().equal(30);
	}

	bool checkScore() { return false; }
};

TEST_CASE("Construction", "[condition][construction]")
{
	Node node;
	node.properties["Key"] = 100;

	TestCondition c(&node);
	REQUIRE(c.checkStrict() == true);
}
