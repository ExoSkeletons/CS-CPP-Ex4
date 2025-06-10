#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.hpp"
#include "containers.hpp"

using namespace containers;


TEST_CASE("operations") {
    // Create a container and check its initial state
    MyContainer<int> c;
    CHECK(c.size() == 0); // Container should start empty

    // Add elements to the container
    c.add(5);
    c.add(3);
    c.add(9);
    CHECK(c.size() == 3); // check size

    // Index-based access and bounds checking
    CHECK(c[0] == 5); // First element
    CHECK_THROWS(c[3]); // Out-of-bounds access

    // Remove
    c.remove(3);
    CHECK(c.size() == 2);

    // Attempting to remove a non-existent value should throw
    CHECK_THROWS(c.remove(100));
}

TEST_CASE("Copy, =") {
    // Test copy constructor
    MyContainer<int> a;
    a.add(1);
    a.add(2);

    MyContainer<int> b = a; // Copy constructor
    CHECK(b.size() == 2);
    CHECK(b[0] == 1);
    CHECK(b[1] == 2);

    // Test assignment operator
    MyContainer<int> c;
    c = b;
    CHECK(c.size() == 2);
    CHECK(c[0] == 1);
    CHECK(c[1] == 2);
}

TEST_SUITE("Iterators") {
    TEST_CASE("Iterator - Order") {
        // Iterates over elements in the order they were added
        MyContainer<int> c;
        c.add(1);
        c.add(2);
        c.add(3);

        auto it = c.begin_order();
        std::vector<int> out;
        while (it) out.push_back(*it++);

        CHECK(out == std::vector{1, 2, 3});
    }

    TEST_CASE("Iterator - Reverse Order") {
        // Iterates over elements in reverse order of addition
        MyContainer<int> c;
        c.add(1);
        c.add(2);
        c.add(3);

        auto it = c.begin_reverse_order();
        std::vector<int> out;
        while (it) out.push_back(*it++);

        CHECK(out == std::vector{3, 2, 1});
    }

    TEST_CASE("Iterator - Ascending Order") {
        // Iterates over elements sorted in ascending order
        MyContainer<int> c;
        c.add(8);
        c.add(1);
        c.add(5);

        auto it = c.begin_ascending_order();
        std::vector<int> out;
        while (it) out.push_back(*it++);

        CHECK(out == std::vector{1, 5, 8});
    }

    TEST_CASE("Iterator - Descending Order") {
        // Iterates over elements sorted in descending order
        MyContainer<int> c;
        c.add(8);
        c.add(1);
        c.add(5);

        auto it = c.begin_descending_order();
        std::vector<int> out;
        while (it) out.push_back(*it++);

        CHECK(out == std::vector{8, 5, 1});
    }

    TEST_CASE("Iterator - SideCross Order") {
        MyContainer<int> c;
        c.add(1);
        c.add(2);
        c.add(3);
        c.add(4);
        c.add(5);

        auto it = c.begin_side_cross_order();
        std::vector<int> out;
        while (it)out.push_back(*it++);

        // Expected order
        CHECK(out == std::vector{1, 5, 2, 4, 3});
    }

    TEST_CASE("Iterator - MiddleOut Order") {
        // Iterates starting from the middle and expanding outward
        MyContainer<int> c;
        c.add(1);
        c.add(2);
        c.add(3);
        c.add(4);
        c.add(5);

        auto it = c.begin_middle_out_order();
        std::vector<int> out;
        while (it) out.push_back(*it++);

        // Expected
        CHECK(out == std::vector{3, 2, 4, 1, 5});
    }
}