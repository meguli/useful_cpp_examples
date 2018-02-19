#include <playground/unique_ptr.hpp>
#include <catch.hpp>

TEST_CASE("A unique_ptr<int>", "[linear_search]") {
	
	auto ip = chops::make_unique<int>(30);

	SECTION("can be dereferenced and assigned") {
		REQUIRE(*ip == 30);
		*ip = 40;
		REQUIRE(*ip == 40);
	}
}

