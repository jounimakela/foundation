#include "FiniteAction.hpp"

FiniteAction::FiniteAction(const std::string name, float duration) :
	Action(name),
	duration_(duration),
	time_elapsed_(0)
{}

void FiniteAction::step(float delta)
{
	time_elapsed_ += delta;

	if (time_elapsed_ >= duration_) {
		success();
		return;
	}

	update();
}
