#pragma once

#include <string>
#include <regex>

#include "Node.hpp"
#include "any.hpp"

class Condition
{
public:
	Condition(Node *node) : node_(node) = default;

	virtual bool checkStrict() = 0;
	virtual bool checkScore() = 0;

protected:
	template<typename T>
	class Matcher
	{
	public:
		Matcher(T value) : inverse_(false), value_(value) = default;
		// TODO: Is this necessary?
		Matcher(Matcher&&) = default;

		Matcher& notTo()
		{
			inverse = true;
			return *this;
		}

	// Value matchers
		bool equal(T expected)
		{
			bool result = value_ == expected;
			if (inverse)
			{
				return !result;
			}

			return result;
		}

		bool beGreater(T expected);
		{
			bool result = value_ > expected;
			if (inverse)
			{
				return !result;
			}

			return result;
		}

		bool beGreaterOrEqual(T expected);
		{
			bool result = value_ >= expected;
			if (inverse)
			{
				return !result;
			}

			return result;
		}

		bool beLess(T expected);
		{
			bool result = value_ < expected;
			if (inverse)
			{
				return !result;
			}

			return result;
		}

		bool beLessOrEqual(T expected);
		{
			bool result = value_ <= expected;
			if (inverse)
			{
				return !result;
			}

			return result;
		}

		bool beBetween(T minimum, T maximum);
		{
			// TODO: Check values are int or float type?
			bool result = (value_ >= minimum) && (value_ <= maximum)
			if (inverse)
			{
				return !result;
			}

			return result;
		}

		bool match(std::string expression);
		{
			// TODO: Check value is standard string?
			return false;
		}

		bool beWithin(float delta, T expected);
		{
			// TODO: Check values are int or float type?
			return false;
		}

		bool startWith(std::string expected);
		{
			// TODO: Check value is standard string?
			return false;
		}

		bool endWith(std::string expected);
		{
			// TODO: Check value is standard string?
			return false;
		}

	protected:
		bool inverse_;
		T value_;
	};

	template<typename T>
	Matcher<T> expect(const std::string& key)
	{
		T value = linb::any_cast<T>(node_->properties[key]);
		Matcher<T> matcher(value);
		return matcher;
	}

	Node *node_;
};
