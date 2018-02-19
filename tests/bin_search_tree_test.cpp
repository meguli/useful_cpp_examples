#include <playground/bin_search_tree.hpp>
#include <catch.hpp>
#include <string>

TEST_CASE("For a binary search tree", "[bin_search_tree]")
{
    SECTION("Empty tree has a NULL root"){
        bin_search_tree<int> bst;
        REQUIRE(bst.is_empty() == true);
    }

    SECTION("Insertions are done and BST is correctly deleted afterwards"){
        bin_search_tree<int> bst;
        bst.insert(4);
        bst.insert(2);
        bst.insert(5);

        bin_search_tree<int>::const_nodeptr it = bst.find(8);
        REQUIRE(it == nullptr);

        it = bst.find(4);
        REQUIRE(it->value == 4);

        // This copy will go out of scope and use count will reduce to 1
        // which is the number we got when we created
        REQUIRE(it.use_count() == 2);
    }

    SECTION("We support inorder traversal"){
        bin_search_tree<int> bst;
        bst.insert(4);
        bst.insert(2);
        bst.insert(5);

        bst.inorder_traverse();
    }
}