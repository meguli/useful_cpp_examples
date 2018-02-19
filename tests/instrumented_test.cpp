#include <playground/instrumented.hpp>
#include <catch.hpp>
#include <string>

// This also demonstrates how we can test the workings of
// special member functions like constructors, destructors etc.
// We need to initialize static members at global scope, this
// will be put into data part of address space and will be 0
// initialized
size_t instrumented<std::string>::counts[7];

TEST_CASE("sizeof(T) and sizeof(instrumented<T>) are equal")
{
    REQUIRE(sizeof(std::string) == sizeof(instrumented<std::string>));
}

TEST_CASE("For a type T", "[special member functions]") {

	SECTION("T a; a = b; works as  T a = b;") {
        // T a; a = b; calls assignment
        instrumented<std::string> is1;
        instrumented<std::string> is2("hello");

		REQUIRE(instrumented<std::string>::default_const_count() == 1);
        REQUIRE(instrumented<std::string>::constructor_count() == 1);
        is1 = is2;
        REQUIRE(instrumented<std::string>::assignment_count() == 1);
        REQUIRE(is1.value == "hello");

        // T a = b; calls copy
        instrumented<std::string> is3("hello");
        instrumented<std::string> is4 = is3;
		REQUIRE(instrumented<std::string>::copy_const_count() == 1);
        REQUIRE(is4.value == "hello");
	}
}

TEST_CASE("and destructors are called properly for T") {
    REQUIRE(instrumented<std::string>::destructor_count() == 4);
}