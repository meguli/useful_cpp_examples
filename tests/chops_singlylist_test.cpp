#include <playground/chops_singlylist.hpp>
#include <catch.hpp>

TEST_CASE("A singly linked list", "[singly_list_t]") {
	
	SECTION("can be created") {
        list_t *test_list = make_list();
		REQUIRE(test_list != NULL);

        SECTION("and initially is empty, head is NULL") {
		    REQUIRE(test_list->head == NULL);
	    }
	}

    SECTION("can be populated with items") {
        list_t *test_list = make_list();
        node_t *cur = NULL;

		push_back(test_list, 2.0f);
	    push_back(test_list, 4.0f);
	    push_back(test_list, 7.0f);
	    push_back(test_list, 7.0f);
        push_back(test_list, 8.0f);
        push_back(test_list, 12.0f);
        push_back(test_list, 13.0f);
        push_back(test_list, 14.0f);
        
        cur = test_list->head;
        REQUIRE(cur->value == Approx(2.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(4.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(7.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(7.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(8.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(12.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(13.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(14.0f));
        cur = next_node(cur);
        REQUIRE(cur == NULL);
	}

    SECTION("but we prefer inserting to front") {
        list_t *test_list = make_list();
        node_t *cur = NULL;

		push_front(test_list, 2.0f);
	    push_front(test_list, 4.0f);
	    push_front(test_list, 7.0f);
	    push_front(test_list, 7.0f);
        push_front(test_list, 8.0f);
        push_front(test_list, 12.0f);
        push_front(test_list, 13.0f);
        push_front(test_list, 14.0f);
        
        cur = test_list->head;
        REQUIRE(cur->value == Approx(14.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(13.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(12.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(8.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(7.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(7.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(4.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(2.0f));
        cur = next_node(cur);
        REQUIRE(cur == NULL);
	}

     SECTION("and can be transformed using map_each") {
        list_t *test_list = make_list();
        node_t *cur = NULL;

		push_back(test_list, 2.0f);
	    push_back(test_list, 4.0f);
	    push_back(test_list, 7.0f);
	    push_back(test_list, 7.0f);
        push_back(test_list, 8.0f);
        push_back(test_list, 12.0f);
        push_back(test_list, 13.0f);
        push_back(test_list, 14.0f);

        map_each(test_list, double_node);

        cur = test_list->head;
        REQUIRE(cur->value == Approx(4.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(8.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(14.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(14.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(16.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(24.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(26.0f));
        cur = next_node(cur);
        REQUIRE(cur->value == Approx(28.0f));
        cur = next_node(cur);
        REQUIRE(cur == NULL);
	}
}