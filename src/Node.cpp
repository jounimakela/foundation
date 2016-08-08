#include "Node.hpp"

Node::Node() :
	identifier_(DEFAULT_IDENTIFIER)
{
	parent_ = nullptr;
}

Node::Node(int identifier) :
	identifier_(identifier)
{
	parent_ = nullptr;
}

Node::Node(Node *parent) :
	identifier_(DEFAULT_IDENTIFIER)
{
	parent_ = nullptr;
	attach(parent);
}

Node::Node(int identifier, Node *parent) :
	identifier_(identifier)
{
	parent_ = nullptr;
	attach(parent);
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

std::vector<Node*> Node::getChildrenByGroup(int group)
{
	std::vector<Node*> children_ = children();
	std::vector<Node*> result;

	for (Node *child : children_) {
		if (child->hasGroup(group)) {
			result.push_back(child);
		}
	}

	return result;
}

bool Node::hasChild(Node *child)
{
	return std::find(children_.begin(),
			 children_.end(),
			 child) != children_.end();
}

bool Node::hasChild(int identifier)
{
	for (auto child : children_) {
		if (child->getId() == identifier) {
			return child;
		}
	}

	return false;
}

std::size_t Node::childrenCount() const
{
	return children_.size();
}

Node* Node::root()
{
	return parents().back();
}

std::vector<Node*> Node::siblings()
{
	std::vector<Node*> siblings = parent()->children();
	siblings.erase(
		std::remove(siblings.begin(), siblings.end(), this),
		siblings.end()
	);

	return siblings;
}

Node* Node::getSiblingById(int identifier)
{
	std::vector<Node*> siblings_ = siblings();

	for (Node *sibling : siblings_) {
		if (sibling->getId() == identifier) {
			return sibling;
		}
	}

	return nullptr;
}

std::vector<Node*> Node::getSiblingsByGroup(int group)
{
	std::vector<Node*> siblings_ = siblings();
	std::vector<Node*> result;

	for (Node *sibling : siblings_) {
		if (sibling->hasGroup(group)) {
			result.push_back(sibling);
		}
	}

	return result;
}

std::size_t Node::siblingCount() const
{
	if (parent() == nullptr) {
		return 0;
	}

	std::size_t count = parent()->children().size();
	count--; // -1 since the current node is one of the children

	return count;
}

Node* Node::parent(int identifier) const
{
	Node *parent = parent_;

	if (parent_ == nullptr) {
		return parent;
	}

	do {
		parent = parent->parent();
	} while (parent != nullptr && parent->getId() != identifier);

	return parent;
}

std::vector<Node*> Node::parents()
{
	std::vector<Node*> parents;

	if (parent_ == nullptr) {
		return parents;
	}

	Node *parent = parent_;

	do {
		parents.push_back(parent);
		parent = parent->parent();
	} while (parent != nullptr);

	return parents;
}

void Node::removeChild(Node* child)
{
	children_.erase(
		std::remove(children_.begin(), children_.end(), child),
		children_.end()
	);

	if (child->parent() == this) {
		child->detach();
	}
}

void Node::removeChild(int identifier)
{
	auto child = getChildById(identifier);

	removeChild(child);
}

void Node::removeAllChildren()
{
	for (auto child : children_) {
		removeChild(child);
	}
}

void Node::attach(Node *parent)
{
	if (!parent->hasChild(this)) {
		parent->append(this);
	}

	parent_ = parent;
}

void Node::detach()
{
	if (parent_->hasChild(this)) {
		parent_->removeChild(this);
	}

	parent_ = nullptr;
}

void Node::addGroup(int group)
{
	groups_.push_back(group);
}

void Node::addGroup(std::vector<int> groups)
{
	groups_.insert(groups_.end(), groups.begin(), groups.end());
}

void Node::removeFromGroup(int group)
{
	groups_.erase(
		std::remove(groups_.begin(), groups_.end(), group),
		groups_.end()
	);
}

void Node::removeAllGroups()
{
	groups_.clear();
}

bool Node::hasGroup(int group)
{
	return std::find(groups_.begin(),
			 groups_.end(),
			 group) != groups_.end();
}

void Node::setProperties(HashMap &properties)
{
	properties_.pairs_.clear();
	properties_.clone(properties);
}
