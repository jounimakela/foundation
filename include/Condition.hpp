#pragma once

#include <regex>
#include <string>
#include <cstddef>

#include "Node.hpp"
#include "any.hpp"

class Condition
{
public:
	Condition(Node *node) : node_(node) = default;

	virtual bool checkStrict() = 0;
	virtual bool checkScore()  = 0;

protected:
	template<typename T>
	class Matcher
	{
	public:
		Matcher(T value) : inverse_(false), value_(value) = default;
		// TODO: Is this necessary?
		// Matcher(Matcher&&) = default;

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
			// TODO: Assert values are int or float type?
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
