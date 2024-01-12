
#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
#include "main.cpp"

TEST_CASE("Date class tests") {
    SECTION("Default constructor") {
        Date defaultDate;
        REQUIRE(defaultDate.getYear() == 0);
        REQUIRE(defaultDate.getMonth() == 0);
        REQUIRE(defaultDate.getDay() == 0);
    }

    SECTION("Parameterized constructor") {
        Date date(2024, 1, 12);
        REQUIRE(date.getYear() == 2024);
        REQUIRE(date.getMonth() == 1);
        REQUIRE(date.getDay() == 12);
    }

    // Additional tests can be added here based on the full functionality of the Date class
}

