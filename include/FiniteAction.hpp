#pragma once

#include "Action.hpp"

class FiniteAction : public Action
{
public:
	FiniteAction(const std::string& name, float duration);
	~FiniteAction()
        {
        }

	void step(float delta);
	float timeElapsed() const
	{
		return time_elapsed_;
	}

        void setDuration(float duration)
        {
                duration_ = duration;
        }

        float getDuration() const
        {
                return duration_;
        }

        float progress() const
        {
                return time_elapsed_ / duration_ * 100;
        }

protected:
	float duration_;
	float time_elapsed_;
};
