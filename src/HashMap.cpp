#include "HashMap.hpp"

HashMap::~HashMap()
{
}

bool HashMap::contains(const std::string& key)
{
	return pairs_.find(key) != pairs_.end();
}

std::size_t HashMap::count()
{
	return pairs_.size();
}
