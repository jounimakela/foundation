#pragma once

#include <regex>
#include <string>
#include <cstddef>

#include "Node.hpp"
#include "any.hpp"

/**
 * TODO: Cleanup the code, requires more "safe" coding
 * This thing should apply rules on creation, since they cannot be changed in
 * runtime. On check() and ratio() they should be applied.
 */

class Condition
{
public:
	Condition(Node *node) : node_(node) = default;

	bool check();
	int ratio();
	int score();

protected:
	template<typename T>
	class Matcher
	{
	public:
		Matcher(T value) : inverse_(false), value_(value) = default;
		// TODO: Is this necessary?
		// Matcher(Matcher&&) = default;

		Matcher& to()
		{
			// FIXME: RULES STRICTINESS
		}

		Matcher& notTo()
		{
			// FIXME: RULES STRICTINESS
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
			// TODO: Assert values are int or float type?
			bool result = value_ >= minimum && value_ <= maximum;
			if (inverse)
			{
				return !result;
			}

			return result;
		}

		bool match(std::string expression);
		{
			// TODO: Assert value is standard string?
			auto regex = std::regex(expression);

			if (std::regex_match(value_, regex)) {
				if (inverse) {
					return false;
				}

				return true;
			}

			return false;
		}

		bool beWithin(float delta, T expected);
		{
			float low  = reinterpret_cast<float>(expected) - delta;
			float high = reinterpret_cast<float>(expected) + delta;

			return beBetween(low, high);
		}

		bool startsWith(std::string expected);
		{
			// TODO: Assert value is standard string?
			std::size_t found = value_.find(expected);

			if (found != std::string::npos) {
				if (found == 0) {
					if (inverse) {
						return false;
					}

					return true;
				}
			}

			return false;
		}

		bool endsWith(std::string expected);
		{
			// TODO: Assert value is standard string?
			std::size_t found = value_.find(expected);

			// TODO: Ugly, there are more similar cases
			if (found != std::string::npos) {
				if (found == value_.length()) {
					if (inverse) {
						return false;
					}

					return true;
				}
			}

			return false;
		}

	protected:
		bool inverse_;
		bool strict_;
		T value_;
	};

	template<typename T>
	Matcher<T> expect(const std::string& key)
	{
		T value = linb::any_cast<T>(node_->properties[key]);
		Matcher<T> matcher(value);
		// Matcher* matcher = new Matcher<T>(value);
		//rules.push_back(matcher);
		return matcher;
	}

	virtual void rules() = 0;

	Node *node_;
	// TODO: These should be maps
	std::vector<Matcher*> loose_rules;
	std::vector<Matcher*> strict_rules;
};
