#pragma once

#include <string>
#include <cstddef>
#include <iostream>
#include <typeinfo>
#include <unordered_map>

using KeyValuePairs = std::unordered_map<std::string, linb::any>;

/**
 * TODO: Rule of five
 */

class HashMap
{
public:
	HashMap()
	{
	};
	virtual ~HashMap();

	template<class T>
	T get(const std::string& key)
	{
		if (!contains(key)) {
			std::cerr	<< "Property(" << key << ") not found. "
					<< "Returning blank type." << std::endl;
			return T();
		}

		if (pairs_.at(key)->type() != typeid(T).name()) {
			std::cerr	<< "Property(" << key << ") type mismatch. "
					<< "Returning blank type." << std::endl;
			return T();
		}

		return static_cast<Property<T>*>(pairs_[key])->value();
	}

	template<class T>
	void set(const std::string& key, T value)
	{
		if (!contains(key)) {
			std::cerr	<< "Property(" << key << ") not found. "
					<< "Returning blank type." << std::endl;
			return;
		}

		if (pairs_.at(key)->type() != typeid(T).name()) {
			std::cerr	<< "Property(" << key << ") type mismatch. "
					<< "Value not set." << std::endl;
			return;
		}

		static_cast<Property<T>*>(pairs_[key])->assign(value);
	}

	template<class T>
	void add(const std::string& key, T value)
	{
		if (contains(key)) {
			std::cerr	<< "Property(" << key << ") already exists. "
					<< std::endl;
			return;
		}

    // TODO: Should get moved, right?
		pairs_[key] = linb::any<T>(value);
	}

	void add(PropertyInterface *property);
	bool contains(const std::string& key);
	std::size_t count();

	KeyValuePairs pairs_;
};
