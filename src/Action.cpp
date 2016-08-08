#include "Action.hpp"

Action::Action(const std::string& name) :
	Node(),
	name_(name),
	status_(ActionStatus::FRESH),
	target_(nullptr)
{
}

void Action::execute(Node *target)
{
	target_ = target;
	status_ = ActionStatus::RUNNING;
}

void Action::fail()
{
	status_ = ActionStatus::FAILED;
}

void Action::cancel()
{
	status_ = ActionStatus::CANCELLED;
}

void Action::success()
{
	status_ = ActionStatus::SUCCEEDED;
}

bool Action::isDone() const
{
	if (    status_ != ActionStatus::FRESH ||
		status_ != ActionStatus::RUNNING) {
		return true;
	}

	return false;
}
