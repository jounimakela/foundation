#include "HashMap.hpp"

HashMap::~HashMap()
{
	// for (auto pair : pairs_) {
	// 	PropertyInterface *property = (pair.second);
	// 	delete property;
	// }
	KeyValuePairs::iterator anProptertyIter;
	for(anProptertyIter = pairs_.begin();
		anProptertyIter != pairs_.end();
		++anProptertyIter)
	{
		PropertyInterface* anProperty = (anProptertyIter->second);
		delete anProperty;
		anProperty = NULL;
	}
}

bool HashMap::contains(const std::string key)
{
	return (pairs_.find(key) != pairs_.end());
}

void HashMap::add(PropertyInterface *property)
{
	if (!contains(property->name())) {
		pairs_[property->name()] = property;
	}
}

void HashMap::clone(const HashMap &hash_map)
{
	auto pairs = hash_map.pairs_;
	for (auto pair : pairs) {
		PropertyInterface *property = pair.second;
		add(property->clone());
	}
}

std::size_t HashMap::count()
{
	return pairs_.size();
}
