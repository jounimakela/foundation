#pragma once

#include "Node.hpp"

enum class Event {
	TEST
};

class EventListener
{
public:
	EventListener(Node *node) : node_(node) {}

	void broadcast(const Event& event)
	{
	}

	bool on(const Event&& event, Action&& side_effect)
	{
		events_[std::move(event)].push_back(
			std::forward<Action>(side_effect)
		);
	}

protected:
	Node *node_;
	std::map<Event, std::vector<std::function<void()>>> events_;
};
