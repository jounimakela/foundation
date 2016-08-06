#include "RepeatingAction.hpp"

RepeatingAction::RepeatingAction(const std::string name, float duration) :
	FiniteAction(name, duration),
	count_repeated_(0)
{}

void RepeatingAction::step(float delta)
{
	if (status() != ActionStatus::RUNNING)
	{
		return;
	}

	time_elapsed_ += delta;

	if (time_elapsed_ >= duration_) {
		time_elapsed_ = time_elapsed_ - duration_;
		count_repeated_++;
	}

	update();
}
