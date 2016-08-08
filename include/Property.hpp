#pragma once

#include <string>
#include <typeinfo>

class PropertyInterface
{
public:
	PropertyInterface(std::string type, std::string name) :
		type_(type),
		name_(name)
	{
	};

	virtual ~PropertyInterface()
	{
	};

	std::string type() const
	{
		return type_;
	};
	const std::string name() const
	{
		return name_;
	};
	virtual PropertyInterface* clone() = 0;

protected:
	void type(std::string type)
	{
		type_ = type;
	};

private:
	std::string type_;
	const std::string name_;
};

template<class T = unsigned int>
class Property : public PropertyInterface
{
public:
	Property(const std::string& name) :
		PropertyInterface(typeid(T).name(), name),
		value_(T())
	{
	}

	Property(const std::string& name, T value) :
		PropertyInterface(typeid(T).name(), name),
		value_(value)
	{
	}

	T value() const
	{
		return value_;
	}
	void assign(T value)
	{
		value_ = value;
	}
	PropertyInterface* clone()
	{
		Property<T> *property = new Property<T>(name());
		property->assign(value());
		return property;
	}

protected:
	T value_;
};
