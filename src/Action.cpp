#include "Action.hpp"

Action::Action(const std::string name) :
	name_(name),
	status_(ActionStatus::FRESH)
{}

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
