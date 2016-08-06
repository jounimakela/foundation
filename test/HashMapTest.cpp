#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "HashMap.hpp"

SCENARIO("Hash map can get and set values", "[hash_map][manipulation]")
{
	GIVEN("Hash map") {
		HashMap map;
		map.add<int>("Key", 1337);

		WHEN("Value is added") {
			THEN("Key is stored") {
				REQUIRE(map.contains("Key"));
			}

			THEN("Value can be fetched") {
				int value = map.get<int>("Key");
				REQUIRE(value == 1337);
			}

			THEN("Value can be changed") {
				map.set<int>("Key", 1234);
				REQUIRE(map.get<int>("Key") == 1234);
			}
		}
	}
}

SCENARIO("Hash map can be cloned", "[hash_map][manipulation]")
{
	GIVEN("Hash map") {
		HashMap map;
		map.add<int>("Test", 1337);

		WHEN("Map is cloned") {
			HashMap clonemap;
			clonemap.clone(map);

			THEN("Cloned map has the same keys") {
				REQUIRE(clonemap.contains("Test"));
			}
		}
	}
}
