#include <vector>
#include <list>
#include <string>
#include <array>
#include <playground/stl_sort_search.hpp>
#include <catch.hpp>

TEST_CASE("A vector<float> with items { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f }", "[linear_search]") {

	using VecIt = std::vector<float>::const_iterator;
	std::vector<float> v{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };

	SECTION("can be searched for 2.0f, successfully") {
		VecIt f1 = linear_search(v.begin(), v.end(), 5.2f - 3.2f);
		REQUIRE(*f1 == Approx(2.0f));
	}

	SECTION("can be searched for 7.0f, but returns end iterator") {
		VecIt f1 = linear_search(v.begin(), v.end(), 8.2f - 1.2f);
		REQUIRE(f1 == v.end());
	}
}

TEST_CASE("A list<float> with items { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f }", "[linear_search]") {

	using ListIt = std::list<float>::const_iterator;
	std::list<float> v{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };

	SECTION("can be searched for 2.0f, successfully") {
		ListIt f1 = linear_search(v.begin(), v.end(), 5.2f - 3.2f);
		REQUIRE(*f1 == Approx(2.0f));
	}

	SECTION("can be searched for 7.0f, but returns end iterator") {
		ListIt f1 = linear_search(v.begin(), v.end(), 8.2f - 1.2f);
		REQUIRE(f1 == v.end());
	}
}


TEST_CASE("A vector<std::string> with items { \"Foo\", \"Bar\", \"foo\", \"bar\", \"baz\" }", "[linear_search]") {

	using StrIt = std::vector<std::string>::const_iterator;
	std::vector<std::string> v{ "Foo", "Bar", "foo", "bar", "baz" };

	SECTION("can be searched for \"baz\", successfully") {
		StrIt f1 = linear_search(v.begin(), v.end(), "baz");
		REQUIRE(*f1 == "baz");
	}

	SECTION("can be searched for \"Baz\", but returns end iterator") {
		StrIt f1 = linear_search(v.begin(), v.end(), "Baz");
		REQUIRE(f1 == v.end());
	}
}

TEST_CASE("vector<float> of items { 6.0f, 5.0f, 3.0f, 1.0f, 8.0f }", "[insertion_sort]") {

	SECTION("can be sorted with insertion_sort") {
		std::vector<float> v{ 6.0f, 5.0f, 3.0f, 1.0f, 8.0f };
		insertion_sort(v.begin(), v.end());
		REQUIRE(v[0] == Approx(1.0f));
		REQUIRE(v[1] == Approx(3.0f));
		REQUIRE(v[2] == Approx(5.0f));
		REQUIRE(v[3] == Approx(6.0f));
		REQUIRE(v[4] == Approx(8.0f));
	}

	SECTION("and insertion_sort do not invalidate the iterators") {
		using VecIt = std::vector<float>::const_iterator;
		std::vector<float> v{ 6.0f, 5.0f, 3.0f, 1.0f, 8.0f };
		VecIt begin_before_sort = v.begin();
		VecIt end_before_sort = v.end();
		insertion_sort(v.begin(), v.end());
		REQUIRE(v.begin() == begin_before_sort);
		REQUIRE(v.end() == end_before_sort);
	}
}

TEST_CASE("vector<std::string> of items { \"Foo\", \"Bar\", \"foo\", \"bar\", \"baz\" }", "[insertion_sort]") {

	SECTION("can be sorted with insertion_sort into lexicographic order") {
		std::vector<std::string> v{ "Foo", "Bar", "foo", "bar", "baz" };
		insertion_sort(v.begin(), v.end());
		REQUIRE(v[0] == "Bar");
		REQUIRE(v[1] == "Foo");
		REQUIRE(v[2] == "bar");
		REQUIRE(v[3] == "baz");
		REQUIRE(v[4] == "foo");
	}

	SECTION("and insertion_sort do not invalidate the iterators") {
		using StrIt = std::vector<std::string>::const_iterator;
		std::vector<std::string> v{ "Foo", "Bar", "foo", "bar", "baz" };
		StrIt begin_before_sort = v.begin();
		StrIt end_before_sort = v.end();
		insertion_sort(v.begin(), v.end());
		REQUIRE(v.begin() == begin_before_sort);
		REQUIRE(v.end() == end_before_sort);
	}
}

TEST_CASE("list<float> of items { 6.0f, 5.0f, 3.0f, 1.0f, 8.0f }", "[insertion_sort]") {
	
	SECTION("can be sorted with insertion_sort since we require BidirectionalIter") {
		using ListIt = std::list<float>::iterator;
		std::list<float> v{ 6.0f, 5.0f, 3.0f, 1.0f, 8.0f };
		ListIt lit = v.begin();
		insertion_sort(v.begin(), v.end());
		REQUIRE(*lit++ == Approx(1.0f));
		REQUIRE(*lit++ == Approx(3.0f));
		REQUIRE(*lit++ == Approx(5.0f));
		REQUIRE(*lit++ == Approx(6.0f));
		REQUIRE(*lit++ == Approx(8.0f));
	}

	SECTION("and insertion_sort do not invalidate the iterators") {
		using ListIt = std::list<float>::iterator;
		std::list<float> v{ 6.0f, 5.0f, 3.0f, 1.0f, 8.0f };
		ListIt begin_before_sort = v.begin();
		ListIt end_before_sort = v.end();
		insertion_sort(v.begin(), v.end());
		REQUIRE(v.begin() == begin_before_sort);
		REQUIRE(v.end() == end_before_sort);
	}
}

TEST_CASE("insertion_sort works with normal arrays and pointers", "[insertion_sort]") {

	SECTION("arrays can be sorted with insertion_sort sine pointers are BidirectionalIter") {
		float  v[] = { 6.0f, 5.0f, 3.0f, 1.0f, 8.0f };
		insertion_sort(v, v + 5);
		REQUIRE(v[0] == Approx(1.0f));
		REQUIRE(v[1] == Approx(3.0f));
		REQUIRE(v[2] == Approx(5.0f));
		REQUIRE(v[3] == Approx(6.0f));
		REQUIRE(v[4] == Approx(8.0f));
	}

	SECTION("and also works with STL arrays") {
		std::array<float, 5> v{ 6.0f, 5.0f, 3.0f, 1.0f, 8.0f };
		insertion_sort(v.begin(), v.end());
		REQUIRE(v[0] == Approx(1.0f));
		REQUIRE(v[1] == Approx(3.0f));
		REQUIRE(v[2] == Approx(5.0f));
		REQUIRE(v[3] == Approx(6.0f));
		REQUIRE(v[4] == Approx(8.0f));
	}
}
