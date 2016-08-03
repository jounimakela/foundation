# pragma once

#include <cstddef>
#include <vector>
#include <algorithm> // std::find

class Node
{
public:
	enum {
		DEFAULT_IDENTIFIER = 0
	};

	/**
	 * TODO: We should add the root here as well!
	 * Also move constructor blocks to cpp
	 */
	Node() :
		identifier_(DEFAULT_IDENTIFIER) {
			parent_ = nullptr;
			root_ = nullptr;
		}

	Node(int identifier) :
		identifier_(identifier) {
			parent_ = nullptr;
			root_ = nullptr;
		}

	Node(Node *parent) :
		parent_(parent),
		identifier_(DEFAULT_IDENTIFIER)  {
			root_ = nullptr;
		}

	Node(Node *parent, int identifier) :
		parent_(parent),
		identifier_(identifier) {
			root_ = nullptr;
		}

	~Node() {};

	// Children management
	void addChild(Node *child);
	void addChild(Node *child, std::vector<int> groups);

	std::vector<Node*>& children();
	Node* getChildById(int identifier) const;
	std::vector<Node*>& getChildrenByGroup(int group) const;
	bool hasChild(Node *child);

	std::size_t childrenCount() const;

	Node* root() const { return root_; }

	// Parent management
	Node* parent() const { return parent_; }
	std::vector<Node*>& parents(int parent_identifier = DEFAULT_IDENTIFIER) const;
	void removeChild(Node *child);
	void removeChildByTag(int tag);
	void removeAllChildren();

	void attach(Node *parent);
	void detach();

	// Current node management
	int getId() const { return identifier_; };

	int addGroup(int group);
	int addGroup(std::vector<int> groups);
	void removeFromGroup(int group);
	void removeAllgroups();
	bool hasGroup(int group);

protected:
	std::vector<Node*> children_;
	Node *parent_;
	Node *root_;

	int identifier_;
	std::vector<int> groups_;
};
