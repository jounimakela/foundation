#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Property.hpp"

#include <string>
#include <typeinfo>

TEST_CASE("Construction", "[property][construction]")
{
	SECTION("Property with name")
	{
		Property<int> property("Test");
		REQUIRE(property.name() == "Test");
	}

	SECTION("Property with value and name")
	{
		Property<std::string> property("Name", "Value");
		REQUIRE(property.name() == "Name");
		REQUIRE(property.value() == "Value");
	}

	SECTION("Property can be cloned")
	{
		Property<std::string> property("Name", "Value");
		PropertyInterface *cloned = property.clone();

		REQUIRE(cloned->name() == "Name");
	}
}

TEST_CASE("Setters and getters", "[property][set][get]")
{
	Property<int> property("Test");

	SECTION("Values can be set")
	{
		property.assign(100);
		REQUIRE(property.value() == 100);

		property.assign(200);
		REQUIRE(property.value() == 200);
	}

	SECTION("Type information is correct")
	{
		REQUIRE(property.type() == typeid(int).name());
	}
}
