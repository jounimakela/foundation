#pragma once

#include "FiniteAction.hpp"

class RepeatingAction : public FiniteAction
{
public:
	RepeatingAction(const std::string name, float duration);
	~RepeatingAction() {};

	void step(float delta);
	int repeatCount() { return count_repeated_; };

protected:
	int count_repeated_;
};
