#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Node.hpp"

#include <algorithm> // std::find

const int TEST_IDENTIFIER = 1;

TEST_CASE("Node can be constructed", "[node]")
{
	Node node;
	REQUIRE(node.getId() == Node::DEFAULT_IDENTIFIER);

	Node node_with_id(TEST_IDENTIFIER);
	REQUIRE(node_with_id.getId() == TEST_IDENTIFIER);

	Node parent;
	Node node_with_parent(&parent);
	REQUIRE(node_with_parent.parent() == &parent);

	Node node_with_parent_and_id(&parent, TEST_IDENTIFIER);
	REQUIRE(node_with_parent_and_id.parent() == &parent);
	REQUIRE(node_with_parent_and_id.getId() == TEST_IDENTIFIER);
}

TEST_CASE("Node can have children", "[node, children]")
{
	enum {
		PARENT = 1,
		FIRST_CHILD = 2,
		SECOND_CHILD = 3,
		THIRD_CHILD = 4
	};

	Node parent(PARENT);
	Node first(FIRST_CHILD);
	Node second(SECOND_CHILD);
	Node third(THIRD_CHILD);

	parent.addChild(&first);
	REQUIRE(parent.childrenCount() == 1);
	REQUIRE(first.parent() == &parent);
	REQUIRE(first.root() == &parent);

	std::vector<Node*> children = parent.children();
	REQUIRE(parent.hasChild(&first));

	REQUIRE(std::find(children.begin(),
			  children.end(),
			  &first) != children.end()
	);

	parent.addChild(&second);

	REQUIRE(parent.getChildById(SECOND_CHILD) == &second);
	REQUIRE(parent.hasChild(&second));
	REQUIRE(second.parent() == &parent);
	REQUIRE(second.root() == &parent);

	third.attach(&parent);
	REQUIRE(third.parent() == &parent);
	REQUIRE(third.root() == &parent);

	REQUIRE(parent.getChildById(THIRD_CHILD) == &third);
	REQUIRE(parent.childrenCount() == 3);

	third.detach();

	REQUIRE(third.parent() == nullptr);
	REQUIRE(third.root() == nullptr);
	REQUIRE(parent.hasChild(&third) == false);
	REQUIRE(parent.childrenCount() == 2);
}
