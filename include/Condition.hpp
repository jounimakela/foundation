#pragma once

#include <string>

#include "Node.hpp"
#include "any.hpp"

class Condition
{
public:
	Condition(Node *node) : node_(node) {};

	virtual bool checkStrict() = 0;
	virtual bool checkScore() = 0;

protected:
	class Matcher
	{
	public:
		Matcher(int value) :
			inverse(false),
			value_(value) {}

		Matcher(Matcher&&) = default;

		Matcher& notTo()
		{
			inverse = true;
			return *this;
		}

	// Value matchers
	/*
		bool toEqual(int expected);
		bool toEqual(bool expected);
		bool toEqual(float expected);
		bool toEqual(std::string expected);

		bool toBeGreater(int expected);
		bool toBeGreater(float expected);

		bool toBeGreaterOrEqual(int expected);
		bool toBeGreaterOrEqual(float expected);

		bool toBeLess(int expected);
		bool toBeLess(float expected);

		bool toBeLessOrEqual(int expected);
		bool toBeLessOrEqual(float expected);

		bool toBeBetween(int minimum, int maximum);
		bool toBeBetween(float minimum, float maximum);

		bool toMatch(std::string expression);

		bool toBeWithin(int delta, int expected);
		bool toBeWithin(float delta, float expected);

		bool toStartWith(std::string expected);
		bool toEndWith(std::string expected);
	*/
		bool equal(int expected)
		{
			bool result = value_ == expected;
			if (inverse)
			{
				return !result;
			}

			return result;
		}

	protected:
		bool inverse;
		int value_;
	};

	Matcher expect(const std::string& key)
	{
		int value = linb::any_cast<int>(node_->properties[key]);
		Matcher matcher(value);
		return matcher;
	}


	Node *node_;
};
