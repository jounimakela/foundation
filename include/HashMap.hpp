#pragma once

#include <string>
#include <cstddef>
#include <iostream>
#include <typeinfo>
#include <unordered_map>

#include "any.hpp"

using namespace linb;

class HashMap
{
public:
	template<class T>
	T get(const std::string& key)
	{
		if (!contains(key)) {
			std::cerr	<< "Property(" << key << ") not found. "
					<< "Returning blank type." << std::endl;
			return T();
		}

		if (pairs_.at(key).type().name() != typeid(T).name()) {
			std::cerr	<< "Property(" << key << ") type mismatch. "
					<< "Returning blank type." << std::endl;
			return T();
		}

		return any_cast<T>(pairs_[key]);
	}

	template<class T>
	void set(const std::string& key, T value)
	{
		if (!contains(key)) {
			std::cerr	<< "Property(" << key << ") not found. "
					<< "Returning blank type." << std::endl;
			return;
		}

		if (pairs_.at(key).type().name() != typeid(T).name()) {
			std::cerr	<< "Property(" << key << ") type mismatch. "
					<< "Value not set." << std::endl;
			return;
		}

		pairs_[key] = any(value);
	}

	template<class T>
	void add(const std::string& key, T value)
	{
		if (contains(key)) {
			std::cerr	<< "Property(" << key << ") already exists."
					<< std::endl;
			return;
		}

		pairs_[key] = any(value);
	}

	bool contains(const std::string& key)
	{
		return pairs_.find(key) != pairs_.end();
	}

	std::size_t count()
	{
		return pairs_.size();
	}

protected:
	std::unordered_map<std::string, any> pairs_;
};
