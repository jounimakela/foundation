#include "InstantAction.hpp"

InstantAction::InstantAction(const std::string& name) :
	Action(name)
{
}

void InstantAction::step(float delta)
{
	if (status() != ActionStatus::RUNNING) {
		return;
	}

	update();
	success();
}
