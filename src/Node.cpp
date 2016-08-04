#include "Node.hpp"

Node::Node() :
	identifier_(DEFAULT_IDENTIFIER)
{
	parent_ = nullptr;
	root_ = nullptr;
}

Node::Node(int identifier) :
	identifier_(identifier)
{
	parent_ = nullptr;
	root_ = nullptr;
}

Node::Node(Node *parent) :
	parent_(parent),
	identifier_(DEFAULT_IDENTIFIER)
{
	root_ = parent_->root();

	if (!root_) {
		root_ = parent_;
	}
}

Node::Node(int identifier, Node *parent) :
	parent_(parent),
	identifier_(identifier)
{
	root_ = parent_->root();

	if (!root_) {
		root_ = parent_;
	}
}

Node::~Node()
{
}

void Node::append(Node *child)
{
	if (child->parent() != this) {
		children_.push_back(child);
		child->attach(this);
	}

	// TODO: Should we set a flag that children has changed?
}

std::vector<Node*>& Node::children()
{
	return children_;
}


Node* Node::getChildById(int identifier) const
{
	for (auto child : children_) {
		if (child->getId() == identifier) {
			return child;
		}
	}

	return nullptr;
}

std::vector<Node*> getChildrenByGroup(int group)
{
	std::vector<Node*> children;
	return children;
}

bool Node::hasChild(Node *child)
{
	return (std::find(children_.begin(),
			  children_.end(),
			  child) != children_.end());
}

bool Node::hasChild(int identifier)
{
	return false;
}

std::size_t Node::childrenCount() const
{
	return children_.size();
}

std::vector<Node*>& Node::siblings()
{
	std::vector<Node*> siblings;
	return siblings;
}

Node* Node::getSiblingById(int identifier) const
{
	return nullptr;
}

std::vector<Node*> Node::getSiblingsByGroup(int group)
{
	std::vector<Node*> siblings;
	return siblings;
}

std::size_t Node::siblingCount() const
{
	return children_.size();
}

Node* Node::parent(int identifier) const
{
	return nullptr;
}

std::vector<Node*>& Node::parents()
{
	std::vector<Node*> parents;
	return parents;
}

void Node::removeChild(Node* child)
{
	children_.erase(
		std::remove(children_.begin(), children_.end(), child),
		children_.end()
	);
	// TODO: BUG: Removed child does not know it has been removed
}

void Node::removeChild(int identifier)
{
	return;
}

void Node::removeAllChildren()
{
	return;
}

void Node::attach(Node *parent)
{
	if (!parent->hasChild(this)) {
		parent->append(this);
	}

	parent_ = parent;
	root_ = parent_->root();

	if (!root_) {
		root_ = parent_;
	}
}

void Node::detach()
{
	parent_->removeChild(this);
	parent_ = nullptr;
	root_	= nullptr;
}

void Node::addGroup(int group)
{
	return;
}

void Node::addGroup(std::vector<int> groups)
{
	return;
}

void Node::removeFromGroup(int group)
{
	return;
}

void Node::removeAllGroups()
{
	return;
}

bool Node::hasGroup(int group)
{
	return false;
}

/*
sdt::vector<Node*>& Node::parents(int parent_identifier)
{
	std::vector<Node*> parents;

	if (root_ == nullptr) {
		return parents;
	}

	Node *parent = parent_;

	if (parent_identifier != DEFAULT_IDENTIFIER) {
		do {
			parents.push_back(parent);
			parent = parent.parent();
		} while(parent != root_ || parent.getId() == parent_identifier);

	return parents;
	}

	do {
		parents.push_back(parent);
		parent = parent.parent();
	} while(parent != root_);

	return parents;
}
*/
