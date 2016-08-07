#pragma once

#include <string>

#include "Node.hpp"

enum ActionStatus {
	FRESH,
	RUNNING,
	SUCCEEDED,
	FAILED,
	CANCELLED
};

class Action : public Node
{
public:
	Action(const std::string name);
	~Action() {};

	std::string name() const { return name_; }
	void execute(Node *target);
	virtual void update() = 0;
	virtual void step(float delta) = 0;
	ActionStatus status() const { return status_; };

	void fail();
	void cancel();
	void success();

	bool isDone() const;

protected:
	const std::string name_;
	ActionStatus status_;
	Node *target_;
};
