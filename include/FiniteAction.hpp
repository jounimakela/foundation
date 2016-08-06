#pragma once

#include "Action.hpp"

class FiniteAction : public Action
{
public:
	FiniteAction(const std::string name, float duration);
	~FiniteAction() {};

	void step(float delta);

protected:
	float duration_;
	float time_elapsed_;
};
