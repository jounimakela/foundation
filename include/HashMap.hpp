#pragma once

#include <string>
#include <cstddef>
#include <iostream>
#include <typeinfo>
#include <unordered_map>

#include "Property.hpp"

using KeyValuePairs = std::unordered_map<std::string, PropertyInterface *>;

class HashMap
{
public:
	HashMap() {};
	virtual ~HashMap();

	template<class T>
	T get(const std::string& key)
	{
		if (!contains(key)) {
			std::cerr << "Property(" << key << ") not found. "
				<< "Returning blank type." << std::endl;
			return T();
		}

		if (pairs_.at(key)->type() != typeid(T).name()) {
			std::cerr << "Property(" << key << ") type mismatch. "
				<< "Returning blank type." << std::endl;
			return T();
		}

		return static_cast<Property<T>*>(pairs_[key])->value();
	}

	template<class T>
	void set(const std::string& key, T value)
	{
		if (!contains(key)) {
			std::cerr << "Property(" << key << ") not found. "
				<< "Returning blank type." << std::endl;
			return;
		}

		if (pairs_.at(key)->type() != typeid(T).name()) {
			std::cerr << "Property(" << key << ") type mismatch. "
				<< "Value not set." << std::endl;
			return;
		}

		static_cast<Property<T>*>(pairs_[key])->assign(value);
	}

	template<class T>
	void add(const std::string& key, T value)
	{
		if (contains(key)) {
			std::cerr << "Property(" << key << ") already exists. "
				<< std::endl;
			return;
		}

		Property<T> *property = new Property<T>(key);
		property->assign(value);
		pairs_[property->name()] = property;
	}

	void add(PropertyInterface *property);
	void clone(const HashMap &map);
	bool contains(const std::string& key);
	std::size_t count();

	KeyValuePairs pairs_;
};
