#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Node.hpp"

#include <algorithm>

enum {
	PARENT,
	FIRST_CHILD,
	SECOND_CHILD
};

enum {
	GROUP_ONE,
	GROUP_TWO
};

TEST_CASE("Construction", "[node][construction]")
{
	SECTION("Empty constructor")
	{
		Node node;

		REQUIRE(node.getId()  == Node::DEFAULT_IDENTIFIER);
		REQUIRE(node.parent() == nullptr);
	}

	SECTION("Constructor with identifier")
	{
		Node node(PARENT);

		REQUIRE(node.getId()  == PARENT);
		REQUIRE(node.parent() == nullptr);
	}

	SECTION("Constructor with parent")
	{
		Node parent;
		Node node(&parent);

		REQUIRE(node.parent() == &parent);
		REQUIRE(parent.hasChild(&node));
	}

	SECTION("Constructor with identifier and parent")
	{
		Node parent;
		Node node(FIRST_CHILD, &parent);

		REQUIRE(node.getId()  == FIRST_CHILD);
		REQUIRE(node.parent() == &parent);
		REQUIRE(parent.hasChild(&node));
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

	SECTION(".parent()")
	{
		REQUIRE(first.parent() == &parent);
	}

	SECTION(".parents()")
	{
		auto parents = grand_child.parents();

		REQUIRE(parents.size() == 2);

		REQUIRE(std::find(parents.begin(),
				parents.end(),
				&parent) != parents.end());
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
		auto children = parent.getChildrenByGroup(GROUP_TWO);

		REQUIRE((std::find(children.begin(),
				  children.end(),
				  &second) != children.end()));
	}

	SECTION(".hasChild(Node *child)")
	{
		REQUIRE(parent.hasChild(&first));
	}

	SECTION(".hasChild(int child_identifier)")
	{
		REQUIRE(parent.hasChild(FIRST_CHILD));
	}

	SECTION(".root()")
	{
		REQUIRE(grand_child.root() == &parent);
	}

	SECTION(".getSiblingById(int identifier)")
	{
		REQUIRE(first.getSiblingById(SECOND_CHILD));
	}

	SECTION(".getSiblingsByGroup(int group)")
	{
		auto siblings = first.getSiblingsByGroup(GROUP_TWO);

		REQUIRE((std::find(siblings.begin(),
				  siblings.end(),
				  &second) != siblings.end()));
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
		Node parent(PARENT);
		Node child(FIRST_CHILD);
		Node grand_child(SECOND_CHILD, &child);

		WHEN("Node attaches to a parent")
		{
			child.attach(&parent);

			THEN("Parent knows about the new child")
			{
				REQUIRE(parent.hasChild(&child));
				REQUIRE(parent.hasChild(FIRST_CHILD));
			}

			THEN("Child knows about the new parent")
			{
				REQUIRE(child.parent() == &parent);
			}
		}

		WHEN("Child detaches from its parent")
		{
			child.attach(&parent);
			child.detach();

			THEN("Parent knows the child left")
			{
				REQUIRE_FALSE(parent.hasChild(&child));
				REQUIRE_FALSE(parent.hasChild(FIRST_CHILD));
			}

			THEN("Child doesnt have parents anymore")
			{
				REQUIRE(child.parent() == nullptr);
			}
		}
	}
}

SCENARIO("Nodes can add a new child", "[node][manipulation]")
{
	GIVEN("Parent and a node")
	{
		Node parent(PARENT);
		Node child(FIRST_CHILD);
		Node grand_child(SECOND_CHILD, &child);

		WHEN("Parent adds a new child")
		{
			parent.append(&child);

			THEN("Parent knows about the new child")
			{
				REQUIRE(parent.hasChild(&child));
				REQUIRE(parent.hasChild(FIRST_CHILD));
			}

			THEN("Child knows about the new parent")
			{
				REQUIRE(child.parent() == &parent);
			}
		}

		WHEN("Parent removes a child")
		{
			parent.append(&child);
			parent.removeChild(&child);

			THEN("Parent knows the child left")
			{
				REQUIRE_FALSE(parent.hasChild(&child));
				REQUIRE_FALSE(parent.hasChild(FIRST_CHILD));
			}

			THEN("Child doesnt have parents anymore")
			{
				REQUIRE(child.parent() == nullptr);
			}
		}
	}
}

/*
SCENARIO("Node properties can be changed")
{
	GIVEN("A fresh node")
	{
		Node node;

		WHEN("Single property is assigned")
		{
			node.properties().add<int>("Key", 100);

			THEN("It can be fetched")
			{
				REQUIRE(node.properties().contains("Key"));
			}

			THEN("It can be changed")
			{
				node.properties().set<int>("Key", 200);
				int key = node.properties().get<int>("Key");

				REQUIRE(key == 200);
			}
		}

		WHEN("Properties are assigned")
		{
			HashMap new_properties;
			new_properties.add<int>("Integer", 100);
			new_properties.add<float>("Float", 12);

			node.setProperties(new_properties);

			THEN("They are copied over")
			{
				REQUIRE(node.properties().contains("Integer"));
				REQUIRE(node.properties().contains("Float"));
			}
		}
	}
}
*/
