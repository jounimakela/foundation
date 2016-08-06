#pragma once

#include "Action.hpp"

class FiniteAction : public Action
{
public:
	FiniteAction(const std::string name, float duration);
	~FiniteAction() {};

	void step(float delta);
	float timeElapsed() const { return time_elapsed_; };

protected:
	float duration_;
	float time_elapsed_;
};
