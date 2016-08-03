#include "Node.hpp"

void Node::addChild(Node *child)
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

std::size_t Node::childrenCount() const
{
	return children_.size();
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

void Node::removeChild(Node* child)
{
	children_.erase(std::remove(
				children_.begin(),
				children_.end(),
				child),
			children_.end());
}

bool Node::hasChild(Node *child)
{
	return (std::find(children_.begin(),
			  children_.end(),
			  child) != children_.end());
}

void Node::detach()
{
	parent_->removeChild(this);
	parent_ = nullptr;
	root_	= nullptr;
}

void Node::attach(Node *parent)
{
	if (!parent->hasChild(this)) {
		parent->addChild(this);
	}

	parent_ = parent;
	root_ = parent_->root();

	if (!root_) {
		root_ = parent_;
	}
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

void Node::removeFromParent()
{
	// TODO: Cleanup! Smartpointers?
	parent_ = nullptr;
}
*/
