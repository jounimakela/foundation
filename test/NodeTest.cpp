#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Node.hpp"

#include <algorithm>

// TODO: = 1, = 2, =3 .. does it work without sayin em numbers?
enum {
	PARENT = 1,
	FIRST_CHILD = 2,
	SECOND_CHILD = 3
};

enum {
	GROUP_ONE = 1,
	GROUP_TWO = 2
};

TEST_CASE("Construction", "[node][construction]")
{
	SECTION("Empty constructor")
	{
		Node node;

		REQUIRE(node.getId()  == Node::DEFAULT_IDENTIFIER);
		REQUIRE(node.parent() == nullptr);
		REQUIRE(node.root()   == nullptr);
	}

	SECTION("Constructor with identifier")
	{
		Node node(PARENT);

		REQUIRE(node.getId()  == PARENT);
		REQUIRE(node.parent() == nullptr);
		REQUIRE(node.root()   == nullptr);
	}

	SECTION("Constructor with parent")
	{
		Node parent;
		Node node(&parent);

		REQUIRE(node.parent() == &parent);
		REQUIRE(node.root()   == &parent);
	}

	SECTION("Constructor with identifier and parent")
	{
		Node parent;
		Node node(FIRST_CHILD, &parent);

		REQUIRE(node.getId()  == FIRST_CHILD);
		REQUIRE(node.parent() == &parent);
		REQUIRE(node.root()   == &parent);
	}
}

TEST_CASE("Manipulation", "[node][manipulation]")
{
	Node parent(PARENT);
	Node first(FIRST_CHILD);
	Node second(SECOND_CHILD);

	SECTION(".append()")
	{
		parent.append(&first);

		REQUIRE(parent.hasChild(&first));
		REQUIRE(parent.childrenCount() == 1);
	}

	SECTION(".removeChild(*Node)")
	{
		parent.append(&first);
		parent.removeChild(&first);

		REQUIRE_FALSE(parent.hasChild(&first));
		REQUIRE(parent.childrenCount() == 0);
	}

	SECTION(".removeChild(int identifier)")
	{
		parent.append(&first);
		parent.removeChild(FIRST_CHILD);

		REQUIRE_FALSE(parent.hasChild(&first));
		REQUIRE(parent.childrenCount() == 0);
	}

	SECTION(".removeAllChildren()")
	{
		parent.append(&first);
		parent.append(&second);
		parent.removeAllChildren();

		REQUIRE(parent.childrenCount() == 0);
	}

	SECTION(".attach()")
	{
		first.attach(&parent);

		REQUIRE(first.parent() == &parent);
		REQUIRE(parent.hasChild(&first));
	}

	SECTION(".detach()")
	{
		first.attach(&parent);
		first.detach();

		REQUIRE(first.parent() == nullptr);
		REQUIRE_FALSE(parent.hasChild(&first));
	}

	SECTION(".addGroup(int group)")
	{
		parent.addGroup(GROUP_ONE);

		REQUIRE(parent.hasGroup(GROUP_ONE));
	}

	SECTION(".addGroup(std::vector<int> groups)")
	{
		std::vector<int> groups { GROUP_TWO };
		parent.addGroup(groups);

		REQUIRE(parent.hasGroup(GROUP_TWO));
	}

	SECTION(".removeFromGroup(int group)")
	{
		parent.removeFromGroup(GROUP_ONE);

		REQUIRE_FALSE(parent.hasGroup(GROUP_ONE));
	}

	SECTION(".removeAllGroups()")
	{
		parent.addGroup(GROUP_ONE);
		parent.removeAllGroups();

		REQUIRE(parent.groups().empty());
	}
}

TEST_CASE("Tree traversal", "[node][traversing]")
{
	Node parent(PARENT);
	Node first(FIRST_CHILD);
	Node second(SECOND_CHILD);
	Node grand_child;

	parent.append(&first);
	parent.append(&second);
	second.append(&grand_child);

	SECTION(".children()")
	{
		auto children = parent.children();

		REQUIRE_FALSE(children.empty());
	}

	SECTION(".siblings()")
	{
		auto siblings = first.siblings();

		REQUIRE_FALSE(siblings.empty());
	}

	SECTION(".root()")
	{
		REQUIRE(grand_child.root() == &parent);
	}

	SECTION(".parent()")
	{
		REQUIRE(first.parent() == &parent);
	}

	SECTION(".parents()")
	{
		auto parents = grand_child.parents();

		REQUIRE(parents.size() == 2);
	//	REQUIRE(std::find(parents.begin(),
	//			  parents.end(),
	//			  parent) != parents.end());
	}
}

TEST_CASE("Filtering", "[node][filtering]")
{
	Node parent(PARENT);
	Node first(FIRST_CHILD);
	Node second(SECOND_CHILD);
	Node grand_child;

	first.addGroup(GROUP_ONE);
	second.addGroup(GROUP_TWO);

	parent.append(&first);
	parent.append(&second);
	second.append(&grand_child);

	SECTION(".getChildById(int identifier)")
	{
		REQUIRE(parent.getChildById(SECOND_CHILD) == &second);
	}

	SECTION(".getChildrenByGroup(int group)")
	{
	//	REQUIRE(parent.getChildrenByGroup(GROUP_TWO) == &second);
	}

	SECTION(".hasChild(Node *child)")
	{
		REQUIRE(parent.hasChild(&first));
	}

	SECTION(".hasChild(int child_identifier)")
	{
		REQUIRE(parent.hasChild(FIRST_CHILD));
	}

	SECTION(".getSiblingById(int identifier)")
	{
		REQUIRE(first.getSiblingById(SECOND_CHILD));
	}

	SECTION(".getSiblingsByGroup(int group)")
	{
		//TODO: REQUIRE(first.getSiblingsByGroup(GROUP_TWO));
	}

	SECTION(".parent(int identifier)")
	{
		Node* found = grand_child.parent(PARENT);

		REQUIRE(found == &parent);
	}
}

TEST_CASE("Enumeration", "[node][enumeration]")
{
	Node parent, first, second, third;

	parent.append(&first);
	parent.append(&second);
	parent.append(&third);

	SECTION(".siblingCount()")
	{
		std::size_t count = first.siblingCount();
		REQUIRE(count == 2);
	}
}

SCENARIO("Nodes can attach to a parent", "[node][manipulation]")
{
	GIVEN("Parent and a node")
	{
		WHEN("Node attaches to a parent")
		{
			THEN("Parent knows about the new child")
			{
			}

			THEN("Child knows about the new parent")
			{
			}

			THEN("Children know about the new root")
			{
			}
		}

		WHEN("Child detaches from its parent")
		{
			THEN("Parent knows the child left")
			{
			}

			THEN("Child doesnt have parents anymore")
			{
			}

			THEN("Children know about the new root")
			{
			}
		}
	}
}

SCENARIO("Nodes can add a new child", "[node][manipulation]")
{
	GIVEN("Parent and a node")
	{
		WHEN("Parent adds a new child")
		{
			THEN("Parent knows about the new child")
			{
			}

			THEN("Child knows about the new parent")
			{
			}

			THEN("Children know about the new root")
			{
			}
		}

		WHEN("Parent removes a child")
		{
			THEN("Parent knows the child left")
			{
			}

			THEN("Child doesnt have parents anymore")
			{
			}

			THEN("Children know about the new root")
			{
			}
		}
	}
}
